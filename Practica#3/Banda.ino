/*
  Fundación Kinal Centro Educativo Técnico Labral Kinal
  Grado:   Quinto Electrónica
  Sección: A
  Curso:   Taller de Electrónica Digital y Reparación de Computadoras I
  Nombre:  Juan David Tejada Peñuela 
  Carné:   2022454 
  Nombre:  Jared Hernan Ruiz Anleu
  Carné:   2022011
  Proyecto: Practica #3 - Banda transportadora
*/
//Librerias
#include <Stepper.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//Directivas del preprocesador
#define LDR    A0  //pin A0 del arduino, a este conectaremos el punto medio del divisor de tension entre LDR y una resistencia de 33K
#define LED_V  A3
#define LED_AZUL  4   //led azul conectado al pin 3
#define LED_VERDE 2   //led verde conectado al pin 4
#define LED_ROJO  5   //led rojo conectado al pin 5
#define IN1 8  //Pines del Stepper
#define IN2 9  //Pines del Stepper
#define IN3 10  //Pines del Stepper
#define IN4 11  //Pines del Stepper
#define detector 7  //Sensor de objetos


#define direccion_lcd 0x27
#define filas 2
#define columnas 16

LiquidCrystal_I2C LCD_David(direccion_lcd, columnas, filas);

//Variables
//Valores analogicos de la intensidad de cada color
int resultado_azul, resultado_rojo, resultado_verde;
//Valores analogicos leidos por la LDR
int resultado;

//Valor de umbral para los colores
int tol = 8; //este valor lo podremos cambiar segun los valores leidos por nuestra LDR
//Constructor
Stepper BANDA_STP(2048,IN1,IN3,IN2,IN4);   //Constructor del Stepper
Servo MOTOR;  //Constructor del Servo
void setup() {
//Comunicacion serial
  LCD_David.init();
  LCD_David.backlight();

  //Configuracion de I/O 
  pinMode(LDR, INPUT); //pin A0 como entrada
  pinMode(LED_AZUL, OUTPUT); //pin 3 como salida
  pinMode(LED_VERDE, OUTPUT); //pin 4 como salida
  pinMode(LED_ROJO, OUTPUT);  //pin 5 como salida
  pinMode(LED_V,OUTPUT);

  
  //Los leds inician en un estado de bajo
  digitalWrite(LED_AZUL, LOW);
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_ROJO, LOW);
  
  //Configuracion Banda  
  BANDA_STP.setSpeed(15);
  //Configuracion Servo
  MOTOR.attach(3);
  MOTOR.write(125);  //Posicion de inicio del Servo

}

void loop() {
  if(digitalRead(detector) == true){  //Si no hay un objeto
    BANDA_STP.step(-1);
    }
    if(digitalRead(detector) == false){   //Si hay un objeto
    color();
    }

}

int color(){
  //Enciendo el led rojo
  digitalWrite(LED_ROJO, HIGH);
  //espero 150 milisegundos
  delay(50);

  //Leo el valor captado por la LDR
  resultado = analogRead(LDR);
  resultado_rojo = map(resultado, 0,1023,0,255);  //lo linealizo 
  digitalWrite(LED_ROJO, LOW);
  delay(50);
  //Enciendo el led verde
  digitalWrite(LED_VERDE, HIGH);
  //espero 150 milisegundos
  delay(50);

  //Leo el valor captado por la LDR
  resultado = analogRead(LDR);
  resultado_verde = map(resultado, 0,1023,0,255);  //lo linealizo 
  digitalWrite(LED_VERDE, LOW);
  delay(50);
   //Enciendo el led azul
  digitalWrite(LED_AZUL, HIGH);
  //espero 150 milisegundos
  delay(50);

  //Leo el valor captado por la LDR
  resultado = analogRead(LDR);
  resultado_azul = map(resultado, 0,1023,0,255);  //lo linealizo 
  digitalWrite(LED_AZUL, LOW);
  delay(50);

  if(resultado_verde > resultado_azul && resultado_verde > resultado_rojo){  //Si el resultado del verde es mayor a los demas realiza lo siguiente
  MOTOR.write(110
  );  // Mueve el servo a un lado
  digitalWrite(LED_V, HIGH);
  LCD_David.clear();
  LCD_David.setCursor(5,0);
  LCD_David.print("VERDE");

  BANDA_STP.step(-2048); 
  delay(100);
  
  }
  else{
  LCD_David.clear();
  LCD_David.setCursor(3,0);
  LCD_David.print("NO VERDE");

  MOTOR.write(140);  //Regresa el servo a su posicion de inicio//El color escaneado no es verde
  digitalWrite(LED_V, LOW);
  BANDA_STP.step(-5000); 
  
  }
}
