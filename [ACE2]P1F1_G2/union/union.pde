ChildApplet child;
ChildAppletSG winSonido;
ChildAppletGota winAgua;
ChildAppletpas winkk;
ChildAppletInc winInc;
ChildAppletcor wincor;

import processing.serial.*;
import java.awt.event.KeyEvent;
import java.io.IOException;
String data="";
float pasos,roll, pitch;
PImage imgBoton;
String info="0.00";
PFont f;
PFont F;
Serial myPort;        
int xPos = 40;  
boolean boton = false;
color apagado = color(255, 0, 0);
color encendido = color(0, 255, 0);

int anchoSG = 1400, altoSG = 650;
int luz = 0, sonido = 0;
int contDatos = 1;
int xSAn = 60, ySAn = 590, xSAc = 60, ySAc = 0;
int xLAn = 760, yLAn = 590, xLAc = 760, yLAc = 0;

PImage imgGota1, imgGota2, pasosIMG;
PImage colum0, colum15, colum30, colum45, colum60;
int agua = 1;
 
 
int ancho = 1100;
int alto = 400;

int val,shul;                        
long valTime;                  
int[] valores;
float voltaje;
PFont J;
 
void settings() {
  size(400, 400);
  smooth();
}

void setup() {
  child = new ChildApplet();
  winSonido = new ChildAppletSG();
  winAgua = new ChildAppletGota();
  winkk =new ChildAppletpas();
  
  wincor=new ChildAppletcor();
  winInc =new ChildAppletInc();
  surface.setTitle("Antirrobo");
  imgBoton = loadImage("boton.png");
  imgGota1 = loadImage("gota1.png");
  pasosIMG = loadImage("pasos.png");
  colum0 = loadImage("columna0.png");
  colum15 = loadImage("columna15.png");
  colum30 = loadImage("columna30.png");
  colum45 = loadImage("columna45.png");
  colum60 = loadImage("columna60.png");
  F = createFont("Arial",24,true);
  println(Serial.list());
  myPort = new Serial(this, Serial.list()[0], 9600);
  
   
}

void draw() {
  String cadena = myPort.readStringUntil('\n');
 
  if(cadena != null) {
    cadena = trim(cadena);
    if(cadena.equals("ad")){
      boton=false;
    }else{
    String[] datos = cadena.split("/");
    info = datos[0];
    luz = Integer.parseInt(datos[1]);
    sonido = Integer.parseInt(datos[2]);
    agua = Integer.parseInt(datos[3]);
     
     
     pasos = float(datos[4]);
     roll = float(datos[5]);
     pitch = float(datos[6]);
     shul=Integer.parseInt(datos[7]);
    }
  }
  background(255, 255, 255);
  if(boton) {
    fill(encendido);
  } else {
    fill(apagado); 
  }
  
  ellipse(200, 175, 300, 300);
  image(imgBoton,75,50);
  textFont(F);
  text("ANTIRROBO", 130, 360);
}

void mouseClicked() {
  float pos = dist(200, 175, mouseX, mouseY);
  
  if(pos<150) {
    if(boton) {
      myPort.write('B');
      boton=false;
    } else {
      myPort.write('A');
      boton=true;
    }
  }
}



class ChildAppletcor extends PApplet {
  
  public ChildAppletcor() {
    super();
    PApplet.runSketch(new String[]{this.getClass().getName()}, this);
  }

  public void settings() {
      size(1280, 480);
    valores = new int[ancho];
    smooth();
 
  
  }
  
  public void setup() { 
    J = createFont("Arial", 16, true);
  }
int getvalor() {
  int valor = 0;
  
   
  valor = shul;   
     
 
  return valor;
} 

int getY(int val) {
  return (int)(alto/2 -(val-512) / 1023.0f * (alto - 1));
}


void pushvalor(int valor) {
  for (int i=0; i<ancho-1; i++)
    valores[i] = valores[i+1];
  valores[ancho-1] = valor;
}



void GarficaLinea() {
  int x0 = 0, x1 = 0, y0 = 0, y1 = 0;
  stroke(0,0,255);
    for (int i=0; i<ancho; i++) {
    x1 = round(ancho - ((ancho-i) * 2) );
    y1 = getY(valores[i]);
    if(i > 1)
      line(x0, y0, x1, y1);
    x0 = x1;
    y0 = y1;
  }
}
  public void draw() {
    int pFive = getY(1023);
  int zero  = getY(0);
  background(203, 203, 203);  
 
  fill(255);
  rectMode(CORNERS);
  noStroke();
  rect(0, 0, 1100, 400);//blanco
  
  textFont(J, 18);
  fill(255, 0, 0);
  text("85", 5, pFive+12);
  text("60", 5, zero-4);
  
  val = getvalor();
  valTime = System.nanoTime();
  pushvalor(val);
 
  textFont(J, 16);
  fill(204, 102, 0);
  voltaje = 5.0* val / 1023;
  text("BPM: ", 1130, 80);
  text(nfc(shul , 1),1200, 80);
  textFont(J, 16);
  fill(227, 37, 26);
  text("Pulso", 500, 30);
  GarficaLinea();
  }
}





class ChildApplet extends PApplet {
  
  public ChildApplet() {
    super();
    PApplet.runSketch(new String[]{this.getClass().getName()}, this);
  }

  public void settings() {
    size(700, 600); 
    smooth();
  }
  
  public void setup() { 
    f = createFont("Arial",12,true);
    F = createFont("Arial",24,true);
    surface.setTitle("Sensor de Peso");
    background(0);
  }

  public void draw() {
    int y = year(); 
    int m = month(); 
    int d = day(); 
    fill(255,0,0);
    textFont(F);       
    fill(255,0,0);
    textAlign(LEFT);
    text(d + "/" + m + "/" + y, 300, 25);
    int s = second(); 
    int mi = minute(); 
    int h = hour(); 
 
 
    float puntos = float(info+(char)6); 
    puntos = map(puntos, 0,117, 0, height*2);
    //println(puntos);
 
    stroke(175);                      
    line(40,height-40,40,40);
    
    stroke(175);                        
    line(40,height-40,width-40,height-40);
    
    stroke(100,100,255);                          //  
    line(40,height-194,width,height-194);
   
    stroke(100,100,255);                          //  
    line(40,height-344,width,height-344);
    
    stroke(100,100,255);                          //  
    line(40,height-244,width,height-244);
   
    stroke(100,100,255);                            
    line(40,height-294,width,height-294);
     
    stroke(100,100,255);                            
    line(40,height-144,width,height-144);
   
    stroke(100,100,255);                           
    line(40,height-394,width,height-394);
    
    stroke(100,100,255);                            
    line(40,height-94,width,height-94);
    
    stroke(100,100,255);                            
    line(40,height-394,width,height-394);
    
    stroke(100,100,255);                            
    line(40,height-444,width,height-444);
    
    stroke(100,100,255);                            
    line(40,height-494,width,height-494);
   
    textFont(F);       
    fill(255);
    
    textAlign(RIGHT);
    text("PESO",70,40);                         
    
    textAlign(RIGHT);
    text("HORA --->",590,580);    
   
    fill(0);
    stroke(255);   
    
    for(int j=680;j>600;j--) {
      line(j,height-550,j,height-585);
    }
    
    stroke(0,0,0);
    textAlign(RIGHT);
    text(info,680,40); 
    stroke(0,0,0);  
    
    for(int j=700;j>600;j--) {
      line(j,height-10,j,height-39);
    }
    
    stroke(255,0,0);
    textAlign(LEFT);
    fill(255,0,0);
    text(h + ":"+ mi + ":" + s,610,580);
    fill(240);
    textFont(f); 
 
    textAlign(RIGHT);
    text("(Kg)",110,40); 
    
    textAlign(RIGHT);                 
    text("50 -",40,60);
    
    textAlign(RIGHT);                
    text("45 -",40,110);
    
    textAlign(RIGHT);               
    text("40 -",40,160);
    
    textAlign(RIGHT);                
    text("35 -",40,210);
    
    textAlign(RIGHT);                
    text("30 -",40,260);
    
    textAlign(RIGHT);            
    text("25 -",40,310);
    
    textAlign(RIGHT);                 
    text("20 -",40,360);
    
    textAlign(RIGHT);
    text("15 -",40,410);
    
    textAlign(RIGHT);
    text("10 -",40,460);
    
    textAlign(RIGHT);
    text("5 -",40,510);
    
    textAlign(RIGHT);
    text("0 -",40,560);

    int inicial=40;            
    stroke(255,0,0);   
    
    for(int i=0;i<1;i++) {
      line(xPos, height-puntos-(inicial+5), xPos, height-puntos-inicial);
      xPos++;
    }
    
    if (xPos >= width) {
      xPos = 40;
      background(0);
    } 
  }
}

class ChildAppletSG extends PApplet {
  
  public ChildAppletSG() {
    super();
    PApplet.runSketch(new String[]{this.getClass().getName()}, this);
  }

  public void settings() {
    size(anchoSG, altoSG);
    smooth();
  }
  
  public void setup() { 
    f = createFont("Arial", 20, true);
    F = createFont("Arial", 24, true);
    surface.setTitle("Sensor de Sonido y Luminocidad");
    background(255);
    
    textFont(f);
    fill(255, 0, 0);
    text("SONIDO (dB) : ", 20, 30);
    cuadriculaSonido();
    
    strokeWeight(4);
    stroke(150);
    line(700, 20, 700, 630);
    
    fill(0, 0, 255);
    text("LUMINOCIDAD (lm) : ", 720, 30);
    cuadriculaLuz();
    
  }
  
  public void draw() {
    fill(255);
    noStroke();
    rect(0, 0, 200, 40);
      
    fill(255, 0, 0);
    text("SONIDO (dB) : " + sonido, 20, 30);
    
    if(contDatos%50 == 0){
      dibujarSonido();
    }
    
    fill(255);
    noStroke();
    rect(705, 0, 300, 40);
      
    fill(0, 0, 255);
    text("LUMINOCIDAD (lml) : " + luz, 720, 30);
    
    if(contDatos%50 == 0){
      dibujarLuz();
    }
    
    if(contDatos == 1100){
      borrarCuadriculasSG();
      cuadriculaSonido();
      cuadriculaLuz();
      contDatos = 0;
      xSAn = 60;
      xSAc = 60;
      xLAn = 760;
      xLAc = 760;
    }else{
      contDatos++;
    }
  }
  
  
  void cuadriculaSonido(){
    int db = 10;
    fill(0);
    
    strokeWeight(4);
    stroke(0);
    line(60, 60, 60, 590);
    line(60, 590, 640, 590);
    
    strokeWeight(1);
    stroke(200);
    for(int i = 110; i <= 640; i+=50) {
      line(i, 60, i, 590);
    }
    
    for(int i = 540; i >= 60; i-=50){
      line(60, i, 640, i);
      text(db, 20, (i+10));
      db+=10;
    }
  }
  
  void cuadriculaLuz(){
    int luz = 500;
    fill(0);
    
    strokeWeight(4);
    stroke(0);
    line(770, 60, 770, 590);
    line(770, 590, 1340, 590);
    
    strokeWeight(1);
    stroke(200);
    for(int i = 820; i <= 1340; i+=50) {
      line(i, 60, i, 590);
    }
    
    for(int i = 540; i >= 60; i-=50){
      line(770, i, 1340, i);
      text(luz, 720, (i+10));
      luz+=500;
    }
  }
  
  void dibujarSonido(){
    if(sonido < 0) {
      sonido = 0;
    } else if(sonido > 100) {
      sonido = 100;
    }
    
    xSAc+=25;
    ySAc = 590-(5*sonido);
    
    ellipse(xSAc, ySAc, 8, 8);
    stroke(50);
    line(xSAn, ySAn, xSAc, ySAc);
    
    xSAn = xSAc;
    ySAn = ySAc;
  }
  
  void dibujarLuz(){
    if(luz < 0) {
      luz = 0;
    } else if(luz > 5000) {
      luz = 5000;
    }
    
    xLAc+=25;
    yLAc = (int)(590-(0.1*luz));
    
    ellipse(xLAc, yLAc, 8, 8);
    stroke(50);
    line(xLAn, yLAn, xLAc, yLAc);
    
    xLAn = xLAc;
    yLAn = yLAc;
  }
  
  void borrarCuadriculasSG() {
    fill(255);
    noStroke();
    rect(5, 48, 650, 550);
    rect(705, 48, 650, 550);
  }
}

class ChildAppletGota extends PApplet {
  
  public ChildAppletGota() {
    super();
    PApplet.runSketch(new String[]{this.getClass().getName()}, this);
  }

  public void settings() {
    size(200, 400);
    smooth();
  }
  
  public void setup() { 
    f = createFont("Arial", 12, true);
    F = createFont("Arial", 24, true);
    
    surface.setTitle("Sensor de Agua");
    
    background(255);
    
  }
  
  public void draw() {
    
    fill(255);
    noStroke();
    rect(0, 0,  499, 849);
      
    if(agua == 1) {
      tint(255, 10);
      image(imgGota1, 1, 1, 200, 300);
    } else {
      tint(255, 255);
      image(imgGota1, 1, 1, 200, 300);
      fill(0, 170, 228);
      textFont(f);
      text("AGUA DETECTADA", 10, 320);
    }
    //println(agua); 
  }
}
class ChildAppletpas extends PApplet {
  
  public ChildAppletpas() {
    super();
    PApplet.runSketch(new String[]{this.getClass().getName()}, this);
  }

  public void settings() {
    size (1050, 625); 
    smooth();
  }
  
  public void setup() { 
    
    
    background(50); 
   
    
    fill(255); 
    textSize(40); 
    text("Contador de pasos", 250, 75);
    textSize(20); 
    text("(pasos/min)", 620, 75);  
    //pasosIMG.resize(75,75);
    
    
    int y = 125; 
    int x=75;
    int space = 15; 
    int len1 = 400; 
    int stopX = 975;
    int len2 = stopX-x; 
    int stopY = y+len1;
    
    int minuto = 0;
    int pasosG = 80;
   
    //Horizontal lines
    for (int xx=75; xx<=stopX; xx+=space) { 
      line(xx, y, xx, y+len1);
      textSize(10);
      if(minuto == 61)
      {
        minuto = 0;
      }
      text(minuto, xx-5, 550);
      minuto++;
    }
   
    //Vertical lines  
    for (int yy=125; yy<=stopY; yy+=space+35) { 
      line(x, yy, x+len2, yy);
      textSize(10);
      if(pasosG == -1)
      {
        pasosG = 80;
      }
      text(pasosG, x-15, yy+5);
      pasosG = pasosG - 10;
    }  
     //image(pasosIMG,1,1,100,100);
  }

  public void draw() {
    
    
    
    if(pasos > 80){
      
      pasos = 0;
    }
  
    
    float ejex;
    float ejey;
    
    ejey = 525 - pasos * 5;
    ejex = 75 + minute() * 15 + second() / 4;
    fill(255, 0, 0); 
    ellipse(ejex, ejey, 10, 10);
  }
  
}
class ChildAppletInc extends PApplet {
  
  public ChildAppletInc() {
    super();
    PApplet.runSketch(new String[]{this.getClass().getName()}, this);
  }

  public void settings() {
    size (960, 640); 
    smooth();
  }
  
  public void setup() { 
    f = createFont("Arial", 12, true);
    F = createFont("Arial", 24, true);
    
    surface.setTitle("Sensor de inclinacion");
    background(50);   
  }

  public void draw() {
    background(0);
    if(pitch > -5 && pitch < 15)
    {
      //colum0.resize(100,250);
      //image(colum0, 430, 100);
    }
    else if(pitch > 14 && pitch < 30)
    {
      //colum15.resize(100,250);
      //image(colum15, 430, 100);
    }
    else if(pitch > 29 && pitch < 45)
    {
      //colum30.resize(100,250);
      //image(colum30, 430, 100);
    }
    else if(pitch > 44 && pitch < 60)
    {
      //colum45.resize(100,250);
      //image(colum45, 430, 100);
    }
    else if(pitch > 60 && pitch < 75)
    {
      //colum60.resize(100,250);
      //image(colum60, 430, 100);
    }
    textSize(50);
    text("Roll: " + int(roll) + "     Pitch: " + int(pitch), 100, 500);
  }
  
}
