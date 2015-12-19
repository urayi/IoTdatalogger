/* Autor: José Polanco
https://github.com/urayi
El Circuito:
 * Conexión del Lector de Memoria SD al BUS SPI:
 **UNO y NANO:  
    * MOSI  -> pin 11
    * MISO  -> pin 12
    * CLK   -> pin 13
    * CS    -> pin 10
 * Conexión del Lector de Memoria SD al BUS I2C:
    * SDA   -> pin 04
    * SCL   -> pin 05
 * Conexión de ESP8266 - Se debe alimentar a 3.3V
    * TXesp    ->D0: RXarduino
    * RXesp    ->D1: TXarduino Se debe emplear un convertidor de niveles lógicos
    * CHP      ->3.3V
    * RST      ->3.3V
 */

//Para Memoria SD
#include <SPI.h>
#include <SD.h>
//CHIP SELECT
const int CS=10;
//Variable para el dato que se escribirá en archivo de texto
File dataFile;
//Para RTC
#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 rtc;

//HTTP Metodo GET, se puede emplear el metodo POST.
//Variables de url con los datos que se transmitirán a ThingSpeak
//apikey debe cambiarse por la correspondeinte a su canal en ThingSpeak
String apikey="GQC4K1JYYEK2PTYZ";
String GET = "GET /update?api_key="+apikey;
String field="&field";
String url="";

void setup()
{
  Serial.begin(115200);
  //Inicio Configuración de RTC
  Wire.begin();
  rtc.begin();
  delay(1000);
  if (!rtc.isrunning()) {
    //la siguiente linea sirve para programar la hora del reloj con la del PC
    //Se debe quitar las barras "//" en caso que el reloj no esté ajustado. 
    //rtc.adjust(DateTime(__DATE__, __TIME__));
  }
  //Fin Configuración de RTC
  
  //Inicio Configuración de SD
  pinMode(CS, OUTPUT);
  // Verifica que la tarjeta SD está presente
  if (!SD.begin(CS)) {
     while (!SD.begin(CS)) ;
  }
  // Abre archivo datalog.txt y lo prepara para escritura
  dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (!dataFile) {
      while (1) ;//El programa se detiene por no existir la memoria o el archivo a escribir.
  }
  //Fin Configuración de SD
  delay(10);
}

void loop()
{
  // Construcción de cadena de texto con data para datalog.txt
  String dataString = "";
  // Construcción de cadena de texto con La Fecha y Hora
  DateTime now = rtc.now()+TimeSpan(0,0,0,25);
  dataString += String(now.year(),DEC)+String("/");
  if(now.month()<10){dataString += String("0");}
  dataString += String(now.month(),DEC)+String("/");
  if(now.day()<10){dataString += String("0");}
  dataString += String(now.day(),DEC)+String("\t");
  if(now.hour()<10){dataString += String("0");}
  dataString += String(now.hour(),DEC)+String(":");
  if(now.minute()<10){dataString += String("0");}
  dataString += String(now.minute(),DEC)+String(":");
  if(now.second()<10){dataString += String("0");}
  dataString += String(now.second(),DEC)+String("\t");
    
  // Lee los cuatro sensores y lo agrega al archivo
  url=GET;
  for (int analogPin = 0; analogPin < 4; analogPin++) {
    float sensor = 5.0*analogRead(analogPin)/1024.0;
    //Serial.print(String(sensor));
    if(analogPin==0)//LM35
    {sensor = (sensor)*100.0;}
    if(analogPin==1)//MCP9700
    {sensor = (sensor-0.5)*100.0;}
    if(analogPin==3)//LDR con valores de 0%(oscuridad) a 100%(Soleado)
    {sensor = sensor*100.0/5.0;}
    url+=field+String(analogPin+1)+"="+String(sensor);
    if(sensor<100.0)
    {
      dataString += " ";
      if(sensor<10.0){
        dataString += " ";
      }
    }
    dataString += String(sensor);
    if (analogPin < 3) {
      dataString += String("\t"); 
    }
  }
  // Carga el dato al archivo
  dataFile.println(dataString);
  // Guarda el archivo despues de cargar el dato.
  dataFile.flush();
  // Carga el url de datos al ESP8266 para que lo suba a ThingSpeak.
  //Este dato se escribe en el puerto serial y el ESP8266 lo leerá.
  //Para esto utilizará la instrucción Serial.readString();
  Serial.println(url);
  //Serial.println(dataString);
  // repite el registo luego de 20seg
  delay(20000);
}
