
#define NOTA 784
#define APRETADO    0
#define SUELTO      1
#define APRETANDOLO 2
#define SOLTANDOLO  3

int  melodyPin = 4;
const int boton = 2; // Botón asignado en el pin 2.
int   anterior;      // guardamos el estado anterior.
int   valor;         // valor actual del botón.
int   estado;        // el estado del botón.
unsigned long tiempopresionado = 0;
unsigned long tiemposuelto = 0;
unsigned long temporizador;
unsigned long tiemporebote = 50;
String concatenar;

char mensaje[10];
int indiceLetra = 0;

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

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(4, OUTPUT);//buzzer
  pinMode(8, OUTPUT);
  
  pinMode(boton,INPUT_PULLUP);
  pinMode(13,OUTPUT); // Vamos a usar el led de la placa como señalización.
  estado = HIGH;
  anterior = HIGH;
}

void loop() {
  
  // Si el estado es igual a lo leido, la entrada no ha cambiado lo que
  // significa que no hemos apretado el botón (ni lo hemos soltado); asi que
  // tenemos que parar el temporizador.
  if ( valor==digitalRead(2) ) {
    temporizador = 0;
  }
  // Si el valor distinto significa que hemos pulsado/soltado el botón. Ahora
  // tendremos que comprobar el estado del temporizador, si vale 0, significa que
  // no hemos guardado el tiempo en el que sa ha producido el cambio, así que
  // hemos de guardarlo.
  else
  if ( temporizador == 0 ) {
    // El temporizador no está iniciado, así que hay que guardar
    // el valor de millis en él.
    temporizador = millis();
  }
  else
  // El temporizador está iniciado, hemos de comprobar si el
  // el tiempo que deseamos de rebote ha pasado.
  if ( millis()-temporizador > tiemporebote ) {
    // Si el tiempo ha pasado significa que el estado es lo contrario
    // de lo que había, asi pues, lo cambiamos.
    valor = !valor;
  }

  // Ahora comprobamos el estado. Recordad que si el boton vale "1" estará suelto,
  // "0" y el botón estará apretado. Si pasa de "1" a "0" es que lo estamos aprentando
  // y si es al contrario es que lo estamos soltando.
  if ( anterior==LOW  && valor==LOW  ) {estado = APRETADO; tiempopresionado++;}
  if ( anterior==LOW  && valor==HIGH ) {estado = SOLTANDOLO;}
  if ( anterior==HIGH && valor==LOW  ) {estado = APRETANDOLO;}
  if ( anterior==HIGH && valor==HIGH ) {estado = SUELTO; tiempopresionado = 0; tiemposuelto++;}

  // Recuerda que hay que guardar el estado anterior.
  anterior = valor;

  // Ahora vamos a ver que podemos hacer con el estado.
  switch ( estado ) {
    case SUELTO:   
      digitalWrite(13,LOW); 
      noTone(4);
      if(tiemposuelto == 100000){
        //Serial.println(concatenar);
        MorseAscii(concatenar);
        concatenar = "";
      } 
      break; // Apagamos el led.
    case APRETANDOLO: 
      //Serial.print("Has apretado el botón\n"); 
      break; // Mandamos un mensaje.
    case APRETADO: 
      digitalWrite(13,HIGH); 
      tone(4,NOTA,200); 
      break; // Encendemos el led.
    case SOLTANDOLO: 
      tiemposuelto = 0; 
      //Serial.print("Has soltado el botón\n"); 
      //Serial.print(tiempopresionado); 
      //Serial.print("\n"); 
      if(tiempopresionado > 1000 && tiempopresionado < 20000){
        concatenar += ".";
      }else if(tiempopresionado > 20000){
        concatenar += "-";
      }
      break; // Mandamos un mensaje.
    default: break;
  }

  /*
  //numeros del 0 al 9
  sing(48);
  sing(49);
  sing(50);
  sing(51);
  sing(52);
  sing(53);
  sing(54);
  sing(55);
  sing(56);
  sing(57);
  //letras de la A a la Z
  sing(65);
  sing(66);
  sing(67);
  sing(68);
  sing(69);
  sing(70);
  sing(71);
  sing(72);
  sing(73);
  sing(74);
  sing(75);
  sing(76);
  sing(77);
  sing(78);
  sing(79);
  sing(80);
  sing(81);
  sing(82);
  sing(83);
  sing(84);
  sing(85);
  sing(86);
  sing(87);
  sing(88);
  sing(89);
  sing(90);*/
}

int song = 0;

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
    indiceLetra = 0;
  }
}

void sing(int s) {
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

      buzz(melodyPin, cero[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

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

      buzz(melodyPin, uno[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

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

      buzz(melodyPin, dos[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

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

      buzz(melodyPin, tres[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

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

      buzz(melodyPin, cuatro[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

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

      buzz(melodyPin, cinco[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

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

      buzz(melodyPin, seis[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

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

      buzz(melodyPin, siete[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

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

      buzz(melodyPin, ocho[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

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

      buzz(melodyPin, nueve[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

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

      buzz(melodyPin, a[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

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

      buzz(melodyPin, b[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

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

      buzz(melodyPin, c[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

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

      buzz(melodyPin, d[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

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

      buzz(melodyPin, e[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

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

      buzz(melodyPin, f[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

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

      buzz(melodyPin, g[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

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

      buzz(melodyPin, h[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

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

      buzz(melodyPin, i[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

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

      buzz(melodyPin, j[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

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

      buzz(melodyPin, k[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

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

      buzz(melodyPin, l[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

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

      buzz(melodyPin, m[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

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

      buzz(melodyPin, n[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

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

      buzz(melodyPin, o[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

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

      buzz(melodyPin, p[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

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

      buzz(melodyPin, q[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

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

      buzz(melodyPin, r[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

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

      buzz(melodyPin, ese[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

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

      buzz(melodyPin, t[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

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

      buzz(melodyPin, u[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

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

      buzz(melodyPin, v[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

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

      buzz(melodyPin, w[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

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

      buzz(melodyPin, x[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

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

      buzz(melodyPin, y[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

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

      buzz(melodyPin, z[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = (1000 / 4) * 1.50;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

    }
  }
  delay(1000);
}

void buzz(int targetPin, long frequency, long length) {
  digitalWrite(8, HIGH);
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
  digitalWrite(8, LOW);

}
