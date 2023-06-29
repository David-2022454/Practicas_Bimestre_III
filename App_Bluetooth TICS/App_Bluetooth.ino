/*
  Fundación Kinal
  Centro Educativo Técnico Labral Kinal
  Electrónica
  Grado: Quinto
  Sección: A
  Curso: Taller de Electrónica Digital y Reparación de Computadoras I
  Nombre: Juan David Tejada Peñuela
  Carné: 2022454
*/

#include <SoftwareSerial.h>
#include <OneWire.h>                
#include <DallasTemperature.h>

#define LED 4

SoftwareSerial CR7(2,3); 

OneWire ourWire(5);                //Se establece el pin 2  como bus OneWire
DallasTemperature sensors(&ourWire); //Se declara una variable u objeto para nuestro sensor
void setup() {
  Serial.begin(9600);
  CR7.begin(9600);
  sensors.begin();
  pinMode(LED,OUTPUT);
}
char recepcion;
void loop() {
  if( CR7.available() ){
    //Serial.write(blue.read());
    recepcion=CR7.read();
    Serial.println(recepcion);
    if( recepcion=='2' ){
      Serial.println("ENCENDER");
      digitalWrite(LED,HIGH);
    }
    if( recepcion=='3' ){
      Serial.println("APAGAR");
      digitalWrite(LED,LOW);
    }
  }
  if( Serial.available() ){
    CR7.write(Serial.read());
  }
    sensors.requestTemperatures();   //Se envía el comando para leer la temperatura
float temp=sensors.getTempCByIndex(0); //Se obtiene la temperatura en ºC
CR7.print(temp); //send distance to MIT App
CR7.print(";");
Serial.println(temp);
}
