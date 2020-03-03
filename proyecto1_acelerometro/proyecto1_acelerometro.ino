#include <Wire.h>
#include <ADXL345.h>
#include "alo.h"

alo accelerometro;

ADXL345 adxl; //variable adxl is an instance of the ADXL345 library

float rollF, pitchF = 0;
float pasos, pasosAnt = 0;
bool modoAntiRobo = false;
bool reposo = false;
int Infra = 8;

void setup() {
  Serial.begin(9600);
  accelerometro.init();
  pinMode(Infra, INPUT);
}

void loop() {

  accelerometro.stepCalc();
  pasosAnt = pasos;
  pasos = accelerometro.stepCount;

  if(Serial.available() > 0)
  {
    reposo = Serial.read();
  }
  
  if (modoAntiRobo == true) //Aqui detecta si esta en reposo o no
  {
    int x, y, z;
    adxl.readXYZ(&x, &y, &z);

    byte interrupts = adxl.getInterruptSource();
    if (adxl.triggered(interrupts, ADXL345_INACTIVITY))
    {
      reposo = true; //si esta en reposo, entonces al moverlo tendra que sonar
    }
    else if(pasosAnt != pasos)
    {
      reposo = false; //si no esta en reposo, entonces al abrir el zipper tendra que sonar
    }
  }
  if (modoAntiRobo == true && reposo == false) //modo zipper
  {
    if (digitalRead(Infra) == HIGH)
    {
      //sonar la puta alarma
      Serial.println("te la estan abriendo gilipollas");
    }
    accelerometro.inclinacion();

    // Low-pass filter
    rollF = 0.94 * rollF + 0.06 * accelerometro.roll;
    pitchF = 0.94 * pitchF + 0.06 * accelerometro.pitch;

    Serial.print(pasos);
    Serial.print("/");
    Serial.print(rollF);
    Serial.print("/");
    Serial.println(pitchF);
  }
  else if (modoAntiRobo == false && reposo == false) //modo sin seguridad
  {
    accelerometro.inclinacion();

    // Low-pass filter
    rollF = 0.94 * rollF + 0.06 * accelerometro.roll;
    pitchF = 0.94 * pitchF + 0.06 * accelerometro.pitch;

    Serial.print(pasos);
    Serial.print("/");
    Serial.print(rollF);
    Serial.print("/");
    Serial.println(pitchF);
  }
  else if(modoAntiRobo == true && reposo == true) //modo por si se la intentan llevar
  {
    if(pasosAnt != pasos)
    {
      //sonar la puta alarma... ya sea bad bunny o gmi.2
    }
  }
}
