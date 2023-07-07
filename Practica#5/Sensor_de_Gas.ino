/*
  Fundación Kinal Centro Educativo Técnico Labral Kinal
  Grado:   Quinto Electrónica
  Sección: A
  Curso:   Taller de Electrónica Digital y Reparación de Computadoras I
  Nombre:  Juan David Tejada Peñuela 
  Carné:   2022454 
  Proyecto: Practica #5 - Sensor de Gas
*/

#include <LedControl.h>   //libreria que me permite usar el controlador led max7219
#include <Ticker.h> 

//Directivas de preprocesador
#define dataPin0   12   //pin 12 conectado al pin de datos del max7219.
#define dataClock0 11   //pin 11 conectado al pin de clock del max7219.
#define dataLoad0  10   //pin 10 conectado al pin de carga del max7219.
#define BUZZER 3
#define Limit 400
#define MQ_SENSOR 0

float sensorValue;

void alerta(void);

//variable
volatile static bool estado_matriz;

//Constructores
LedControl matriz_led = LedControl(dataPin0,dataClock0,dataLoad0,1);

byte number_0[8]= {        // array que contiene todos los elementos de las
  B00000000,        // filas necesarias por mostrar el digito cero
  B00001000,
  B00101010,
  B00011100,
  B01111111,
  B00011100,
  B00101010,
  B00001000
};
byte number_1[8]= {       // array que contiene todos los elementos de las
  B00000100,        // filas necesarias por mostrar el digito uno
  B00001110,
  B00011110,
  B00111111,
  B01111111,
  B01111111,
  B01111111,
  B00111110
};
byte number_2[8]= {       // array que contiene todos los elementos de las
  B00000000,        // filas necesarias por mostrar el digito uno
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};

void setup()
{
  Serial.begin(9600); 
  Serial.println("MQ2 warming up!");
  delay(20000); // allow the MQ2 to warm up
  matriz_led.shutdown(0,false); //Activo el max7219 para poder mostrar los digitos.
  matriz_led.setIntensity(0,15);  //Brilo a la mitad 
  matriz_led.clearDisplay(0);    //limpio el display
  pinMode(BUZZER,OUTPUT);
}
void loop() 
{

  sensorValue = analogRead(MQ_SENSOR); // analog input pin 0
  unsigned int outputValue = map (sensorValue, 0, 1023, 0, 100);
  Serial.print("Sensor Value: ");
  Serial.print(sensorValue);
  Serial.print("    Percent: ");
  Serial.print(outputValue);
  delay(250);
  
  if(sensorValue > Limit)
  {
    Serial.print(" | Smoke detected!");
    alerta();
    alerta();
    alerta();
    alerta();
    alerta();
      tone(BUZZER,300,400);
      noTone(BUZZER);
      tone(BUZZER,300,400);
  }
 
  else if(sensorValue < Limit){
    Serial.print(" | No smoke detected!");
    for(int i=0; i<8;i++)
      {
        matriz_led.setRow(0,i,number_0[i]);
      }
  }
  Serial.println("");
  delay(2000); // 2s para la siguiente medicion
  
}

void alerta(){
  matriz_led.clearDisplay(0);
      for(int i=0; i<8;i++)
      {
        matriz_led.setRow(0,i,number_1[i]);
      }
      delay(500);
      for(int i=0; i<8;i++)
      {
        matriz_led.setRow(0,i,number_2[i]);
      }
      delay(500);
}
