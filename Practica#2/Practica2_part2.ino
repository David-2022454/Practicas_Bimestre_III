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
#define L_R 3
#define L_G 5
#define L_B 6
#define POT 21
int velocidad;
int Color(int R, int G, int B);

void setup() {
for (int i =3 ; i<7 ; i++) {
pinMode(i, OUTPUT);
}
pinMode(POT, INPUT);
}
void loop() {
velocidad = map (analogRead(POT),0,1023,100,1000);
Color(174,92,230); 
delay(velocidad);
Color(255,255,255);
delay(velocidad);
Color(0,255,255);
delay(velocidad);
Color(189,174,20);
delay(velocidad);
Color(255,87,35);
delay(velocidad);
}

int Color(int R, int G, int B) { 
analogWrite(3, R); 
analogWrite(5, G); 
analogWrite(6, B); 
}
