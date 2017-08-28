/*  Autor: José Polanco
    https://github.com/urayi

 * Este sketch envia datos vía HTTP GET requests a www.ThingSpeak.com
 * Se necesita crear un User ID, luego un Channel y obtener una API Key en www.ThingSpeak.com.
*/

#include <ESP8266WiFi.h>

WiFiClient client;
const char* ssid      = "username"; //Nombre de la Red Wifi
const char* password  = "your-password"; //Clave de la Red Wifi
const char* host      = "xxx.xxx.xxx.xxx"; //IP de la pagina www.ThingSpeak.com
const int   httpPort    = 80;// u otro puerto
String url = "";//Variable que contendra la URL que se enviará al servidor de www.ThingSpeak.com
//EJEMPLO DE LECTURA SERIAL:
//API KEY: XXXXXXXXXXXXXXXX
//GET /update?api_key=XXXXXXXXXXXXXXXX&field1=VALOR1&field2=VALOR2&field3=VALOR3&field4=VALOR4

void setup() {
  //Inicia conexión a la red WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
  Serial.begin(115200);
}

void loop() {
  delay(20000); //cada 20seg verificará la existencia de algún dato para cargar al servidor
  //se recibe URL con los datos cargados para cada Field en el Canal de ThingsSpeak
  if (Serial.available() > 0) {
    url = Serial.readString();
    Serial.println(url);
  }
  if (!client.connect(host, httpPort)) {
    return;
  }
  client.print(url +
               " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  delay(10);
  Serial.flush();
}
