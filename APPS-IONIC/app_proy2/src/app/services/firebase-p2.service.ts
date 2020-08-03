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
    return this.db.list('Datos/').valueChanges(); 
    
  }

  addDisparo() {
    return new Promise((resolve, reject) => {
      this.http.patch(this.url, {'Modo': 4})
        .subscribe(response => {
          resolve(response);
        }, (error) => {
          reject(error);
        });
    });
  }

  
  addDerribar() {
    return new Promise((resolve, reject) => {
      this.http.patch(this.url, {'Modo': 1})
        .subscribe(response => {
          resolve(response);
        }, (error) => {
          reject(error);
        });
    });
  }

  addDetener() {
    return new Promise((resolve, reject) => {
      this.http.patch(this.url, {'Modo': 2})
        .subscribe(response => {
          resolve(response);
        }, (error) => {
          reject(error);
        });
    });
  }

  addEsquivar() {
    return new Promise((resolve, reject) => {
      this.http.patch(this.url, {'Modo': 3})
        .subscribe(response => {
          resolve(response);
        }, (error) => {
          reject(error);
        });
    });
  }

}
