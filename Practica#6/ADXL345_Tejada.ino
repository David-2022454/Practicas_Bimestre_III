/*
  Fundación Kinal Centro Educativo Técnico Labral Kinal
  Grado:   Quinto Electrónica
  Sección: A
  Curso:   Taller de Electrónica Digital y Reparación de Computadoras I
  Nombre:  Juan David Tejada Peñuela 
  Carné:   2022454 
  Proyecto: Practica #6 - Aclerómetro ADXL345
*/
#include <SparkFun_ADXL345.h>
#include <SPI.h>
#include <Wire.h>
#include <LedControl.h>   //libreria que me permite usar el controlador led max7219
int x, y, z;

//Directivas de preprocesador
#define dataPin0   12   //pin 12 conectado al pin de datos del max7219.
#define dataClock0 11   //pin 11 conectado al pin de clock del max7219.
#define dataLoad0  10   //pin 10 conectado al pin de carga del max7219.

//Constructores
LedControl matriz_led = LedControl(dataPin0,dataClock0,dataLoad0,1);
ADXL345 adxl_sensor = ADXL345();

void sensor_values(void);
void visualizador(void);

byte bola_1[8]= {        // array que contiene todos los elementos de las
  B01000100,
  B01000100,
  B01000100,
  B01000100,
  B01000100,
  B01000100,
  B01000100,
  B01010100
};
byte bola_2[8]= {        // array que contiene todos los elementos de las
  B01000100,
  B01000100,
  B01000100,
  B01000100,
  B01000100,
  B01000100,
  B01010100,
  B01000100
};
byte bola_3[8]= {        // array que contiene todos los elementos de las
  B01000100,
  B01000100,
  B01000100,
  B01000100,
  B01000100,
  B01010100,
  B01000100,
  B01000100
};
byte bola_4[8]= {        // array que contiene todos los elementos de las
  B01000100,
  B01000100,
  B01000100,
  B01000100,
  B01010100,
  B01000100,
  B01000100,
  B01000100
};
byte bola_5[8]= {        // array que contiene todos los elementos de las
  B01000100,
  B01000100,
  B01000100,
  B01010100,
  B01000100,
  B01000100,
  B01000100,
  B01000100
};
byte bola_6[8]= {        // array que contiene todos los elementos de las
  B01000100,
  B01000100,
  B01010100,
  B01000100,
  B01000100,
  B01000100,
  B01000100,
  B01000100
};
byte bola_7[8]= {        // array que contiene todos los elementos de las
  B01000100,
  B01010100,
  B01000100,
  B01000100,
  B01000100,
  B01000100,
  B01000100,
  B01000100
};
byte bola_8[8]= {        // array que contiene todos los elementos de las
  B01010100,
  B01000100,
  B01000100,
  B01000100,
  B01000100,
  B01000100,
  B01000100,
  B01000100
};

void setup() {
  Serial.begin(9600);
  matriz_led.shutdown(0,false); //Activo el max7219 para poder mostrar los digitos.
  matriz_led.setIntensity(0,15);  //Brilo a la mitad 
  matriz_led.clearDisplay(0);    //limpio el display
  adxl_sensor.powerOn();
  adxl_sensor.setRangeSetting(16);
}

void loop() {
  sensor_values();
  visualizador();
 
}

void sensor_values(void){
  
  adxl_sensor.readAccel(&x, &y, &z);
  Serial.print("x= ");
  Serial.print(x);
  Serial.print("; y= ");
  Serial.print(y);
  Serial.print("; z= ");
  Serial.println(z);
  delay(200);
}

void visualizador(void){
  if(x >= -3 && x <= 3){
    matriz_led.clearDisplay(0);
      for(int i=0; i<8;i++)
      {
        matriz_led.setRow(0,i,bola_4[i]);
      }
      delay(10);
  }

  if(x >= -13 && x <=-4 ){
    matriz_led.clearDisplay(0);
      for(int i=0; i<8;i++)
      {
        matriz_led.setRow(0,i,bola_3[i]);
      }
      delay(10);
  }
  if(x >= -23 && x <=-14){
    matriz_led.clearDisplay(0);
      for(int i=0; i<8;i++)
      {
        matriz_led.setRow(0,i,bola_2[i]);
      }
      delay(10);
  }
  if(x >= -34 && x <=-24 ){
    matriz_led.clearDisplay(0);
      for(int i=0; i<8;i++)
      {
        matriz_led.setRow(0,i,bola_1[i]);
      }
      delay(10);
  }

if(x >= 4 && x <=10 ){
    matriz_led.clearDisplay(0);
      for(int i=0; i<8;i++)
      {
        matriz_led.setRow(0,i,bola_5[i]);
      }
      delay(10);
  }
  if(x >= 11 && x <=17){
    matriz_led.clearDisplay(0);
      for(int i=0; i<8;i++)
      {
        matriz_led.setRow(0,i,bola_6[i]);
      }
      delay(10);
  }
  if(x >= 18 && x <=24 ){
    matriz_led.clearDisplay(0);
      for(int i=0; i<8;i++)
      {
        matriz_led.setRow(0,i,bola_7[i]);
      }
  }
      delay(10);
      if(x >= 25 && x <=33 ){
    matriz_led.clearDisplay(0);
      for(int i=0; i<8;i++)
      {
        matriz_led.setRow(0,i,bola_8[i]);
      }
      delay(10);
  }
  
}
