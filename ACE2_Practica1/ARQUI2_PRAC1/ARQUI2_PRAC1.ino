#include <SoftwareSerial.h>
#include "LedControlMS.h"
#define numMatriz 1

SoftwareSerial Arduino(11, 10);

#define NOTA 784
#define APRETADO    0
#define SUELTO      1
#define APRETANDOLO 2
#define SOLTANDOLO  3

const int switch1Pin = 6;    // switch input 1
const int switch2Pin = 7;    // switch input 2
int  melodyPin = 4;
const int boton = 2; // Botón asignado en el pin 2.

int   anterior;      // guardamos el estado anterior.
int   valor;         // valor actual del botón.
int   estado;        // el estado del botón.
unsigned long tiempopresionado = 0;
unsigned long tiemposuelto = 0;
unsigned long tiempoSHN = 0;
unsigned long temporizador;
unsigned long tiemporebote = 50;
String concatenar;

int punteo = 0;

char mensaje[10];
int indiceLetra = 0;

LedControl lc = LedControl(22, 26, 24, numMatriz);
bool letraH[93][8] = {
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  
  {1,1,1,1,1,1,1,1},
  {0,0,0,0,1,0,0,0},
  {0,0,0,0,1,0,0,0},
  {0,0,0,0,1,0,0,0},
  {1,1,1,1,1,1,1,1},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},

  {0,1,1,1,1,1,1,0},
  {1,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1},
  {0,1,1,1,1,1,1,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  
  {1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0},
  {1,0,0,0,0,0,0,0},
  {1,0,0,0,0,0,0,0},
  {1,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  
  {1,1,1,1,1,1,1,0},
  {0,0,0,1,0,0,0,1},
  {0,0,0,1,0,0,0,1},
  {0,0,0,1,0,0,0,1},
  {1,1,1,1,1,1,1,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},

  {0,1,1,1,1,1,1,0},
  {1,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1},
  {1,0,0,1,0,0,0,1},
  {0,1,1,1,0,0,1,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},

  {1,1,1,1,1,1,1,1},
  {0,0,0,1,0,0,0,1},
  {0,0,1,1,0,0,0,1},
  {0,1,0,1,0,0,0,1},
  {1,0,0,0,1,1,1,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},

  {0,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0},
  {1,0,0,0,0,0,0,0},
  {1,0,0,0,0,0,0,0},
  {0,1,1,1,1,1,1,1},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},

  {1,1,1,1,1,1,1,1},
  {0,0,0,1,0,0,0,1},
  {0,0,0,1,0,0,0,1},
  {0,0,0,1,0,0,0,1},
  {0,0,0,0,1,1,1,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},

  {0,1,1,1,1,1,1,0},
  {1,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1},
  {0,1,1,1,1,1,1,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},

  {1,1,1,0,0,0,1,0},
  {1,0,0,1,0,0,0,1},
  {1,0,0,1,0,0,0,1},
  {1,0,0,1,0,0,0,1},
  {1,0,0,0,1,1,1,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},

  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0}
};

//------------------------NUMEROS--------------------------------
int cero[] = {
  NOTA, NOTA, NOTA, NOTA, NOTA
};

int tempo_cero[] = {
  1, 1, 1, 1, 1
};

int uno[] = {
  NOTA, NOTA, NOTA, NOTA, NOTA
};

int tempo_uno[] = {
  4, 1, 1, 1, 1
};

int dos[] = {
  NOTA, NOTA, NOTA, NOTA, NOTA
};

int tempo_dos[] = {
  4, 4, 1, 1, 1
};

int tres[] = {
  NOTA, NOTA, NOTA, NOTA, NOTA
};

int tempo_tres[] = {
  4, 4, 4, 1, 1
};

int cuatro[] = {
  NOTA, NOTA, NOTA, NOTA, NOTA
};

int tempo_cuatro[] = {
  4, 4, 4, 4, 1
};

int cinco[] = {
  NOTA, NOTA, NOTA, NOTA, NOTA
};

int tempo_cinco[] = {
  4, 4, 4, 4, 4
};

int seis[] = {
  NOTA, NOTA, NOTA, NOTA, NOTA
};

int tempo_seis[] = {
  1, 4, 4, 4, 4
};

int siete[] = {
  NOTA, NOTA, NOTA, NOTA, NOTA
};

int tempo_siete[] = {
  1, 1, 4, 4, 4
};

int ocho[] = {
  NOTA, NOTA, NOTA, NOTA, NOTA
};

int tempo_ocho[] = {
  1, 1, 1, 4, 4
};

int nueve[] = {
  NOTA, NOTA, NOTA, NOTA, NOTA
};

int tempo_nueve[] = {
  1, 1, 1, 1, 4
};

//----------------------------------LETRAS---------------------------------

int a[] = {
  NOTA, NOTA
};

int tempo_a[] = {
  4, 1
};

int b[] = {
  NOTA, NOTA, NOTA, NOTA
};

int tempo_b[] = {
  1,4,4,4
};

int c[] = {
  NOTA, NOTA, NOTA, NOTA
};

int tempo_c[] = {
  1,4,1,4
};

int d[] = {
  NOTA, NOTA, NOTA
};

int tempo_d[] = {
  1,4,4
};

int e[] = {
  NOTA
};

int tempo_e[] = {
  4
};

int f[] = {
  NOTA, NOTA, NOTA, NOTA
};

int tempo_f[] = {
  4,4,1,4
};

int g[] = {
  NOTA, NOTA, NOTA
};

int tempo_g[] = {
  1,1,4
};

int h[] = {
  NOTA, NOTA, NOTA, NOTA
};

int tempo_h[] = {
  4,4,4,4
};

int i[] = {
  NOTA, NOTA
};

int tempo_i[] = {
  4,4
};

int j[] = {
  NOTA, NOTA, NOTA, NOTA
};

int tempo_j[] = {
  4,1,1,1
};

int k[] = {
  NOTA, NOTA, NOTA
};

int tempo_k[] = {
  1,4,1
};

int l[] = {
  NOTA, NOTA, NOTA, NOTA
};

int tempo_l[] = {
  4,1,4,4
};

int m[] = {
  NOTA, NOTA
};

int tempo_m[] = {
  1,1
};

int n[] = {
  NOTA, NOTA
};

int tempo_n[] = {
  1,4
};

int o[] = {
  NOTA, NOTA, NOTA
};

int tempo_o[] = {
  1,1,1
};

int p[] = {
  NOTA, NOTA, NOTA, NOTA
};

int tempo_p[] = {
  4,1,1,4
};

int q[] = {
  NOTA, NOTA, NOTA, NOTA
};

int tempo_q[] = {
  1,1,4,1
};

int r[] = {
  NOTA, NOTA, NOTA
};

int tempo_r[] = {
  4,1,4
};

int ese[] = {
  NOTA, NOTA, NOTA
};

int tempo_s[] = {
  4,4,4
};

int t[] = {
  NOTA
};

int tempo_t[] = {
  1
};

int u[] = {
  NOTA, NOTA, NOTA
};

int tempo_u[] = {
  4,4,1
};

int v[] = {
  NOTA, NOTA, NOTA, NOTA
};

int tempo_v[] = {
  4,4,4,1
};

int w[] = {
  NOTA, NOTA, NOTA
};

int tempo_w[] = {
  4,1,1
};

int x[] = {
  NOTA, NOTA, NOTA, NOTA
};

int tempo_x[] = {
  1,4,4,1
};

int y[] = {
  NOTA, NOTA, NOTA, NOTA
};

int tempo_y[] = {
  1,4,1,1
};

int z[] = {
  NOTA, NOTA, NOTA, NOTA
};

int tempo_z[] = {
  1,1,4,4
};

bool punto[8][8] = {
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,1,1,1,1,0,0},
  {0,0,1,1,1,1,0,0},
  {0,0,1,1,1,1,0,0},
  {0,0,1,1,1,1,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
};

bool guion[8][8] = {
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,1,1,1,1,1,1,0},
  {0,1,1,1,1,1,1,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Arduino.begin(4800);
  
  pinMode(4, OUTPUT);//buzzer
  pinMode(8, OUTPUT);
  pinMode(switch1Pin, INPUT); 
  pinMode(switch2Pin, INPUT);
  
  pinMode(boton,INPUT_PULLUP);
  pinMode(13,OUTPUT); // Vamos a usar el led de la placa como señalización.
  estado = HIGH;
  anterior = HIGH;

  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
  //mostrarMensaje();   
}

void loop() {
  if (digitalRead(switch1Pin) == HIGH) { //Hacer post
    lc.clearDisplay(0);
    palPost();
  } 
  else if(digitalRead(switch2Pin) == HIGH){ //Hacer get
    lc.clearDisplay(0);
    if(Arduino.available() > 0){
      String cadenarecibida;
      cadenarecibida = Arduino.readString();
      
      for(int iii = 0; iii < 10; iii++){
        if((cadenarecibida[iii] > 47 && cadenarecibida[iii] < 58) || (cadenarecibida[iii] > 64 && cadenarecibida[iii] < 91)){
          sing(true, cadenarecibida[iii]);
        }
      }
    }
  }
  else { //Hacer get y el juego 
    lc.clearDisplay(0);    
    if(Arduino.available() > 0){
      String cadenarecibida;
      cadenarecibida = Arduino.readString();
      indiceLetra = 0;
      punteo = 0;
      concatenar = "";
      while(true && indiceLetra != 10){
        if((cadenarecibida[indiceLetra] > 47 && cadenarecibida[indiceLetra] < 58) || (cadenarecibida[indiceLetra] > 64 && cadenarecibida[indiceLetra] < 91)){
          desplegar(cadenarecibida[indiceLetra]);          
          juego(cadenarecibida[indiceLetra]);
          if(indiceLetra == 10){
            break;
          }
        }
      }
    }
  }
}

int song = 0;

void mostrarMensaje() {
  for(int k=0; k<86; k++) { 
    for(int i=0; i<8; i++) {
      for(int j=0; j<8; j++) {
        lc.setLed(0, i, j, letraH[i+k][j]);
      }
    }
    delay(350);
    //meter aca el morse de las letras del mensaje de inicio!
    if(k == 6){
      sing(false, 'H');
    }
    if(k == 14){
      sing(false, 'O');
    }
    if(k == 22){
      sing(false, 'L');
    }
    if(k == 30){
      sing(false, 'A');
    }
    if(k == 38){
      sing(false, 'G');
    }
    if(k == 46){
      sing(false, 'R');
    }
    if(k == 54){
      sing(false, 'U');
    }
    if(k == 62){
      sing(false, 'P');
    }
    if(k == 70){
      sing(false, 'O');
    }
    if(k == 78){
      sing(false, '2');
    }
  }
}

void juego(char car){
  if ( valor==digitalRead(2) ) {
    temporizador = 0;
  }
  else if ( temporizador == 0 ) {
    temporizador = millis();
  }
  else if ( millis()-temporizador > tiemporebote ) {
    valor = !valor;
  }
  if ( anterior==LOW  && valor==LOW  ) {estado = APRETADO; tiempopresionado++;}
  if ( anterior==LOW  && valor==HIGH ) {estado = SOLTANDOLO;}
  if ( anterior==HIGH && valor==LOW  ) {estado = APRETANDOLO;}
  if ( anterior==HIGH && valor==HIGH ) {estado = SUELTO; tiempopresionado = 0; /*tiempoSHN++;*/ tiemposuelto++;}

  anterior = valor;

  //desplegar(car);
  switch ( estado ) {
    case SUELTO:   
      digitalWrite(13,LOW); 
      noTone(4);
      Serial.println(tiempoSHN);
      if(tiemposuelto == 100){
        veriSSHC(concatenar, car);
        concatenar = "";
      } 
//      if(tiempoSHN == 400){
//        veriSSHC(concatenar, car);
//        concatenar = "";
//        fracaso();
//        indiceLetra++;
//        tiempoSHN = 0;
//      } 
      break;
    case APRETANDOLO: 
      break;
    case APRETADO: 
      digitalWrite(13,HIGH); 
      tone(4,NOTA,200); 
      //desplegar(car);
      break;
    case SOLTANDOLO: 
      tiemposuelto = 0; 
      //tiempoSHN = 0; 
      if(tiempopresionado > 3 && tiempopresionado < 15){
        concatenar += ".";
      }else if(tiempopresionado > 15){
        concatenar += "-";
      }
      break; 
    default: 
      break;
  }
}

void exito(){
  tone(4,1047);
  delay(250);
  noTone(4);
  delay(100);
  tone(4,1109);
  delay(500);
  noTone(4);
  punteo++;
}

void fracaso(){
  tone(4,294);
  delay(250);
  noTone(4);
  delay(100);
  tone(4,294);
  delay(500);
  noTone(4);
}

void veriSSHC(String caracter, char car) {
  Serial.println(caracter);
  Serial.println(car);
  if(caracter == "-----" && car == '0'){
    Serial.print("0");
    exito();
    indiceLetra++;
  }
  else if(caracter == ".----" && car == '1'){
    Serial.print("1");
    exito();
    indiceLetra++;
  }
  else if(caracter == "..---" && car == '2'){
    Serial.print("2");
    exito();
    indiceLetra++;
  }
  else if(caracter == "...--" && car == '3'){
    Serial.print("3");
    exito();
    indiceLetra++;
  }
  else if(caracter == "....-" && car == '4'){
    Serial.print("4");
    exito();
    indiceLetra++;
  }
  else if(caracter == "....." && car == '5'){
    Serial.print("5");
    exito();
    indiceLetra++;
  }
  else if(caracter == "-...." && car == '6'){
    Serial.print("6");
    exito();
    indiceLetra++;
  }
  else if(caracter == "--..." && car == '7'){
    Serial.print("7");
    exito();
    indiceLetra++;
  }
  else if(caracter == "---.." && car == '8'){
    Serial.print("8");
    exito();
    indiceLetra++;
  }
  else if(caracter == "----." && car == '9'){
    Serial.print("9");
    exito();
    indiceLetra++;
  }
  else if(caracter == ".-" && car == 'A'){
    Serial.print("A");
    exito();
    indiceLetra++;
  }
  else if(caracter == "-..." && car == 'B'){
    Serial.print("B");
    exito();
    indiceLetra++;
  }
  else if(caracter == "-.-." && car == 'C'){
    Serial.print("C");
    exito();
    indiceLetra++;
  }
  else if(caracter == "-.." && car == 'D'){
    Serial.print("D");
    exito();
    indiceLetra++;
  }
  else if(caracter == "." && car == 'E'){
    Serial.print("E");
    exito();
    indiceLetra++;
  }
  else if(caracter == "..-." && car == 'F'){
    Serial.print("F");
    exito();
    indiceLetra++;
  }
  else if(caracter == "--." && car == 'G'){
    Serial.print("G");
    exito();
    indiceLetra++;
  }
  else if(caracter == "...." && car == 'H'){
    Serial.print("H");
    exito();
    indiceLetra++;
  }
  else if(caracter == ".." && car == 'I'){
    Serial.print("I");
    exito();
    indiceLetra++;
  }
  else if(caracter == ".---" && car == 'J'){
    Serial.print("J");
    exito();
    indiceLetra++;
  }
  else if(caracter == "-.-" && car == 'K'){
    Serial.print("K");
    exito();
    indiceLetra++;
  }
  else if(caracter == ".-.." && car == 'L'){
    Serial.print("L");
    exito();
    indiceLetra++;
  }
  else if(caracter == "--" && car == 'M'){
    Serial.print("M");
    exito();
    indiceLetra++;
  }
  else if(caracter == "-." && car == 'N'){
    Serial.print("N");
    exito();
    indiceLetra++;
  }
  else if(caracter == "---" && car == 'O'){
    Serial.print("O");
    exito();
    indiceLetra++;
  }
  else if(caracter == ".--." && car == 'P'){
    Serial.print("P");
    exito();
    indiceLetra++;
  }
  else if(caracter == "--.-" && car == 'Q'){
    Serial.print("Q");
    exito();
    indiceLetra++;
  }
  else if(caracter == ".-." && car == 'R'){
    Serial.print("R");
    exito();
    indiceLetra++;
  }
  else if(caracter == "..." && car == 'S'){
    Serial.print("S");
    exito();
    indiceLetra++;
  }
  else if(caracter == "-" && car == 'T'){
    Serial.print("T");
    exito();
    indiceLetra++;
  }
  else if(caracter == "..-" && car == 'U'){
    Serial.print("U");
    exito();
    indiceLetra++;
  }
  else if(caracter == "...-" && car == 'V'){
    Serial.print("V");
    exito();
    indiceLetra++;
  }
  else if(caracter == ".--" && car == 'W'){
    Serial.print("W");
    exito();
    indiceLetra++;
  }
  else if(caracter == "-..-" && car == 'X'){
    Serial.print("X");
    exito();
    indiceLetra++;
  }
  else if(caracter == "-.--" && car == 'Y'){
    Serial.print("Y");
    exito();
    indiceLetra++;
  }
  else if(caracter == "--.." && car == 'Z'){
    Serial.print("Z");
    exito();
    indiceLetra++;
  }
  else{
    fracaso();
    indiceLetra++;
  }
  if(indiceLetra == 10)
  {
    Serial.print(punteo);
    if(punteo == 1){
      desplegar('1');
    }
    if(punteo == 2){
      desplegar('2');
    }
    if(punteo == 3){
      desplegar('3');
    }
    if(punteo == 4){
      desplegar('4');
    }
    if(punteo == 5){
      desplegar('5');
    }
    if(punteo == 6){
      desplegar('6');
    }
    if(punteo == 7){
      desplegar('7');
    }
    if(punteo == 8){
      desplegar('8');
    }
    if(punteo == 9){
      desplegar('9');
    }
    if(punteo == 0){
      desplegar('0');
    }
    if(punteo == 10){
      desplegar('1');
    }    
    
    delay(2500);
    return;
  }
}

void palPost() {
  if ( valor==digitalRead(2) ) {
    temporizador = 0;
  }
  else if ( temporizador == 0 ) {
    temporizador = millis();
  }
  else if ( millis()-temporizador > tiemporebote ) {
    valor = !valor;
  }
  if ( anterior==LOW  && valor==LOW  ) {estado = APRETADO; tiempopresionado++;}
  if ( anterior==LOW  && valor==HIGH ) {estado = SOLTANDOLO;}
  if ( anterior==HIGH && valor==LOW  ) {estado = APRETANDOLO;}
  if ( anterior==HIGH && valor==HIGH ) {estado = SUELTO; tiempopresionado = 0; tiemposuelto++;}

  anterior = valor;

  switch ( estado ) {
    case SUELTO:   
      digitalWrite(13,LOW); 
      noTone(4);
      if(tiemposuelto == 900){
        MorseAscii(concatenar);
        concatenar = "";
      } 
      break;
    case APRETANDOLO: 
      break;
    case APRETADO: 
      digitalWrite(13,HIGH); 
      tone(4,NOTA,200); 
      break;
    case SOLTANDOLO: 
      tiemposuelto = 0; 
      if(tiempopresionado > 25 && tiempopresionado < 90){
        concatenar += ".";
      }else if(tiempopresionado > 90){
        concatenar += "-";
      }
      break; 
    default: 
      break;
  }
}

void MorseAscii(String caracter) {
  if(caracter == "-----"){
    Serial.print("0");
    mensaje[indiceLetra] = '0';
    indiceLetra++;
  }
  else if(caracter == ".----"){
    Serial.print("1");
    mensaje[indiceLetra] = '1';
    indiceLetra++;
  }
  else if(caracter == "..---"){
    Serial.print("2");
    mensaje[indiceLetra] = '2';
    indiceLetra++;
  }
  else if(caracter == "...--"){
    Serial.print("3");
    mensaje[indiceLetra] = '3';
    indiceLetra++;
  }
  else if(caracter == "....-"){
    Serial.print("4");
    mensaje[indiceLetra] = '4';
    indiceLetra++;
  }
  else if(caracter == "....."){
    Serial.print("5");
    mensaje[indiceLetra] = '5';
    indiceLetra++;
  }
  else if(caracter == "-...."){
    Serial.print("6");
    mensaje[indiceLetra] = '6';
    indiceLetra++;
  }
  else if(caracter == "--..."){
    Serial.print("7");
    mensaje[indiceLetra] = '7';
    indiceLetra++;
  }
  else if(caracter == "---.."){
    Serial.print("8");
    mensaje[indiceLetra] = '8';
    indiceLetra++;
  }
  else if(caracter == "----."){
    Serial.print("9");
    mensaje[indiceLetra] = '9';
    indiceLetra++;
  }
  else if(caracter == ".-"){
    Serial.print("A");
    mensaje[indiceLetra] = 'A';
    indiceLetra++;
  }
  else if(caracter == "-..."){
    Serial.print("B");
    mensaje[indiceLetra] = 'B';
    indiceLetra++;
  }
  else if(caracter == "-.-."){
    Serial.print("C");
    mensaje[indiceLetra] = 'C';
    indiceLetra++;
  }
  else if(caracter == "-.."){
    Serial.print("D");
    mensaje[indiceLetra] = 'D';
    indiceLetra++;
  }
  else if(caracter == "."){
    Serial.print("E");
    mensaje[indiceLetra] = 'E';
    indiceLetra++;
  }
  else if(caracter == "..-."){
    Serial.print("F");
    mensaje[indiceLetra] = 'F';
    indiceLetra++;
  }
  else if(caracter == "--."){
    Serial.print("G");
    mensaje[indiceLetra] = 'G';
    indiceLetra++;
  }
  else if(caracter == "...."){
    Serial.print("H");
    mensaje[indiceLetra] = 'H';
    indiceLetra++;
  }
  else if(caracter == ".."){
    Serial.print("I");
    mensaje[indiceLetra] = 'I';
    indiceLetra++;
  }
  else if(caracter == ".---"){
    Serial.print("J");
    mensaje[indiceLetra] = 'J';
    indiceLetra++;
  }
  else if(caracter == "-.-"){
    Serial.print("K");
    mensaje[indiceLetra] = 'K';
    indiceLetra++;
  }
  else if(caracter == ".-.."){
    Serial.print("L");
    mensaje[indiceLetra] = 'L';
    indiceLetra++;
  }
  else if(caracter == "--"){
    Serial.print("M");
    mensaje[indiceLetra] = 'M';
    indiceLetra++;
  }
  else if(caracter == "-."){
    Serial.print("N");
    mensaje[indiceLetra] = 'N';
    indiceLetra++;
  }
  else if(caracter == "---"){
    Serial.print("O");
    mensaje[indiceLetra] = 'O';
    indiceLetra++;
  }
  else if(caracter == ".--."){
    Serial.print("P");
    mensaje[indiceLetra] = 'P';
    indiceLetra++;
  }
  else if(caracter == "--.-"){
    Serial.print("Q");
    mensaje[indiceLetra] = 'Q';
    indiceLetra++;
  }
  else if(caracter == ".-."){
    Serial.print("R");
    mensaje[indiceLetra] = 'R';
    indiceLetra++;
  }
  else if(caracter == "..."){
    Serial.print("S");
    mensaje[indiceLetra] = 'S';
    indiceLetra++;
  }
  else if(caracter == "-"){
    Serial.print("T");
    mensaje[indiceLetra] = 'T';
    indiceLetra++;
  }
  else if(caracter == "..-"){
    Serial.print("U");
    mensaje[indiceLetra] = 'U';
    indiceLetra++;
  }
  else if(caracter == "...-"){
    Serial.print("V");
    mensaje[indiceLetra] = 'V';
    indiceLetra++;
  }
  else if(caracter == ".--"){
    Serial.print("W");
    mensaje[indiceLetra] = 'W';
    indiceLetra++;
  }
  else if(caracter == "-..-"){
    Serial.print("X");
    mensaje[indiceLetra] = 'X';
    indiceLetra++;
  }
  else if(caracter == "-.--"){
    Serial.print("Y");
    mensaje[indiceLetra] = 'Y';
    indiceLetra++;
  }
  else if(caracter == "--.."){
    Serial.print("Z");
    mensaje[indiceLetra] = 'Z';
    indiceLetra++;
  }
  if(indiceLetra == 10)
  {
    Serial.println("");
    Serial.println(mensaje);
    Arduino.write(mensaje);
    indiceLetra = 0;
  }
}

void sing(bool PyG, int s) {
  // iterate over the notes of the melody:
  song = s;
  if (song == 48) {
    Serial.println(" 'CERO'");
    int size = sizeof(cero) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo_cero[thisNote];

      buzz(PyG, melodyPin, cero[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(PyG, melodyPin, 0, noteDuration);

    }
  }
  else if (song == 49) {
    Serial.println(" 'UNO'");
    int size = sizeof(uno) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo_uno[thisNote];

      buzz(PyG, melodyPin, uno[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(PyG, melodyPin, 0, noteDuration);

    }
  }
  else if (song == 50) {
    Serial.println(" 'DOS'");
    int size = sizeof(dos) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo_dos[thisNote];

      buzz(PyG, melodyPin, dos[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(PyG, melodyPin, 0, noteDuration);

    }
  }
  else if (song == 51) {
    Serial.println(" 'TRES'");
    int size = sizeof(tres) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo_tres[thisNote];

      buzz(PyG, melodyPin, tres[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(PyG, melodyPin, 0, noteDuration);

    }
  }
  else if (song == 52) {
    Serial.println(" 'CUATRO'");
    int size = sizeof(cuatro) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo_cuatro[thisNote];

      buzz(PyG, melodyPin, cuatro[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(PyG, melodyPin, 0, noteDuration);

    }
  }
  else if (song == 53) {
    Serial.println(" 'CINCO'");
    int size = sizeof(cinco) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo_cinco[thisNote];

      buzz(PyG, melodyPin, cinco[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(PyG, melodyPin, 0, noteDuration);

    }
  }
  else if (song == 54) {
    Serial.println(" 'SEIS'");
    int size = sizeof(seis) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo_seis[thisNote];

      buzz(PyG, melodyPin, seis[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(PyG, melodyPin, 0, noteDuration);

    }
  }
  else if (song == 55) {
    Serial.println(" 'SIETE'");
    int size = sizeof(siete) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo_siete[thisNote];

      buzz(PyG, melodyPin, siete[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(PyG, melodyPin, 0, noteDuration);

    }
  }
  else if (song == 56) {
    Serial.println(" 'OCHO'");
    int size = sizeof(ocho) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo_ocho[thisNote];

      buzz(PyG, melodyPin, ocho[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(PyG, melodyPin, 0, noteDuration);

    }
  }
  else if (song == 57) {
    Serial.println(" 'NUEVE'");
    int size = sizeof(nueve) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo_nueve[thisNote];

      buzz(PyG, melodyPin, nueve[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(PyG, melodyPin, 0, noteDuration);

    }
  }
  else if (song == 65) {
    Serial.println(" 'A'");
    int size = sizeof(a) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo_a[thisNote];

      buzz(PyG, melodyPin, a[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(PyG, melodyPin, 0, noteDuration);

    }
  }
  else if (song == 66) {
    Serial.println(" 'B'");
    int size = sizeof(b) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo_b[thisNote];

      buzz(PyG, melodyPin, b[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(PyG, melodyPin, 0, noteDuration);

    }
  }
  else if (song == 67) {
    Serial.println(" 'C'");
    int size = sizeof(c) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo_c[thisNote];

      buzz(PyG, melodyPin, c[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(PyG, melodyPin, 0, noteDuration);

    }
  }
  else if (song == 68) {
    Serial.println(" 'D'");
    int size = sizeof(d) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo_d[thisNote];

      buzz(PyG, melodyPin, d[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(PyG, melodyPin, 0, noteDuration);

    }
  }
  else if (song == 69) {
    Serial.println(" 'E'");
    int size = sizeof(e) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo_e[thisNote];

      buzz(PyG, melodyPin, e[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(PyG, melodyPin, 0, noteDuration);

    }
  }
  else if (song == 70) {
    Serial.println(" 'F'");
    int size = sizeof(f) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo_f[thisNote];

      buzz(PyG, melodyPin, f[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(PyG, melodyPin, 0, noteDuration);

    }
  }
  else if (song == 71) {
    Serial.println(" 'G'");
    int size = sizeof(g) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo_g[thisNote];

      buzz(PyG, melodyPin, g[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(PyG, melodyPin, 0, noteDuration);

    }
  }
  else if (song == 72) {
    Serial.println(" 'H'");
    int size = sizeof(h) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo_h[thisNote];

      buzz(PyG, melodyPin, h[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(PyG, melodyPin, 0, noteDuration);

    }
  }
  else if (song == 73) {
    Serial.println(" 'I'");
    int size = sizeof(i) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo_i[thisNote];

      buzz(PyG, melodyPin, i[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(PyG, melodyPin, 0, noteDuration);

    }
  }
  else if (song == 74) {
    Serial.println(" 'J'");
    int size = sizeof(j) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo_j[thisNote];

      buzz(PyG, melodyPin, j[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(PyG, melodyPin, 0, noteDuration);

    }
  }
  else if (song == 75) {
    Serial.println(" 'K'");
    int size = sizeof(k) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo_k[thisNote];

      buzz(PyG, melodyPin, k[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(PyG, melodyPin, 0, noteDuration);

    }
  }
  else if (song == 76) {
    Serial.println(" 'L'");
    int size = sizeof(l) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo_l[thisNote];

      buzz(PyG, melodyPin, l[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(PyG, melodyPin, 0, noteDuration);

    }
  }
  else if (song == 77) {
    Serial.println(" 'M'");
    int size = sizeof(m) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo_m[thisNote];

      buzz(PyG, melodyPin, m[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(PyG, melodyPin, 0, noteDuration);

    }
  }
  else if (song == 78) {
    Serial.println(" 'N'");
    int size = sizeof(n) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo_n[thisNote];

      buzz(PyG, melodyPin, n[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(PyG, melodyPin, 0, noteDuration);

    }
  }
  else if (song == 79) {
    Serial.println(" 'O'");
    int size = sizeof(o) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo_o[thisNote];

      buzz(PyG, melodyPin, o[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(PyG, melodyPin, 0, noteDuration);

    }
  }
  else if (song == 80) {
    Serial.println(" 'P'");
    int size = sizeof(p) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo_p[thisNote];

      buzz(PyG, melodyPin, p[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(PyG, melodyPin, 0, noteDuration);

    }
  }
  else if (song == 81) {
    Serial.println(" 'Q'");
    int size = sizeof(q) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo_q[thisNote];

      buzz(PyG, melodyPin, q[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(PyG, melodyPin, 0, noteDuration);

    }
  }
  else if (song == 82) {
    Serial.println(" 'R'");
    int size = sizeof(r) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo_r[thisNote];

      buzz(PyG, melodyPin, r[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(PyG, melodyPin, 0, noteDuration);

    }
  }
  else if (song == 83) {
    Serial.println(" 'S'");
    int size = sizeof(ese) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo_s[thisNote];

      buzz(PyG, melodyPin, ese[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(PyG, melodyPin, 0, noteDuration);

    }
  }
  else if (song == 84) {
    Serial.println(" 'T'");
    int size = sizeof(t) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo_t[thisNote];

      buzz(PyG, melodyPin, t[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(PyG, melodyPin, 0, noteDuration);

    }
  }
  else if (song == 85) {
    Serial.println(" 'U'");
    int size = sizeof(u) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo_u[thisNote];

      buzz(PyG, melodyPin, u[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(PyG, melodyPin, 0, noteDuration);

    }
  }
  else if (song == 86) {
    Serial.println(" 'V'");
    int size = sizeof(v) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo_v[thisNote];

      buzz(PyG, melodyPin, v[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(PyG, melodyPin, 0, noteDuration);

    }
  }
  else if (song == 87) {
    Serial.println(" 'W'");
    int size = sizeof(w) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo_w[thisNote];

      buzz(PyG, melodyPin, w[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(PyG, melodyPin, 0, noteDuration);

    }
  }
  else if (song == 88) {
    Serial.println(" 'X'");
    int size = sizeof(x) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo_x[thisNote];

      buzz(PyG, melodyPin, x[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(PyG, melodyPin, 0, noteDuration);

    }
  }
  else if (song == 89) {
    Serial.println(" 'Y'");
    int size = sizeof(y) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo_y[thisNote];

      buzz(PyG, melodyPin, y[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(PyG, melodyPin, 0, noteDuration);

    }
  }
  else if (song == 90) {
    Serial.println(" 'Z'");
    int size = sizeof(z) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo_z[thisNote];

      buzz(PyG, melodyPin, z[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(PyG, melodyPin, 0, noteDuration);

    }
  }
  delay(1000);
}

void buzz(bool PyG, int targetPin, long frequency, long length) {
  if(length == 250 && PyG == true){
    for(int i=0; i<8; i++) {
      for(int j=0; j<8; j++) {
        lc.setLed(0, i, j, punto[i][j]);
      }
    }
  }  
  else if(length == 1000 && PyG == true){
    for(int i=0; i<8; i++) {
      for(int j=0; j<8; j++) {
        lc.setLed(0, j, i, guion[i][j]);
      }
    }
  }
  long delayValue = 1000000 / frequency / 2; // calculate the delay value between transitions
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = frequency * length / 1000; // calculate the number of cycles for proper timing
  //// multiply frequency, which is really cycles per second, by the number of seconds to
  //// get the total number of cycles to produce
  for (long i = 0; i < numCycles; i++) { // for the calculated length of time...
    digitalWrite(targetPin, HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(targetPin, LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait again or the calculated delay value
  }
  if(PyG == true){
    lc.clearDisplay(0);
  }
}

void desplegar(char carac){
  
  bool matriz0[8][8] ={
      {0,0,0,0,0,0,0,0},
      {0,0,0,1,1,0,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,1,0,1,1,0,0},
      {0,0,1,1,0,1,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,0,1,1,0,0,0},
      {0,0,0,0,0,0,0,0}
    };
  bool matriz1[8][8] ={
      {0,0,0,0,0,0,0,0},
      {0,0,0,0,1,0,0,0},
      {0,0,0,1,1,0,0,0},
      {0,0,1,0,1,0,0,0},
      {0,0,0,0,1,0,0,0},
      {0,0,0,0,1,0,0,0},
      {0,0,0,0,1,0,0,0},
      {0,0,0,0,0,0,0,0}
    };
  bool matriz2[8][8] ={
      {0,0,0,0,0,0,0,0},
      {0,0,0,1,1,0,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,0,0,0,1,0,0},
      {0,0,0,1,1,0,0,0},
      {0,0,1,0,0,0,0,0},
      {0,0,1,1,1,1,0,0},
      {0,0,0,0,0,0,0,0}
    };
  bool matriz3[8][8] ={
      {0,0,0,0,0,0,0,0},
      {0,0,0,1,1,0,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,0,0,1,0,0,0},
      {0,0,0,0,0,1,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,0,1,1,0,0,0},
      {0,0,0,0,0,0,0,0}
    };
  bool matriz4[8][8] ={
      {0,0,0,0,0,0,0,0},
      {0,0,0,0,1,1,0,0},
      {0,0,0,1,0,1,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,1,1,1,1,0,0},
      {0,0,0,0,0,1,0,0},
      {0,0,0,0,0,1,0,0},
      {0,0,0,0,0,0,0,0}
    };
  bool matriz5[8][8] ={
      {0,0,0,0,0,0,0,0},
      {0,0,1,1,1,1,0,0},
      {0,0,1,0,0,0,0,0},
      {0,0,1,1,1,0,0,0},
      {0,0,0,0,0,1,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,0,1,1,0,0,0},
      {0,0,0,0,0,0,0,0}
    };
  bool matriz6[8][8] ={
      {0,0,0,0,0,0,0,0},
      {0,0,0,1,1,0,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,1,0,0,0,0,0},
      {0,0,1,1,1,0,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,0,1,1,0,0,0},
      {0,0,0,0,0,0,0,0}
    };
  bool matriz7[8][8] ={
      {0,0,0,0,0,0,0,0},
      {0,0,1,1,1,1,0,0},
      {0,0,0,0,0,1,0,0},
      {0,0,0,0,1,0,0,0},
      {0,0,0,1,0,0,0,0},
      {0,0,1,0,0,0,0,0},
      {0,0,1,0,0,0,0,0},
      {0,0,0,0,0,0,0,0}
    };
  bool matriz8[8][8] ={
      {0,0,0,0,0,0,0,0},
      {0,0,0,1,1,0,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,0,1,1,0,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,0,1,1,0,0,0},
      {0,0,0,0,0,0,0,0}
    };
  bool matriz9[8][8] ={
      {0,0,0,0,0,0,0,0},
      {0,0,0,1,1,0,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,0,1,1,1,0,0},
      {0,0,0,0,0,1,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,0,1,1,0,0,0},
      {0,0,0,0,0,0,0,0}
    };
  bool matrizA[8][8] ={
      {0,0,0,0,0,0,0,0},
      {0,0,0,1,1,0,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,1,1,1,1,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,0,0,0,0,0,0}
    };
  bool matrizB[8][8] ={
      {0,0,0,0,0,0,0,0},
      {0,0,1,1,1,0,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,1,1,1,0,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,1,1,1,0,0,0},
      {0,0,0,0,0,0,0,0}
    };
  bool matrizC[8][8] ={
      {0,0,0,0,0,0,0,0},
      {0,0,0,1,1,0,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,1,0,0,0,0,0},
      {0,0,1,0,0,0,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,0,1,1,0,0,0},
      {0,0,0,0,0,0,0,0}
    };
  bool matrizD[8][8] ={
      {0,0,0,0,0,0,0,0},
      {0,0,1,1,1,0,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,1,1,1,0,0,0},
      {0,0,0,0,0,0,0,0}
    };
  bool matrizE[8][8] ={
      {0,0,0,0,0,0,0,0},
      {0,0,1,1,1,1,0,0},
      {0,0,1,0,0,0,0,0},
      {0,0,1,1,1,0,0,0},
      {0,0,1,0,0,0,0,0},
      {0,0,1,0,0,0,0,0},
      {0,0,1,1,1,1,0,0},
      {0,0,0,0,0,0,0,0}
    };
  bool matrizF[8][8] ={
      {0,0,0,0,0,0,0,0},
      {0,0,1,1,1,1,0,0},
      {0,0,1,0,0,0,0,0},
      {0,0,1,1,1,0,0,0},
      {0,0,1,0,0,0,0,0},
      {0,0,1,0,0,0,0,0},
      {0,0,1,0,0,0,0,0},
      {0,0,0,0,0,0,0,0}
    };
  bool matrizG[8][8] ={
      {0,0,0,0,0,0,0,0},
      {0,0,0,1,1,0,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,1,0,0,0,0,0},
      {0,0,1,0,1,1,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,0,1,1,0,0,0},
      {0,0,0,0,0,0,0,0}
    };
  bool matrizH[8][8] ={
      {0,0,0,0,0,0,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,1,1,1,1,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,0,0,0,0,0,0}
    };
  bool matrizI[8][8] ={
      {0,0,0,0,0,0,0,0},
      {0,0,0,1,1,1,0,0},
      {0,0,0,0,1,0,0,0},
      {0,0,0,0,1,0,0,0},
      {0,0,0,0,1,0,0,0},
      {0,0,0,0,1,0,0,0},
      {0,0,0,1,1,1,0,0},
      {0,0,0,0,0,0,0,0}
    };
  bool matrizJ[8][8] ={
      {0,0,0,0,0,0,0,0},
      {0,0,0,1,1,1,0,0},
      {0,0,0,0,0,1,0,0},
      {0,0,0,0,0,1,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,0,1,1,0,0,0},
      {0,0,0,0,0,0,0,0}
    };
  bool matrizK[8][8] ={
      {0,0,0,0,0,0,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,1,0,1,0,0,0},
      {0,0,1,1,0,0,0,0},
      {0,0,1,0,1,0,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,0,0,0,0,0,0}
    };
  bool matrizL[8][8] ={
      {0,0,0,0,0,0,0,0},
      {0,0,1,0,0,0,0,0},
      {0,0,1,0,0,0,0,0},
      {0,0,1,0,0,0,0,0},
      {0,0,1,0,0,0,0,0},
      {0,0,1,0,0,0,0,0},
      {0,0,1,1,1,1,0,0},
      {0,0,0,0,0,0,0,0}
    };
  bool matrizM[8][8] ={
      {0,0,0,0,0,0,0,0},
      {0,0,1,0,0,0,1,0},
      {0,0,1,1,0,1,1,0},
      {0,0,1,0,1,0,1,0},
      {0,0,1,0,0,0,1,0},
      {0,0,1,0,0,0,1,0},
      {0,0,1,0,0,0,1,0},
      {0,0,0,0,0,0,0,0}
    };
  bool matrizN[8][8] ={
      {0,0,0,0,0,0,0,0},
      {0,0,1,0,0,0,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,1,1,0,1,0,0},
      {0,0,1,0,1,1,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,0,0,0,0,0,0}
    };
  bool matrizO[8][8] ={
      {0,0,0,0,0,0,0,0},
      {0,0,0,1,1,0,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,0,1,1,0,0,0},
      {0,0,0,0,0,0,0,0}
    };
  bool matrizP[8][8] ={
      {0,0,0,0,0,0,0,0},
      {0,0,1,1,1,0,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,1,1,1,0,0,0},
      {0,0,1,0,0,0,0,0},
      {0,0,1,0,0,0,0,0},
      {0,0,0,0,0,0,0,0}
    };
  bool matrizQ[8][8] ={
      {0,0,0,0,0,0,0,0},
      {0,0,0,1,1,0,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,0,1,1,1,1,0},
      {0,0,0,0,0,0,0,0}
    };
  bool matrizR[8][8] ={
      {0,0,0,0,0,0,0,0},
      {0,0,1,1,1,0,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,1,1,1,0,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,0,0,0,0,0,0}
    };
  bool matrizS[8][8] ={
      {0,0,0,0,0,0,0,0},
      {0,0,0,1,1,0,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,0,1,0,0,0,0},
      {0,0,0,0,1,0,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,0,1,1,0,0,0},
      {0,0,0,0,0,0,0,0}
    };
  bool matrizT[8][8] ={
      {0,0,0,0,0,0,0,0},
      {0,0,1,1,1,1,1,0},
      {0,0,0,0,1,0,0,0},
      {0,0,0,0,1,0,0,0},
      {0,0,0,0,1,0,0,0},
      {0,0,0,0,1,0,0,0},
      {0,0,0,0,1,0,0,0},
      {0,0,0,0,0,0,0,0}
    };
  bool matrizU[8][8] ={
      {0,0,0,0,0,0,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,1,1,1,1,0,0},
      {0,0,0,0,0,0,0,0}
    };
  bool matrizV[8][8] ={
      {0,0,0,0,0,0,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,0,1,1,0,0,0},
      {0,0,0,0,0,0,0,0}
    };
  bool matrizW[8][8] ={
      {0,0,0,0,0,0,0,0},
      {0,0,1,0,0,0,1,0},
      {0,0,1,0,0,0,1,0},
      {0,0,1,0,0,0,1,0},
      {0,0,1,0,1,0,1,0},
      {0,0,1,0,1,0,1,0},
      {0,0,0,1,0,1,0,0},
      {0,0,0,0,0,0,0,0}
    };
  bool matrizX[8][8] ={
      {0,0,0,0,0,0,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,0,1,1,0,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,1,0,0,1,0,0},
      {0,0,0,0,0,0,0,0}
    };
  bool matrizY[8][8] ={
      {0,0,0,0,0,0,0,0},
      {0,0,1,0,0,0,1,0},
      {0,0,1,0,0,0,1,0},
      {0,0,0,1,0,1,0,0},
      {0,0,0,0,1,0,0,0},
      {0,0,0,0,1,0,0,0},
      {0,0,0,0,1,0,0,0},
      {0,0,0,0,0,0,0,0}
    };
  bool matrizZ[8][8] ={
      {0,0,0,0,0,0,0,0},
      {0,0,1,1,1,1,0,0},
      {0,0,0,0,0,1,0,0},
      {0,0,0,0,1,0,0,0},
      {0,0,0,1,0,0,0,0},
      {0,0,1,0,0,0,0,0},
      {0,0,1,1,1,1,0,0},
      {0,0,0,0,0,0,0,0}
    };

  if(carac == '0'){
    waaaa(matriz0);
  }
  if(carac == '1'){
    waaaa(matriz1);
  }
  if(carac == '2'){
    waaaa(matriz2);
  }
  if(carac == '3'){
    waaaa(matriz3);
  }
  if(carac == '4'){
    waaaa(matriz4);
  }
  if(carac == '5'){
    waaaa(matriz5);
  }
  if(carac == '6'){
    waaaa(matriz6);
  }
  if(carac == '7'){
    waaaa(matriz7);
  }
  if(carac == '8'){
    waaaa(matriz8);
  }
  if(carac == '9'){
    waaaa(matriz9);
  }
  if(carac == 'A'){
    waaaa(matrizA);
  }
  if(carac == 'B'){
    waaaa(matrizB);
  }
  if(carac == 'C'){
    waaaa(matrizC);
  }
  if(carac == 'D'){
    waaaa(matrizD);
  }
  if(carac == 'E'){
    waaaa(matrizE);
  }
  if(carac == 'F'){
    waaaa(matrizF);
  }
  if(carac == 'G'){
    waaaa(matrizG);
  }
  if(carac == 'H'){
    waaaa(matrizH);
  }
  if(carac == 'I'){
    waaaa(matrizI);
  }
  if(carac == 'J'){
    waaaa(matrizJ);
  }
  if(carac == 'K'){
    waaaa(matrizK);
  }
  if(carac == 'L'){
    waaaa(matrizL);
  }
  if(carac == 'M'){
    waaaa(matrizM);
  }
  if(carac == 'N'){
    waaaa(matrizN);
  }
  if(carac == 'O'){
    waaaa(matrizO);
  }
  if(carac == 'P'){
    waaaa(matrizP);
  }
  if(carac == 'Q'){
    waaaa(matrizQ);
  }
  if(carac == 'R'){
    waaaa(matrizR);
  }
  if(carac == 'S'){
    waaaa(matrizS);
  }
  if(carac == 'T'){
    waaaa(matrizT);
  }
  if(carac == 'U'){
    waaaa(matrizU);
  }
  if(carac == 'V'){
    waaaa(matrizV);
  }
  if(carac == 'W'){
    waaaa(matrizW);
  }
  if(carac == 'X'){
    waaaa(matrizX);
  }
  if(carac == 'Y'){
    waaaa(matrizY);
  }
  if(carac == 'Z'){
    waaaa(matrizZ);
  }
  
}

void waaaa(bool mat[8][8]){
  for(int i=0; i<8; i++) {
      for(int j=0; j<8; j++) {
        lc.setLed(0, i, j, mat[i][j]);
      }
    }
}
