import { Component, OnInit } from '@angular/core';
import { AlertController } from '@ionic/angular';
import { FirebaseP2Service } from '../services/firebase-p2.service';
import { Observable, interval } from 'rxjs';

@Component({
  selector: 'app-tab2',
  templateUrl: 'tab2.page.html',
  styleUrls: ['tab2.page.scss']
})
export class Tab2Page implements OnInit{

  tiem; 

  direccion;
  ejecutar;
  canvas;
  canvasContext;
  img;
  img1;

  estaJugando = false;
  gOver = false;

  movArr;
  movAba;
  movIzq;
  movDer;

  constructor(public alertController: AlertController, public db: FirebaseP2Service) {
    this.db.getDatos()
        .subscribe(dato =>{
          this.direccion = dato; 
          if(this.direccion == 'i'){
            this.movIzq++;
          }
          else if(this.direccion == 'd'){
            this.movDer++;
          }
          else if(this.direccion == 's'){
            this.movArr++;
          }
          else if(this.direccion == 'b'){
            this.movAba++;
          }
        });
  }

  public ngOnInit(): void {
    let self = this;
    this.canvas = <HTMLCanvasElement> document.getElementById('gameCanvas');
    this.canvasContext = <CanvasRenderingContext2D> this.canvas.getContext('2d');

    var img = new Image();
    img.src = "../../assets/icon/c.jpg";
    var imgBI = new Image();
    imgBI.src = "../../assets/icon/bordeI.jpg";
    var imgBD = new Image();
    imgBD.src = "../../assets/icon/bordeD.jpg";
    var imgPlay = new Image();
    imgPlay.src = "../../assets/icon/play.png";
    var imgO1 = new Image();
    imgO1.src = "../../assets/icon/oA.jpg";
    var imgO2 = new Image();
    imgO2.src = "../../assets/icon/oB.jpg";
    var imgO3 = new Image();
    imgO3.src = "../../assets/icon/oC.jpg";
    img.onload = function() {
      self.canvasContext.drawImage(imgBI,0,0,34,self.canvas.height);
      self.canvasContext.drawImage(img,35,0,288,self.canvas.height);
      self.canvasContext.drawImage(imgBD,323,0,36,self.canvas.height);
      self.canvasContext.drawImage(imgPlay,129,170,100,100);
      self.canvasContext.fillStyle = "black";
      self.canvasContext.fillRect(0,0,self.canvas.width,50);
      self.canvasContext.font = "20px Courier";
      self.canvasContext.fillStyle = "white";
      self.canvasContext.fillText('SCORE',5,20);
      self.canvasContext.fillText('0000',10,45);
      self.canvasContext.fillText('TIME',300,20);
      self.canvasContext.fillText('0000',300,45);
      self.canvasContext.drawImage(imgO1,80,10,20,35);
      self.canvasContext.font = "15px Courier";
      self.canvasContext.fillText('+2pts',100,30);
      self.canvasContext.drawImage(imgO2,150,10,20,35);
      self.canvasContext.fillText('+3pts',170,30);
      self.canvasContext.drawImage(imgO3,220,10,20,35);
      self.canvasContext.fillText('+5pts',240,30);
    }
  }

  arriba(){
    this.db.postGuante("s");
    this.direccion = "s";
  }

  izq(){
    this.db.postGuante("i");
    this.direccion = "i";
  }

  neu(){
    this.db.postGuante("n");
    this.direccion = "n";
  }

  der(){
    this.db.postGuante("d");
    this.direccion = "d";
  }

  abajo(){
    this.db.postGuante("b");
    this.direccion = "b";
  }

  sumar(){
    this.tiem = this.tiem + 1;
  }

  apagar(){
    if(this.estaJugando == false){
      this.estaJugando = true;
    }
    else{
      this.estaJugando = false;
    }
    if(this.gOver = true){
      this.gOver = false;
    }
    let self = this;
    this.canvas = <HTMLCanvasElement> document.getElementById('gameCanvas');
    this.canvasContext = <CanvasRenderingContext2D> this.canvas.getContext('2d');

    var fecha: Date = new Date();

    var img = new Image();
    img.src = "../../assets/icon/c.jpg";
    var imgBI = new Image();
    imgBI.src = "../../assets/icon/bordeI.jpg";
    var imgBD = new Image();
    imgBD.src = "../../assets/icon/bordeD.jpg";
    var imgPlay = new Image();
    imgPlay.src = "../../assets/icon/play.png";
    var imgO1 = new Image();
    imgO1.src = "../../assets/icon/oA.jpg";
    var imgO2 = new Image();
    imgO2.src = "../../assets/icon/oB.jpg";
    var imgO3 = new Image();
    imgO3.src = "../../assets/icon/oC.jpg";
    img.onload = function() {
      var yCanvas = 0;
      //Puntaje
      var puntos = 0;
      //Enemigos esquivads
      var enEsq = 0;
      //movimientos
      self.movAba = 0;
      self.movArr = 0;
      self.movIzq = 0;
      self.movDer = 0;
      //Tiempo
      var n = 0;
      //coordenadas del jugador
      var y = 450;
      var x = 150;
      //velocidad de (Jugador,Carretera)
      var k = 0.75;
      var m = 1.5;
      //num aleatorio
      var ale1, ale2, ale3;
      //coordenadas de los oponentes
      var yEn1, xEn1;
      var yEn2, xEn2;
      var yEn3, xEn3;
      //contrincante aleatorio
      var contrin1, contrin2, contrin3 = 0;
      
      self.tiem = 0;
      var id2 = setInterval(function() { self.tiem = self.tiem + 1; },1000);

      var id = setInterval( function() {
        //movimiento de la carretera
        if(yCanvas < 513){
          self.canvasContext.drawImage(imgBI,0,yCanvas,34,self.canvas.height);
          self.canvasContext.drawImage(imgBI,0,-512+yCanvas,34,self.canvas.height);
          self.canvasContext.drawImage(img,35,yCanvas,288,self.canvas.height);
          self.canvasContext.drawImage(img,35,-512+yCanvas,288,self.canvas.height);
          self.canvasContext.drawImage(imgBD,323,yCanvas,36,self.canvas.height);
          self.canvasContext.drawImage(imgBD,323,-512+yCanvas,36,self.canvas.height);
          if(!self.estaJugando){                    
            self.canvasContext.drawImage(imgPlay,129,170,100,100);
          }
          yCanvas = yCanvas + m;          
        }
        else{
          yCanvas = 0;
        }
        //movimiento del jugador
        var img2 = new Image();
        img2.src = "../../assets/icon/jugador.jpg";
        if(self.direccion == 'n'){
        }
        else if(self.direccion == 'd'){
          if(x < 34 + 288 - 20){
            x = x + k;
          }
        }
        else if(self.direccion == 'i'){
          if(x > 34 - 10){
            x = x - k;
          }          
        }
        else if(self.direccion == 's'){
          if(y > 50){
            y = y - k;
          }
        }
        else if(self.direccion == 'b'){
          if(y < 512 - 58){
            y = y + k;
          }
        }
        self.canvasContext.drawImage(img2,x,y,32,58);
        //movimiento del oponente 1
        var imgEn1 = new Image();
        if(yEn1 == -74){
          contrin1 = Math.floor(Math.random() * 60) + 1;
          if(contrin1 > 0 && contrin1 < 31){
            imgEn1.src = "../../assets/icon/oA.jpg";
            yEn1 = yEn1 + 0.9;
          }
          else if(contrin1 > 30 && contrin1 < 51){
            imgEn1.src = "../../assets/icon/oB.jpg";
            yEn1 = yEn1 + 0.5;
          }
          else if(contrin1 > 50 && contrin1 < 61){
            imgEn1.src = "../../assets/icon/oC.jpg";
            yEn1 = yEn1 + 0.3;
          }
          ale1 = Math.floor(Math.random() * 4) + 1;
          if(ale1 == 1 && xEn2 != 34 + 20 && xEn3 != 34 + 20){
            xEn1 = 34 + 20;
          }
          else if(ale1 == 2 && xEn2 != 34 + 20 + 72 && xEn3 != 34 + 20 + 72){
            xEn1 = 34 + 20 + 72;
          }
          else if(ale1 == 3 && xEn2 != 34 + 20 + 72 * 2 && xEn3 != 34 + 20 + 72 * 2){
            xEn1 = 34 + 20 + 72 * 2;
          }
          else if(ale1 == 4 && xEn2 != 34 + 20 + 72 * 3 && xEn3 != 34 + 20 + 72 * 3){
            xEn1 = 34 + 20 + 72 * 3;
          }
        }
        else if(yEn1 > -74 && yEn1 < 512){
          if(contrin1 > 0 && contrin1 < 31){
            imgEn1.src = "../../assets/icon/oA.jpg";
            yEn1 = yEn1 + 0.9;
          }
          else if(contrin1 > 30 && contrin1 < 51){
            imgEn1.src = "../../assets/icon/oB.jpg";
            yEn1 = yEn1 + 0.5;
          }
          else if(contrin1 > 50 && contrin1 < 61){
            imgEn1.src = "../../assets/icon/oC.jpg";
            yEn1 = yEn1 + 0.3;
          }
        }
        else if(yEn1 > 511){
          if(contrin1 > 0 && contrin1 < 31 && yEn1 == 512.7999999999946){
            puntos += 2;
            enEsq++;
          }
          else if(contrin1 > 30 && contrin1 < 51 && yEn1 == 512){
            puntos += 3;
            enEsq++;
          }
          else if(contrin1 > 50 && contrin1 < 61 && yEn1 == 512.2000000000133){
            puntos += 5;
            enEsq++;
          }
          yEn1 = -74;
        }
        else{
          yEn1 = -74;
        }
        self.canvasContext.drawImage(imgEn1,xEn1,yEn1,42,74);
        //movimiento del oponente 2
        var imgEn2 = new Image();
        if(yEn2 == -74 && yEn1 > 100){
          contrin2 = Math.floor(Math.random() * 60) + 1;
          if(contrin2 > 0 && contrin2 < 31){
            imgEn2.src = "../../assets/icon/oA.jpg";
            yEn2 = yEn2 + 0.9;
          }
          else if(contrin2 > 30 && contrin2 < 51){
            imgEn2.src = "../../assets/icon/oB.jpg";
            yEn2 = yEn2 + 0.5;
          }
          else if(contrin2 > 50 && contrin2 < 61){
            imgEn2.src = "../../assets/icon/oC.jpg";
            yEn2 = yEn2 + 0.3;
          }
          ale2 = Math.floor(Math.random() * 4) + 1;
          if(ale2 == 1 && xEn1 != 20 && xEn3 != 20){
            xEn2 = 34 + 20;
          }
          else if(ale2 == 2 && xEn1 != 34 + 20 + 72 && xEn3 != 34 + 20 + 72){
            xEn2 = 34 + 20 + 72;
          }
          else if(ale2 == 3 && xEn1 != 34 + 20 + 72 * 2 && xEn3 != 34 + 20 + 72 * 2){
            xEn2 = 34 + 20 + 72 * 2;
          }
          else if(ale2 == 4 && xEn1 != 34 + 20 + 72 * 3 && xEn3 != 34 + 20 + 72 * 3){
            xEn2 = 34 + 20 + 72 * 3;
          }
        }
        else if(yEn2> -74 && yEn2 < 512){
          if(contrin2 > 0 && contrin2 < 31){
            imgEn2.src = "../../assets/icon/oA.jpg";
            yEn2 = yEn2 + 0.9;
          }
          else if(contrin2 > 30 && contrin2 < 51){
            imgEn2.src = "../../assets/icon/oB.jpg";
            yEn2 = yEn2 + 0.5;
          }
          else if(contrin2 > 50 && contrin2 < 61){
            imgEn2.src = "../../assets/icon/oC.jpg";
            yEn2 = yEn2 + 0.3;
          }
        }
        else if(yEn2 > 511){
          if(contrin2 > 0 && contrin2 < 31 && yEn2 == 512.7999999999946){
            puntos += 2;
            enEsq++;
          }
          else if(contrin2 > 30 && contrin2 < 51 && yEn2 == 512){
            puntos += 3;
            enEsq++;
          }
          else if(contrin2 > 50 && contrin2 < 61 && yEn2 == 512.2000000000133){
            puntos += 5;
            enEsq++;
          }
          yEn2 = -74;
        }
        else{
          yEn2 = -74;
        }
        self.canvasContext.drawImage(imgEn2,xEn2,yEn2,42,74);
        //movimiento del oponente 3
        var imgEn3 = new Image();
        if(yEn3 == -74 && yEn2 > 100){
          contrin3 = Math.floor(Math.random() * 60) + 1;
          if(contrin3 > 0 && contrin3 < 31){
            imgEn3.src = "../../assets/icon/oA.jpg";
            yEn3 = yEn3 + 0.9;
          }
          else if(contrin3 > 30 && contrin3 < 51){
            imgEn3.src = "../../assets/icon/oB.jpg";
            yEn3 = yEn3 + 0.5;
          }
          else if(contrin3 > 50 && contrin3 < 61){
            imgEn3.src = "../../assets/icon/oC.jpg";
            yEn3 = yEn3 + 0.3;
          }
          ale3 = Math.floor(Math.random() * 4) + 1;
          if(ale3 == 1 && xEn1 != 20 && xEn2 != 20){
            xEn3 = 34 + 20;
          }
          else if(ale3 == 2 && xEn1 != 34 + 20 + 72 && xEn2 != 34 + 20 + 72){
            xEn3 = 34 + 20 + 72;
          }
          else if(ale3 == 3 && xEn1 != 34 + 20 + 72 * 2 && xEn2 != 34 + 20 + 72 * 2){
            xEn3 = 34 + 20 + 72 * 2;
          }
          else if(ale3 == 4 && xEn1 != 34 + 20 + 72 * 3 && xEn2 != 34 + 20 + 72 * 3){
            xEn3 = 34 + 20 + 72 * 3;
          }
        }
        else if(yEn3> -74 && yEn3 < 512){
          if(contrin3 > 0 && contrin3 < 31){
            imgEn3.src = "../../assets/icon/oA.jpg";
            yEn3 = yEn3 + 0.9;
          }
          else if(contrin3 > 30 && contrin3 < 51){
            imgEn3.src = "../../assets/icon/oB.jpg";
            yEn3 = yEn3 + 0.5;
          }
          else if(contrin3 > 50 && contrin3 < 61){
            imgEn3.src = "../../assets/icon/oC.jpg";
            yEn3 = yEn3 + 0.3;
          }
        }
        else if(yEn3 > 511){
          if(contrin3 > 0 && contrin3 < 31 && yEn3 == 512.7999999999946){
            puntos += 2;
            enEsq++;
          }
          else if(contrin3 > 30 && contrin3 < 51 && yEn3 == 512){
            puntos += 3;
            enEsq++;
          }
          else if(contrin3 > 50 && contrin3 < 61 && yEn3 == 512.2000000000133){
            puntos += 5;
            enEsq++;
          }
          yEn3 = -74;
        }
        else{
          yEn3 = -74;
        }
        self.canvasContext.drawImage(imgEn3,xEn3,yEn3,42,74);
        self.canvasContext.fillStyle = "black";
        self.canvasContext.fillRect(0,0,self.canvas.width,50);
        self.canvasContext.font = "20px Courier";
        self.canvasContext.fillStyle = "white";
        self.canvasContext.fillText('SCORE',5,20);
        self.canvasContext.fillText(puntos,10,45);
        self.canvasContext.fillText('TIME',300,20);
        self.canvasContext.fillText(self.tiem,300,45);
        self.canvasContext.drawImage(imgO1,80,10,20,35);
        self.canvasContext.font = "15px Courier";
        self.canvasContext.fillText('+2pts',100,30);
        self.canvasContext.drawImage(imgO2,150,10,20,35);
        self.canvasContext.fillText('+3pts',170,30);
        self.canvasContext.drawImage(imgO3,220,10,20,35);
        self.canvasContext.fillText('+5pts',240,30);
        //colisiones-------------------------------------------------
        if((y <= (yEn1 + 74)) && (y >= (yEn1 + 73))){
          if(((x) <= (xEn1 + 42) && (x) >= (xEn1)) || ((x + 32) <= (xEn1 + 42) && (x + 32) >= (xEn1))){
            self.estaJugando = false;
            self.gOver = true;
          }
        }
        if(((y + 58) <= (yEn1 + 1)) && ((y + 58) >= (yEn1))){
          if(((x) <= (xEn1 + 42) && (x) >= (xEn1)) || ((x + 32) <= (xEn1 + 42) && (x + 32) >= (xEn1))){
            self.estaJugando = false;
            self.gOver = true;
          }
        }
        if(((x + 32) <= (xEn1 + 1)) && ((x + 32) >= (xEn1))){
          if(((y) <= (yEn1 + 74) && (y) >= (yEn1)) || ((y + 58) <= (yEn1 + 74) && (y + 58) >= (yEn1))){
            self.estaJugando = false;
            self.gOver = true;
          }
        }
        if((x <= (xEn1 + 42)) && (x >= (xEn1 + 41))){
          if(((y) <= (yEn1 + 74) && (y) >= (yEn1)) || ((y + 58) <= (yEn1 + 74) && (y + 58) >= (yEn1))){
            self.estaJugando = false;
            self.gOver = true;
          }
        }

        if((y <= (yEn2 + 74)) && (y >= (yEn2 + 73))){
          if(((x) <= (xEn2 + 42) && (x) >= (xEn2)) || ((x + 32) <= (xEn2 + 42) && (x + 32) >= (xEn2))){
            self.estaJugando = false;
            self.gOver = true;
          }
        }
        if(((y + 58) <= (yEn2 + 1)) && ((y + 58) >= (yEn2))){
          if(((x) <= (xEn2 + 42) && (x) >= (xEn2)) || ((x + 32) <= (xEn2 + 42) && (x + 32) >= (xEn2))){
            self.estaJugando = false;
            self.gOver = true;
          }
        }
        if(((x + 32) <= (xEn2 + 1)) && ((x + 32) >= (xEn2))){
          if(((y) <= (yEn2 + 74) && (y) >= (yEn2)) || ((y + 58) <= (yEn2 + 74) && (y + 58) >= (yEn2))){
            self.estaJugando = false;
            self.gOver = true;
          }
        }
        if((x <= (xEn2 + 42)) && (x >= (xEn2 + 41))){
          if(((y) <= (yEn2 + 74) && (y) >= (yEn2)) || ((y + 58) <= (yEn2 + 74) && (y + 58) >= (yEn2))){
            self.estaJugando = false;
            self.gOver = true;
          }
        }

        if((y <= (yEn3 + 74)) && (y >= (yEn3 + 73))){
          if(((x) <= (xEn3 + 42) && (x) >= (xEn3)) || ((x + 32) <= (xEn3 + 42) && (x + 32) >= (xEn3))){
            self.estaJugando = false;
            self.gOver = true;
          }
        }
        if(((y + 58) <= (yEn3 + 1)) && ((y + 58) >= (yEn3))){
          if(((x) <= (xEn3 + 42) && (x) >= (xEn3)) || ((x + 32) <= (xEn3 + 42) && (x + 32) >= (xEn3))){
            self.estaJugando = false;
            self.gOver = true;
          }
        }
        if(((x + 32) <= (xEn3 + 1)) && ((x + 32) >= (xEn3))){
          if(((y) <= (yEn3 + 74) && (y) >= (yEn3)) || ((y + 58) <= (yEn3 + 74) && (y + 58) >= (yEn3))){
            self.estaJugando = false;
            self.gOver = true;
          }
        }
        if((x <= (xEn3 + 42)) && (x >= (xEn3 + 41))){
          if(((y) <= (yEn3 + 74) && (y) >= (yEn3)) || ((y + 58) <= (yEn3 + 74) && (y + 58) >= (yEn3))){
            self.estaJugando = false;
            self.gOver = true;
          }
        }

        if(x == 34 - 10 || x >= 34 + 288 - 20){
          self.estaJugando = false;
          self.gOver = true;
        }
        //reinicio----------------------------------------------------
        if(!self.estaJugando && !self.gOver){
          clearInterval(id2);
          clearInterval(id);
        }
        else if(self.gOver){
          self.db.postJuego(puntos,enEsq,self.tiem,self.movArr,self.movAba,self.movIzq,self.movDer, fecha.getDate()+'/'+(fecha.getMonth()+1)+'/'+fecha.getFullYear());
          clearInterval(id2);
          clearInterval(id);
          var gameOver = new Image();
          gameOver.src = "../../assets/icon/gameOver.gif";
          gameOver.onload = function() {
            self.canvasContext.drawImage(gameOver,0,0,self.canvas.width,self.canvas.height);
          }          
        }
      });    
    }
  }
}
