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

 

//Directivas de Propocesador
#define btn_rising  2 //pin 2 utilizado para una interrupción externa para rising
#define btn_falling 3 //pin 3 utilizado para una interrupción externa para falling
#define A1 4
#define B_ 5
#define C1 6
#define D1 7
#define E1 8
#define F1 9
#define G1 10
#define A2 11
#define B2 12
#define C2 13
#define D2 14
#define E2 15
#define F2 16
#define G2 17

#define DW1(pin) digitalWrite(pin, HIGH)
#define DW0(pin) digitalWrite(pin, LOW) 

//Funciones ISR 
/*ISR = interrupt services routine
* Estas son las funciones que van a ser llamadas al dispararse una interrupción externa
*/

//funciones 
int i;

void cero_dec(void);
void uno_dec(void);
void dos_dec(void);
void tres_dec(void);
void cuatro_dec(void);
void cinco_dec(void);

void cero_uni(void);
void uno_uni(void);
void dos_uni(void);
void tres_uni(void);
void cuatro_uni(void);
void cinco_uni(void);
void seis_uni(void);
void siete_uni(void);
void ocho_uni(void);
void nueve_uni(void);

void limite_conteo(void);
void conteo(void);

void funcion_ISR_falling(void);
void funcion_ISR_rising(void);

//Variables 

volatile static bool f_print = false; //Variable booleana que me permite imprimir un texto en el Loop
int N= 0; ///variable que va de 0 - 50

 

void setup() {
  Serial.begin(19200); //Inicion de comunicación serial
  pinMode(btn_rising, INPUT);
  pinMode(btn_falling, INPUT);
  attachInterrupt(digitalPinToInterrupt(btn_rising),funcion_ISR_rising,RISING); //Anclar la interrupcion del pin 2 a una funcion de ISR, disparado por el flanco 
  attachInterrupt(digitalPinToInterrupt(btn_falling),funcion_ISR_falling,FALLING); //Anclar la interrupcion del pin 2 a una funcion de ISR, disparado por el flanco
  for(i=2; i<18; i++) {
  pinMode(i, OUTPUT);
} 
}

void loop() {

    conteo();
  if(f_print){
    f_print = false;
    limite_conteo();
    Serial.println(N);    
  }
}

void cero_dec(){
DW1(A1);
DW1(B_); 
DW1(C1);
DW1(D1);
DW1(E1); 
DW1(F1);
DW0(G1);
} 
void uno_dec(){
DW0(A1);
DW1(B_); 
DW1(C1);
DW0(D1);
DW0(E1); 
DW0(F1);
DW0(G1);
} 
void dos_dec(){
DW1(A1);
DW1(B_); 
DW0(C1);
DW1(D1);
DW1(E1); 
DW0(F1);
DW1(G1);
} 
void tres_dec(){
DW1(A1);
DW1(B_); 
DW1(C1);
DW1(D1);
DW0(E1); 
DW0(F1);
DW1(G1);
} 
void cuatro_dec(){
DW0(A1);
DW1(B_); 
DW1(C1);
DW0(D1);
DW0(E1); 
DW1(F1);
DW1(G1);
} 
void cinco_dec(){
DW1(A1);
DW0(B_); 
DW1(C1);
DW1(D1);
DW0(E1); 
DW1(F1);
DW1(G1);
} 

void cero_uni(){
DW1(A2);
DW1(B2); 
DW1(C2);
DW1(D2);
DW1(E2); 
DW1(F2);
DW0(G2);
} 
void uno_uni(void){
DW0(A2);
DW1(B2); 
DW1(C2);
DW0(D2);
DW0(E2); 
DW0(F2);
DW0(G2);
} 
void dos_uni(void){
DW1(A2);
DW1(B2); 
DW0(C2);
DW1(D2);
DW1(E2); 
DW0(F2);
DW1(G2);
} 
void tres_uni(void){
DW1(A2);
DW1(B2); 
DW1(C2);
DW1(D2);
DW0(E2); 
DW0(F2);
DW1(G2);
} 
void cuatro_uni(void){
DW0(A2);
DW1(B2); 
DW1(C2);
DW0(D2);
DW0(E2); 
DW1(F2);
DW1(G2);
} 
void cinco_uni(void){
DW1(A2);
DW0(B2); 
DW1(C2);
DW1(D2);
DW0(E2); 
DW1(F2);
DW1(G2);
} 
void seis_uni(){
DW1(A2);
DW0(B2); 
DW1(C2);
DW1(D2);
DW1(E2); 
DW1(F2);
DW1(G2);
} 
void siete_uni(){
DW1(A2);
DW1(B2); 
DW1(C2);
DW0(D2);
DW0(E2); 
DW0(F2);
DW0(G2);
} 
void ocho_uni(){
DW1(A2);
DW1(B2); 
DW1(C2);
DW1(D2);
DW1(E2); 
DW1(F2);
DW1(G2);
} 
void nueve_uni(){
DW1(A2);
DW1(B2);
DW1(C2);
DW0(D2);
DW0(E2);
DW1(F2);
DW1(G2);
} 

void limite_conteo(){
  if(N<0){
    N=50;
  }
  if(N>50){
    N=0;
  }
}

void conteo(){
if(N==0 || N==1 || N==2 || N==3 || N==4 || N==5 || N==6 || N==7 || N==8 || N==9){
  cero_dec();
}
if(N==10 || N==11 || N==12 || N==13 || N==14 || N==15 || N==16 || N==17 || N==18 || N==19){
  uno_dec();
}
if(N==20 || N==21 || N==22 || N==23 || N==24 || N==25 || N==26 || N==27 || N==28 || N==29){
  dos_dec();
}
if(N==30 || N==31 || N==32 || N==33 || N==34 || N==35 || N==36 || N==37 || N==38 || N==39){
  tres_dec();
}
if(N==40 || N==41 || N==42 || N==43 || N==44 || N==45 || N==46 || N==47 || N==48 || N==49){
  cuatro_dec();
}
if(N==50){
  cinco_dec();
}
if(N==0 || N==10 || N==20 || N==30 || N==40 || N==50){
  cero_uni();
}
if(N==1 || N==11 || N==21 || N==31 || N==41){
  uno_uni();
}
if(N==2 || N==12 || N==22 || N==32 || N==42){
  dos_uni();
}
if(N==3 || N==13 || N==23 || N==33 || N==43){
  tres_uni();
}
if(N==4 || N==14 || N==24 || N==34 || N==44){
  cuatro_uni();
}
if(N==5 || N==15 || N==25 || N==35 || N==45){
  cinco_uni();
}
if(N==6 || N==16 || N==26 || N==36 || N==46){
  seis_uni();
}
if(N==7 || N==17 || N==27 || N==37 || N==47){
  siete_uni();
}
if(N==8 || N==18 || N==28 || N==38 || N==48){
  ocho_uni();
}
if(N==9 || N==19 || N==29 || N==39 || N==49){
  nueve_uni();
}

}

//Funciones ISR
void funcion_ISR_rising(void){
  N++; //aunmento el valor de la variable
  f_print = true; 
}
void funcion_ISR_falling(void){
  N--; //disminuyo el valor de la variable
  f_print = true;
}
