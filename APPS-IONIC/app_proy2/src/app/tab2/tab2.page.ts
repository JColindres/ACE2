import { Component } from '@angular/core';
import { AlertController } from '@ionic/angular';
import { FirebaseP2Service } from '../services/firebase-p2.service';

@Component({
  selector: 'app-tab2',
  templateUrl: 'tab2.page.html',
  styleUrls: ['tab2.page.scss']
})
export class Tab2Page {


  constructor(public alertController: AlertController, public patchS: FirebaseP2Service) {}

  async disparar(){
    this.patchS.addDisparo();
    const alert = await this.alertController.create({
      header: 'Alert',
      subHeader: 'Disparaste!',
      message: 'Se realizó un Disparo.',
      buttons: ['OK']
    });

    await alert.present();
  }

  async esquivar(){
    this.patchS.addEsquivar();
    const alert = await this.alertController.create({
      header: 'Alert',
      subHeader: 'Evasión!',
      message: 'Evadiendo por la mejor opción.',
      buttons: ['OK']
    });

    await alert.present();
  }

  async derribar(){
    this.patchS.addDerribar();
    const alert = await this.alertController.create({
      header: 'Alert',
      subHeader: 'Derribar!',
      message: 'Derribar al objetivo.',
      buttons: ['OK']
    });

    await alert.present();
  }

  async detener(){
    this.patchS.addDetener();
    const alert = await this.alertController.create({
      header: 'Alert',
      subHeader: 'Detener!',
      message: 'Finalizando recorrido.',
      buttons: ['OK']
    });

    await alert.present();
  }

}
