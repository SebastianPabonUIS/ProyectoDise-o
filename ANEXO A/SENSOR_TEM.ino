#include <AdafruitIO.h>
#include <WiFi.h>
#include <Wire.h>
#include "AdafruitIO_WiFi.h"

#define sensor 34
int valvula = 0;

// Configura tu red WiFi
#define WIFI_SSID       "DESKTOP-9BO637L 6209"
#define WIFI_PASS       "H811p!23"

// Datos de conexión de Adafruit IO
#define IO_USERNAME  "edsonrey02"
#define IO_KEY       "aio_LNBe57ZN6PDGDQQisVBkMMszewAa"

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// Declara el objeto AdafruitIO
AdafruitIO_Feed *S_HUMEDAD = io.feed("e-o1a.humedad");
AdafruitIO_Feed *EVAL = io.feed("e-o1a.valvula");
void setup() {

  pinMode(valvula,INPUT);
  Serial.begin(115200);

  // Conexión a WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Conectando a WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Conectado a WIFI");  // informar al monitor serial que se logró la conexion
  Serial.print("Dirección IP ");
  Serial.println(WiFi.localIP());

  // Conexión a Adafruit IO
  io.connect();
  // Espera a la conexión
  while(io.status() < AIO_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conectado a Adafruit IO!");

}

void loop() {
  io.run();
  // Aquí puedes añadir más lógica de tu programa si es necesario


  /*int valor = map(analogRead(sensor), 2000, 4095, 100, 0);*/
  int valor=3600;
    //se hace un mapeo de la lectura del sensor a porcentual
  
    Serial.print("valor: ");
    Serial.print(analogRead(sensor));
    Serial.print("  ");
    Serial.print("Humedad: ");
    Serial.print(valor);
    Serial.println("%");
    delay(5000);

     if(valor>50)
    {
      valvula=0;
    }else{
      valvula=1;
    }
   
    Serial.print("  ");
    Serial.print("valvula: ");
    Serial.print(valvula);

    S_HUMEDAD->save(valor); 
    EVAL->save(valvula);
}