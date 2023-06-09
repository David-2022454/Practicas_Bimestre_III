/*
 * Fundación Kinal
 * Centro Educativo Técnico Labral Kinal 
 * Electrónica
 * Grado: Quinto
 * Sección: A
 * Curso: Taller de Electrónica Digital y Reparación de Computadoras I
 * Nombre: Juan David Tejada Peñuela
 * Carné: 2022454
*/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define ANALOG_PIN 16
#define direccion_lcd 0x27
#define filas 2
#define columnas 16
float Rx = 0;
int R= 10000;
float Vout = 0;
float operacion = 0;
float lectura_pin = 0;
float result = 0;

LiquidCrystal_I2C LCD_David(0x27,16,2);

void setup() {
  Serial.begin(9600);
  LCD_David.init(); 
  LCD_David.backlight();
}
void loop() {
  lectura_pin = analogRead(ANALOG_PIN);
  operacion = lectura_pin * 5;
  Vout = operacion / 1023;
  result = (5/Vout) -1;
  Rx = R * result;
Serial.println(Vout);
delay(5000);
Serial.println(result);
delay(5000);

  LCD_David.setCursor(0,0);
  LCD_David.print("Valor de Rx:");
  LCD_David.setCursor(0,1);
  LCD_David.print(Rx);
  LCD_David.setCursor(6,1);
  LCD_David.print(" Ohms");


}
