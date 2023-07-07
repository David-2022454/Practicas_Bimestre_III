/*
  Fundación Kinal Centro Educativo Técnico Labral Kinal
  Grado:   Quinto Electrónica
  Sección: A
  Curso:   Taller de Electrónica Digital y Reparación de Computadoras I
  Nombre:  Juan David Tejada Peñuela 
  Carné:   2022454 
  Nombre:  Jared Hernan Ruiz Anleu
  Carné:   2022011
  Proyecto: Practica #4 - Mapa Interactivo
*/
#include <Wire.h>
#include <PCF8574.h>
#include <SoftwareSerial.h>

const int maxNames = 22; // Numero maximo de nombres a guardar
String names[maxNames]; // Arreglo para almacenar los nombres
int indice_actual = 0; // Indice actual en el arreglo de nombres

#define BUZZER 3 
#define LED_Peten           5 
#define LED_Huehuetenango   6 
#define LED_Quiche          7 
#define LED_AltaVera        8 
#define LED_Izabal          9 
#define LED_SanMarcos      10
#define LED_Totonicapan    11
#define LED_BajaVera       12
#define LED_ElProgreso     13
#define LED_Zacapa         14 //A0
#define LED_Quetzaltenango 15 //A1
#define LED_Solola         16 //A2
#define LED_Chimaltenango  17 //A3 

#define PCF8574_HIGH LOW
#define PCF8574_HIGH HIGH

SoftwareSerial bluetooth(2, 4);

PCF8574 expansor_PCF1(0x27);
PCF8574 expansor_PCF2(0x26);

void printRandomName(void);
void melodia_buzzer(void); 

void setup() {
  // Agregar nombres al arreglo
  names[0] = "Peten";
  names[1] = "Huehuetenango";
  names[2] = "Quiche";
  names[3] = "Alta Verapaz";
  names[4] = "Izabal";
  names[5] = "San Marcos";
  names[6] = "Totonicapan";
  names[7] = "Baja Verapaz";
  names[8] = "El Progreso";
  names[9] = "Zacapa";
  names[10] = "Quetzaltenango";
  names[11] = "Solola";
  names[12] = "Chimaltenango";
  names[13] = "Sacatepequez";
  names[14] = "Guatemala";
  names[15] = "Jalapa";
  names[16] = "Chiquimula";
  names[17] = "Retalhuleu";
  names[18] = "Suchitepequez";
  names[19] = "Escuintla";
  names[20] = "Santa Rosa";
  names[21] = "Jutiapa";

  // Iniciar comunicación serial
  bluetooth.begin(9600);
  bluetooth.println("Hola Tilin");
  Wire.begin();  //Inicio la comunicacion i2c.
  expansor_PCF1.begin();
  expansor_PCF2.begin();
  
  // Inicializar el generador de números aleatorios
  randomSeed(analogRead(A0));

  // Configurar los pines del LED como salida
  for(int i = 5; i <=20; i++){   
  pinMode(i,OUTPUT);             
  }

  pinMode(BUZZER,OUTPUT);
}

void loop() {
 printRandomName();
}

void printRandomName() {
 int indice_random;
  do {
    indice_random = random(maxNames); // Obtener un índice aleatorio
  } while (indice_random == indice_actual); // Evitar la repetición del mismo índice

  indice_actual = indice_random; // Actualizar el índice actual

  String randomName = names[indice_actual]; // Obtener el nombre correspondiente al índice

delay(1000);
  bluetooth.print("Departamento: ");
  bluetooth.println(randomName);

  bluetooth.println("Ingresa la capital:");

  while (!bluetooth.available()) {
    // Esperar hasta que se ingrese una respuesta
  }

  String respuesta = bluetooth.readStringUntil('\n');
  respuesta.trim(); // Eliminar espacios en blanco al inicio y final

  if (randomName == "Peten" && respuesta == "Flores") {
    digitalWrite(LED_Peten, HIGH);
    noTone(BUZZER);
  } else if(randomName == "Peten" && respuesta != "Flores"){
    melodia_buzzer();
  }
  if (randomName == "Huehuetenango" && respuesta == "Huehuetenango") {
    digitalWrite(LED_Huehuetenango, HIGH);
    noTone(BUZZER);
  } else if(randomName == "Huehuetenango" && respuesta != "Huehuetenango"){
    melodia_buzzer();
  }
  if (randomName == "Quiche" && respuesta == "Santa Cruz del Quiche") {
    digitalWrite(LED_Quiche, HIGH);
    noTone(BUZZER);
  } else if(randomName == "Quiche" && respuesta != "Santa Cruz del Quiche"){
    melodia_buzzer();
  }
  if (randomName == "Alta Verapaz" && respuesta == "Coban") {
    digitalWrite(LED_AltaVera, HIGH);
    noTone(BUZZER);
  } else if(randomName == "Alta Verapaz" && respuesta != "Coban"){
    melodia_buzzer();
  }
  if (randomName == "Izabal" && respuesta == "Puerto Barrios") {
    digitalWrite(LED_Izabal, HIGH);
    noTone(BUZZER);
  } else if(randomName == "Izabal" && respuesta != "Puerto Barrios"){
    melodia_buzzer();
  }
  if (randomName == "San Marcos" && respuesta == "San Marcos") {
    digitalWrite(LED_SanMarcos, HIGH);
    noTone(BUZZER);
  } else if(randomName == "San Marcos" && respuesta != "San Marcos"){
    melodia_buzzer();
  }
  if (randomName == "Totonicapan" && respuesta == "Totonicapan") {
    digitalWrite(LED_Totonicapan, HIGH);
    noTone(BUZZER);
  } else if(randomName == "Totonicapan" && respuesta != "Totonicapan"){
    melodia_buzzer();
  }
  if (randomName == "Baja Verapaz" && respuesta == "Salama") {
    digitalWrite(LED_BajaVera, HIGH);
    noTone(BUZZER);
  } else if(randomName == "Baja Verapaz" && respuesta != "Salama"){
    melodia_buzzer();
  }
  if (randomName == "El Progreso" && respuesta == "Guatatoya") {
    digitalWrite(LED_ElProgreso, HIGH);
    noTone(BUZZER);
  } else if(randomName == "El Progreso" && respuesta != "Guatatoya"){
    melodia_buzzer();
  }
  if (randomName == "Zacapa" && respuesta == "Zacapa") {
    digitalWrite(LED_Zacapa, HIGH);
    noTone(BUZZER);
  } else if(randomName == "Zacapa" && respuesta != "Zacapa"){
    melodia_buzzer();
  }
  if (randomName == "Quetzaltenango" && respuesta == "Quetzaltenango") {
    digitalWrite(LED_Quetzaltenango, HIGH);
    noTone(BUZZER);
  } else if(randomName == "Quetzaltenango" && respuesta != "Quetzaltenango"){
    melodia_buzzer();
  }
  if (randomName == "Solola" && respuesta == "Solola") {
    digitalWrite(LED_Solola, HIGH);
    noTone(BUZZER);
  } else if(randomName == "Solola" && respuesta != "Solola"){
    melodia_buzzer();
  }
  if (randomName == "Chimaltenango" && respuesta == "Chimaltenango") {
    digitalWrite(LED_Chimaltenango, HIGH);
    noTone(BUZZER);
  } else if(randomName == "Chimaltenango" && respuesta != "Chimaltenango"){
    melodia_buzzer();
  }
  if (randomName == "Sacatepequez" && respuesta == "Antigua Guatemala") {
    expansor_PCF1.write(0,PCF8574_HIGH);
    noTone(BUZZER);
  } else if(randomName == "Sacatepequez" && respuesta != "Antigua Guatemala"){
    melodia_buzzer();
  }
  if (randomName == "Guatemala" && respuesta == "Ciudad de Guatemala") {
    expansor_PCF1.write(1,PCF8574_HIGH);
    noTone(BUZZER);
  } else if(randomName == "Guatemala" && respuesta != "Ciudad de Guatemala"){
    melodia_buzzer();
  }
  if (randomName == "Jalapa" && respuesta == "Jalapa") {
    expansor_PCF1.write(2,PCF8574_HIGH);
    noTone(BUZZER);
  } else if(randomName == "Jalapa" && respuesta != "Jalapa"){
    melodia_buzzer();
  }
  if (randomName == "Chiquimula" && respuesta == "Jalapa") {
    expansor_PCF1.write(4,PCF8574_HIGH);
    noTone(BUZZER);
  } else if(randomName == "Chiquimula" && respuesta != "Flores"){
    melodia_buzzer();
  }
  if (randomName == "Retalhuleu" && respuesta == "Jalapa") {
    expansor_PCF1.write(5,PCF8574_HIGH);
    noTone(BUZZER);
  } else if(randomName == "Retalhuleu" && respuesta != "Flores"){
    melodia_buzzer();
  }
  if (randomName == "Suchitepequez" && respuesta == "Jalapa") {
    expansor_PCF1.write(6,PCF8574_HIGH);
    noTone(BUZZER);
  } else if(randomName == "Suchitepequez" && respuesta != "Flores"){
    melodia_buzzer();
  }
  if (randomName == "Escuintla" && respuesta == "Jalapa") {
    expansor_PCF1.write(7,PCF8574_HIGH);
    noTone(BUZZER);
  } else if(randomName == "Escuintla" && respuesta != "Flores"){
    melodia_buzzer();
  }
  if (randomName == "Santa Rosa" && respuesta == "Jalapa") {
    expansor_PCF2.write(0,PCF8574_HIGH);
    noTone(BUZZER);
  } else if(randomName == "Santa Rosa" && respuesta != "Flores"){
    melodia_buzzer();
  }
  if (randomName == "Jutiapa" && respuesta == "Jalapa") {
    expansor_PCF2.write(2,PCF8574_HIGH);
    noTone(BUZZER);
  } else if(randomName == "Jutiapa" && respuesta != "Flores"){
    melodia_buzzer();
  }
}

void melodia_buzzer(){
  tone(BUZZER,1000,1000);
}
