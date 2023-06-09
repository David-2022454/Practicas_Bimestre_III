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

const int R1= 10000;

LiquidCrystal_I2C LCD_David(0x27,16,2);

void setup() {
  LCD_David.init(); 
  LCD_David.backlight();
}
void loop() {
  int valor = analogRead(ANALOG_PIN);
  float Rx = ((float)valor*R1)/(1023.0-valor);
  Serial.print("Valor de Resitencia: ");
  Serial.print((int)Rx);
  Serial.println(" Ohms");
  delay(500);

  LCD_David.setCursor(0,0);
  LCD_David.print("Valor de Rx:");
  LCD_David.setCursor(0,1);
  LCD_David.print(Rx);
  LCD_David.setCursor(6,1);
  LCD_David.print(" Ohms");

}
