# IoTdatalogger

ThingSpeak+ESP8266-01+Arduino Nano V3+RTC+SD+Sensores=IoTdatalogger

La integración de estos componentes permite implementar un dispositivo IoT que envía y almacena datos en http:\\ThingSpeak.com, permitiendo su acceso remoto desde cualquier terminal fijo o movil con acceso a internet, pero cuenta adicionalmente con un sistema de respaldo local de la data en un archivo de texto almacenado en una memoria SD.

La implementación utiliza los siguientes componentes:
  
    *ESP8266-01: Microcontrolador con WIFI y puerto serial

    *Arduino Nano V3: Microcontrolador con puerto serial, Bus I2C, Bus SPI y entradas analógicas y digitales.

    *TinyRTC DS1307: Reloj de Tiempo real que permite tener la fecha y hora exacta. Utiliza el protocolo de comunicación I2C.

    *Lector de Memoria SD: Utiliza el protocolo de comunicación SPI. Cuenta con un pin para conocer el estado de la batería interna.
  
    *Memoria SD 1GB.
  
    *Convertidor de niveles lógicos basado en transistores BSS138
  
    *Sensores:
  
      *LM35: Sensor de Temperatura Ambiente
      *MCP9700AE: Sensor de Temperatura Ambiente
      *LDR: Fotoresistor 5ohm - 500kohm
      *Batería del RTC.
      *Resistencias de 1kohm:

Para la implementación se utilizaron las librerías:

  *Nativas en Arduino IDE:
  
    SPI - Librería para implementar el protócolo de comunicación SPI
    SD - Librería para controlar la lectura y escritura de ficheros contenidos en la memoría SD.
    El ejemplo de nombre "Datalogger" sirvió de base para este proyecto.
    Wire - Librería para manejar el protócolo de comunicación I2C.
  
  *RTCLib: programar y leer la hora del RTC DS1307. El Ejemplo de nombre "ds1307" muestra como ajustar y leer la fecha y hora.
  https://github.com/adafruit/RTClib
  
  *Arduino core for ESP8266 WiFi chip: Esta librería permite programar el Chip ESP8266 utilizando el IDE Arduino con todas sus características de sintaxis, incluyendo varias librerias de arduino.
  https://github.com/esp8266/Arduino
  
  *ESP8266WiFi: incluida en el paquete anterior. El ejemplo de nombre "WifiClient" sirve de base para programar el microcontrolador ESP8266.
  
  El resultado de la implementación estaba disponible temporalmente en el canal: https://thingspeak.com/channels/51166
  
  
  
