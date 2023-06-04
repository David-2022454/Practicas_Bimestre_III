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

#include <OneWire.h>                
#include <DallasTemperature.h>
#include <Ticker.h>
#define Push_Button 3

//Funciones
void lectura_pulso(void);
void lectura_temp(void);

//Constructores
OneWire ourWire(2);                //Se establece el pin 2  como bus OneWire
DallasTemperature sensors(&ourWire); //Se declara una variable u objeto para nuestro sensor
Ticker timer1(lectura_temp, 3000);
Ticker timer2(lectura_pulso, 6000);


void setup() {
Serial.begin(9600);
sensors.begin();
pinMode(Push_Button, INPUT);
timer1.start();
timer2.start();

}

void loop() {
timer1.update();
timer2.update();
}

void lectura_pulso(void){
 boolean estado_boton = digitalRead(Push_Button);
 if(estado_boton == true){
  Serial.println("Sensor Digital Abierto");
 }
 if(estado_boton == false){
  Serial.println("Sensor Digital Cerrado");
 }
}

void lectura_temp(void){
sensors.requestTemperatures();   //Se envía el comando para leer la temperatura
float tempC= sensors.getTempCByIndex(0); //Se obtiene la temperatura en ºC
Serial.println(tempC); 
}
