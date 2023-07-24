/*
 * Fundacion Kinal
 * Centro educativo tecnico laboral Kinal
 * Electronica
 * Grado: Quinto
 * Sección: A
 * Curso: Taller de electronica digital y reparación de computadoras I
 * Nombre: Jared Hernan Ruiz Aleu 
 * Carnet: 2022011
 * Nombre: Juan David Tejada Peñuela 
 * Carnet: 2022454
 * Proyecto: EGGSA
*/

//Librerias
#include <LiquidCrystal_I2C.h>
#include <Wire.h> 
#include <MFRC522.h>
#include <SPI.h>
#include "RTClib.h"

//Directivas de preprocesador
#define direccion_lcd 0x26
#define filas 2
#define columnas 16
#define SS_PIN 10
#define RST_PIN 9
#define G_LED 3
#define R_LED 4

//variables
float Sensibilidad=0.185;
int Sensor = A1;

//Constructores
LiquidCrystal_I2C LCD(direccion_lcd, columnas, filas);
MFRC522 RFID(SS_PIN, RST_PIN);
RTC_DS3231 rtc;

//funciones
void lcd_values(void);
void registered_user(void);
void invalid_user(void);

void setup() {
Serial.begin(9600);
LCD.init(); // Inicializa la LCD
LCD.backlight();
Wire.begin();  // Inicializa la comunicacion I2C
rtc.begin(); 
SPI.begin();          // Inicializa el bus SPI
RFID.PCD_Init();   // Inicializa el MFRC522
Serial.println("Ponga su Tarjeta para la lectura...");
Serial.println();
Serial.println("- - - - - - - - - - - - - - - - - -");
pinMode(G_LED,OUTPUT); // defino led como salida
pinMode(R_LED,OUTPUT); // defino led como salida

// 24 de Julio del 2023, 4:08 pm 
rtc.adjust(DateTime(2023, 7, 24, 4, 17, 30));   
}

void loop() {
LCD.setCursor(0,0);
LCD.print("  EEGSA  Kinal  ");
LCD.setCursor(0,1);
LCD.print("  Energy Meter  ");
digitalWrite(R_LED, LOW); // El led inicia apagado
digitalWrite(G_LED,LOW); // El led inicia apagado

 // Mirando para nuevas tarjeras
  if ( ! RFID.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Selecciona una de las tarjetas
  if ( ! RFID.PICC_ReadCardSerial()) 
  {
    return;
  }
  // Muestra el UID sobre el Monitor Serial
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < RFID.uid.size; i++) 
  {
     Serial.print(RFID.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(RFID.uid.uidByte[i], HEX);
     content.concat(String(RFID.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(RFID.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.println("- - - - - - - - - - - - - - - - - -");
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "13 85 5B AD") // si el No. de tarjeta es el correcto, realiza lo siguiente:
  {
  Serial.println("Acceso Autorizado");
  Serial.println("- - - - - - - - - - - - - - - - - -");
  digitalWrite(G_LED, HIGH);
  digitalWrite(R_LED,LOW);
  registered_user(); // funcion que contiene las instrucciones para confirmar que el usuario es correcto
  delay(2000); // se mantiene el mensaje en la LCD por 2 segundos
  lcd_values(); // muestra en la LCD los valores de V, I, W
  delay(6000); // se mantiene el mensaje en la LCD por 6 segundos
  }
  else if (content.substring(1) != "13 85 5B AD"){ // si el No. de tarjeta es incorrecto, realiza lo siguiente: 
    Serial.println("Acceso Denegado");
    Serial.println("- - - - - - - - - - - - - - - - - -");
  digitalWrite(R_LED, HIGH);
  digitalWrite(G_LED,LOW);
  invalid_user(); // funcion que contiene instrucciones para confirmar que el usuario es incorrecto
  delay(1500);
  }
}


void lcd_values(void){ // funcion que muestra los valores de V, I, W
  

// Valores de voltaje
float voltaje =  (float)25*analogRead(A1)/1023;

// Valores de corriente
float corriente = get_corriente(200);  
  
// Valores de potencia
 float potencia = corriente * voltaje;

LCD.clear();
LCD.setCursor(0,0);  
LCD.print("  EEGSA  Kinal  ");
LCD.setCursor(0,1);  
LCD.print(voltaje,1);
LCD.setCursor(4,1);
LCD.print("V");
LCD.setCursor(6,1);  
LCD.print(corriente, 1);
LCD.setCursor(9,1);
LCD.print("A");
LCD.setCursor(11,1);  
LCD.print(potencia, 1); 
LCD.setCursor(15,1);
LCD.print("W");
  } 

void registered_user(){ // funcion que confirma si el usuario registrado es correcto
DateTime now = rtc.now();
LCD.clear();
LCD.setCursor(0,0);  
LCD.print("Registered  User");
LCD.setCursor(0,1);  
LCD.print("Time:");
LCD.setCursor(5,1);
LCD.print(" ");
LCD.print(now.hour(), DEC);
LCD.print(':');
LCD.print(now.minute(), DEC);
LCD.print(':');
LCD.print(now.second(), DEC);
}

void invalid_user(){ // funcion que confirma si el usuario registrado es incorrecto
LCD.clear();
LCD.setCursor(0,0);  
LCD.print("  EEGSA  Kinal  ");
LCD.setCursor(0,1);  
LCD.print("  Invalid User  ");  
}

float get_corriente(int n_muestras) // funcion que complementa la formula para obtener el valor de corriente
{
  float voltajeSensor;
  float CURRENT=0;
  for(int i=0;i<n_muestras;i++)
  {
    voltajeSensor = analogRead(A0) * (5.0 / 1023.0);////lectura del sensor
    CURRENT=CURRENT+(voltajeSensor-2.5)/Sensibilidad; //Ecuación  para obtener la corriente
  }
  CURRENT=CURRENT/n_muestras;
  return(CURRENT);
}
