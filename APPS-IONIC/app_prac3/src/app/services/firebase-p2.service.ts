import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { AngularFireDatabase, AngularFireList, AngularFireObject } from '@angular/fire/database';

@Injectable({
  providedIn: 'root'
})
export class FirebaseP2Service {

  url = 'https://arq-wifi.firebaseio.com/.json';

  constructor(public http: HttpClient, private db: AngularFireDatabase) { }

  public getDatos(){
    return this.db.list('Guante/').valueChanges();     
  }

  public getEstadisticas(){
    return this.db.list('Juego/').valueChanges();     
  }

  public postJuego(puntos, EnEsq, tiempo, arr, aba, izq, der, fecha) {
    return new Promise((resolve, reject) => {
      this.http.post('https://arq-wifi.firebaseio.com/Juego/.json', {'Puntos': puntos, 'Esquivados': EnEsq, 'Tiempo': tiempo, 'movAr': arr, 'movAb': aba, 'movIzq': izq, 'movDer': der, 'Fecha': fecha})
        .subscribe(response => {
          resolve(response);
        }, (error) => {
          reject(error);
        });
    });
  }

  public postGuante(a) {
    return new Promise((resolve, reject) => {
      this.http.patch('https://arq-wifi.firebaseio.com/Guante/.json', {'Direccion': a})
        .subscribe(response => {
          resolve(response);
        }, (error) => {
          reject(error);
        });
    });
  }

}
