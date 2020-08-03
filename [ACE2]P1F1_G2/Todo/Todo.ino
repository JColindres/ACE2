#include <Wire.h>
#include <BH1750.h>
#include <HX711.h>
#include <ADXL345.h>
#include "alo.h"
#include "Adafruit_GFX.h"
#include "Adafruit_TFTLCD.h"
#include "TouchScreen.h"
#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>
#include <SoftwareSerial.h>
alo accelerometro;

SoftwareSerial Arduino(11, 10);

#define Pin_RD A0
#define Pin_WR A1
#define Pin_CD A2
#define Pin_CS A3
#define Pin_RESET A4

#define XM A2
#define YP A3
#define YM 9
#define XP 8

#define minX 150
#define maxX 930
#define minY 120
#define maxY 940

Adafruit_TFTLCD pantalla(Pin_CS, Pin_CD, Pin_WR, Pin_RD, Pin_RESET);
TouchScreen touch = TouchScreen(XP, YP, XM, YM, 300);

#define Rojo 0xF800
#define Negro 0x0000
#define Azul 0x001F
#define Blanco 0xFFFF
#define Gris 0x7BEF
#define Cyan 0x07FF
#define Rosa 0xF81F

#define minPres 100
#define maxPres 1000

TSPoint punto;
int colorActual, colorViejo, yxcont = 0;
char RGB [95][160];
char color = '0';
String cadena = "";
boolean cont1 = false, cont2 = false, act = false;
boolean paso1 = false, paso2 = false, paso3 = false;


ADXL345 adxl; //variable adxl is an instance of the ADXL345 library

float rollF = 0, pitchF = 0;
float pasos = 0, pasosAnt = 0;
bool modoAntiRobo = false;
bool reposo = true;
bool ActivarTFT = false;
bool ModoZipper = false;
int Infra = 23;

HX711 scale(45, 47);

float calibration_factor = 45200;
float units = 5.0;

BH1750 Luxometro;

int pinMicro = 8;//8
int valorSensor = 0;
int limite = 540;
int valorAbsoluto = 0;
int sonido = 0;

int pinLluvia = 22;//22
int lluvia = 1;
String kkseca = "0/0/1";
uint16_t luz = 0;
const int PulseWire = A9;
int Threshold = 550;
int xigual = 0, xcont = 0, xcam = 0;
PulseSensorPlayground pulseSensor;

void setup() {
  Serial.begin(9600);
  Arduino.begin(4800);
  pantalla.reset();
  pantalla.begin(0x9341);

  pantalla.fillScreen(Blanco);


  pantalla.fillRect(25, 50, 50, 40, Cyan);
  pantalla.fillRect(100, 50, 50, 40, Cyan);
  pantalla.fillRect(175, 50, 50, 40, Cyan);
  pantalla.fillRect(25, 130, 50, 40, Cyan);
  pantalla.fillRect(100, 130, 50, 40, Cyan);
  pantalla.fillRect(175, 130, 50, 40, Cyan);
  pantalla.fillRect(25, 210, 50, 40, Cyan);
  pantalla.fillRect(100, 210, 50, 40, Cyan);
  pantalla.fillRect(175, 210, 50, 40, Cyan);

  colorActual = Negro;
  pinMode(24, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(13, OUTPUT);

  accelerometro.init();
  pinMode(Infra, INPUT);
  Wire.begin();
  Luxometro.begin(BH1750::CONTINUOUS_HIGH_RES_MODE);

  scale.set_scale();
  scale.tare(10);

  pulseSensor.analogInput(PulseWire);
  pulseSensor.setThreshold(Threshold);


  if (pulseSensor.begin()) {

  }
}
unsigned long TIME = 0;
int periodo = 60000;
void loop() {
  digitalWrite(13, HIGH);
  punto = touch.getPoint();
  digitalWrite(13, LOW);

  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  accelerometro.stepCalc();
  pasosAnt = pasos;
  pasos = accelerometro.stepCount;

  if (Serial.available() > 0)
  {
    char llega = Serial.read();
    if (llega == 'A') {
      modoAntiRobo = true;
    } else if (llega == 'B') {
      digitalWrite(24, LOW);
      modoAntiRobo = false;
      ModoZipper = false;
      reposo = false;
      noTone(28);
    }
  }

  if (pasosAnt != pasos && modoAntiRobo == false )
  {

    reposo = false; //si no esta en reposo, entonces al abrir el zipper tendra que sonar
  } else {
    noTone(28);
    reposo = true;
  }

  if (modoAntiRobo == true) //Aqui detecta si esta en reposo o no
  {
    int x, y, z;
    adxl.readXYZ(&x, &y, &z);

    byte interrupts = adxl.getInterruptSource();
    if (adxl.triggered(interrupts, ADXL345_INACTIVITY))
    {
      reposo = true; //si esta en reposo, entonces al moverlo tendra que sonar
      noTone(28);
    }
    else if (pasosAnt != pasos)
    {
      ActivarTFT = true;
    }
  }
  if (modoAntiRobo == false && reposo == false) //modo sin seguridad
  {
    digitalWrite(24, LOW);

    //ModoZipper=true;
    if (digitalRead(Infra) == HIGH)
    {
      //sonar la puta alarma
      tone(28, 277);
      ///ModoZipper=true;
      //Serial.println("te la estan abriendo gilipollas");
    } else {
      //ModoZipper=false;
      noTone(28);
    }

    accelerometro.inclinacion();

    // Low-pass filter
    rollF = 0.94 * rollF + 0.06 * accelerometro.roll;
    pitchF = 0.94 * pitchF + 0.06 * accelerometro.pitch;
    kkseca = (String)pasos + "/" + (String)rollF + "/" + (String)pitchF;

  }
  else if ((modoAntiRobo == true && reposo == true ) || (ActivarTFT == true )) //modo por si se la intentan llevar
  {
    digitalWrite(24, LOW);
    ModoZipper = true;
    while (true) {
      if (digitalRead(Infra) == HIGH)
      {
        //sonar la puta alarma
        tone(28, 277);
        ModoZipper = true;
        // Serial.println("te la estan abriendo gilipollas");
      } else {
        //ModoZipper=false;
        noTone(28);
        break;
      }
    }
    digitalWrite(24, HIGH);
    digitalWrite(25, LOW);
    /*if(ModoZipper==true){
      reposo=false;
      }*/
    while (ActivarTFT == true) {
      if (ActivarTFT == true)
      {
        //digitalWrite(25, HIGH);
        //tone(28,277);

        if (punto.z > minPres && punto.z < maxPres) {
          act = true;
          punto.x = map(punto.x, minX, maxX, pantalla.width(), 0);
          punto.y = map(punto.y, minY, maxY, pantalla.height(), 0);

          if (punto.x > 175 && punto.x < 225) {
            colorViejo = colorActual;
            if (punto.y > 210 && punto.y < 250 ) {
              pantalla.drawRect(175, 210, 50, 40, Rosa);
              cont1 = true;
            }
            if (punto.y > 130 && punto.y < 170 ) {
              pantalla.drawRect(175, 130, 50, 40, Rosa);

            }
            if (punto.y > 50 && punto.y < 90 ) {
              pantalla.drawRect(175, 50, 50, 40, Rosa);

            }
          }
          if (punto.x > 25 && punto.x < 75) {
            colorViejo = colorActual;
            if (punto.y > 50 && punto.y < 90 ) {
              pantalla.drawRect(25, 50, 50, 40, Rosa);
              cont2 = true;
            }
            if (punto.y > 130 && punto.y < 170 ) {
              pantalla.drawRect(25, 130, 50, 40, Rosa);
              paso2 = true;
            }
            if (punto.y > 210 && punto.y < 250 ) {
              pantalla.drawRect(25, 210, 50, 40, Rosa);
              paso1 = true;
            }
          }
          if (punto.x > 100 && punto.x < 150) {
            colorViejo = colorActual;
            if (punto.y > 50 && punto.y < 90 ) {
              pantalla.drawRect(100, 50, 50, 40, Rosa);

            }
            if (punto.y > 130 && punto.y < 170 ) {
              pantalla.drawRect(100, 130, 50, 40, Rosa);
              paso3 = true;
            }
            if (punto.y > 210 && punto.y < 250 ) {
              pantalla.drawRect(100, 210, 50, 40, Rosa);

            }
          }



          if (punto.x > 100) {
            colorViejo = colorActual;

            if (punto.y < 40) {
              //pantalla.fillRect(0, 0, 95, 160, Blanco);
              //cerotiador();
            } else if (punto.y < 80) {
              colorActual = Negro;
              color = '1';
              //  pantalla.drawRect(100, 40, 145, 40, Rosa);
            } else if (punto.y < 120) {
              //  colorActual = Rojo;
              color = '2';
              //  pantalla.drawRect(100, 80, 145, 40, Rosa);
            } else if (punto.y < 160) {
              // colorActual = Azul;
              color = '2';
              //  pantalla.drawRect(100, 120, 145, 40, Rosa);
            } else if (punto.y < 200) {
              //  colorActual = Blanco;
              color = '0';
              //   pantalla.drawRect(100, 160, 145, 40, Rosa);
            } else if (punto.y < 240) {

            }

            if (colorViejo != colorActual) {
              /*  if(colorViejo == Negro) pantalla.fillRect(100, 40, 145, 40, Negro);
                if(colorViejo == Rojo) pantalla.fillRect(100, 80, 145, 40, Rojo);
                if(colorViejo == Azul) pantalla.fillRect(100, 120, 145, 40, Azul);
                if(colorViejo == Blanco) pantalla.fillRect(100, 160, 145, 40, Blanco);*/
            }

          }

          if ((punto.x > -1 && punto.x < 250) && (punto.y > -1 && punto.y < 350)) {
            pantalla.fillCircle(punto.x, punto.y, 3, colorActual);
            RGB[punto.x][punto.y] = color;
          }

        }
        if (act == true && cont1 == true && cont2 == true) {
          cont1 = false;
          cont2 = false;
          act = false;
          pantalla.fillScreen(Blanco);
          Serial.println("ad");
          ActivarTFT = false;
          reposo = false;
          modoAntiRobo = false;
          noTone(28);
          pantalla.fillRect(25, 50, 50, 40, Cyan);
          pantalla.fillRect(100, 50, 50, 40, Cyan);
          pantalla.fillRect(175, 50, 50, 40, Cyan);
          pantalla.fillRect(25, 130, 50, 40, Cyan);
          pantalla.fillRect(100, 130, 50, 40, Cyan);
          pantalla.fillRect(175, 130, 50, 40, Cyan);
          pantalla.fillRect(25, 210, 50, 40, Cyan);
          pantalla.fillRect(100, 210, 50, 40, Cyan);
          pantalla.fillRect(175, 210, 50, 40, Cyan);
        }
        if (act == true && paso1 == true && paso2 == true && paso3 == true) {
          cont1 = false;
          cont2 = false;
          act = false;
          paso1 = false;
          paso2 = false;
          paso3 = false;
          pantalla.fillScreen(Blanco);


          pantalla.fillRect(25, 50, 50, 40, Cyan);
          pantalla.fillRect(100, 50, 50, 40, Cyan);
          pantalla.fillRect(175, 50, 50, 40, Cyan);
          pantalla.fillRect(25, 130, 50, 40, Cyan);
          pantalla.fillRect(100, 130, 50, 40, Cyan);
          pantalla.fillRect(175, 130, 50, 40, Cyan);
          pantalla.fillRect(25, 210, 50, 40, Cyan);
          pantalla.fillRect(100, 210, 50, 40, Cyan);
          pantalla.fillRect(175, 210, 50, 40, Cyan);
        }
      }
    }
  }
  if (ActivarTFT == false) {
    luz = Luxometro.readLightLevel();

    valorSensor = analogRead(pinMicro);
    valorAbsoluto = abs(valorSensor - limite);
    sonido  = map(valorAbsoluto, 0, 20, 55, 100);

    lluvia = digitalRead(pinLluvia);

    scale.set_scale(calibration_factor);

    units = scale.get_units(), 10;
    if (units < 0) {
      units = 0.00;
    }
    int myBPM = sonido;

    if (xcont == 0) {
      xigual = myBPM;
      xcam = myBPM;
      xcont = 1;
    } else if (xcont == 1) {
      if (xigual == myBPM) {
        xcont = 2;
      } else {
        xcont = 0;
        xcam = myBPM;
      }
    } else if (xcont == 2) {
      if (xigual == myBPM) {
        xcam = 0;
      } else {
        xcont = 0;
        xcam = myBPM;
      }
    }
    if (yxcont == 0) {
      xcam = 0;
      yxcont = 1;
    } else {
      yxcont = 0;
    }
    String datos = (String)units + "/" + (String)luz + "/" + (String)sonido + "/" + (String)lluvia + "/" +  kkseca + "/" + (String)(sonido-48);
    Serial.println(datos);
    Arduino.println(datos);
    delay(10000);
  }
}
