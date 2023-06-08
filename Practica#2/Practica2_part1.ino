/*
* Fundación Kinal
* Centro Educativo Técnico Labral Kinal 
* Electrónica
* Grado: Quinto
* Sección: A
* Curso: Taller de Electrónica Digital y Reparación de Computadoras I
* Nombre: Juan David Tejada Penuela
* Carné: 2022454
*/
#define LED 3
#define POT 21
int intensidad_led;
int POT_valor;
void setup() {
  pinMode(LED,OUTPUT);
  pinMode(POT,INPUT);
}

void loop() {
  intensidad_led = map (analogRead(POT),0,1023,0,255);
  analogWrite(LED, intensidad_led);
}
