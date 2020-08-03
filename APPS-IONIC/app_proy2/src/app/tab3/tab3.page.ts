import { Component, OnInit} from '@angular/core';
import { FirebaseP2Service } from '../services/firebase-p2.service';
import { Observable, interval } from 'rxjs';
import { ChartDataSets } from 'chart.js';
import { Color, Label } from 'ng2-charts';

@Component({
  selector: 'app-tab3',
  templateUrl: 'tab3.page.html',
  styleUrls: ['tab3.page.scss']
})
export class Tab3Page implements OnInit {

  // Data
  chartData: ChartDataSets[] = [{ data: [], label: 'Velocidad' },{ data: [], label: 'Distancia Recorrida' },{ data: [], label: 'Tiempo Total' },{ data: [], label: 'Objetos En' },{ data: [], label: 'Objetos Ev' },{ data: [], label: 'Derribados' },{ data: [], label: 'Tiempo Decision' }];
  chartLabels: Label[];
 
  // Options
  chartOptions = {
    responsive: true,
    title: {
      display: true,
      text: 'Historial'
    },
    pan: {
      enabled: true,
      mode: 'xy'
    },
    zoom: {
      enabled: true,
      mode: 'xy'
    }
  };
  chartColors: Color[] = [
    {
      borderColor: '#000000',
      backgroundColor: '#ff00ff'
    }
  ];
  chartType = 'line';
  showLegend = false;

  datos = [];
  tipo = 'mapa';
  constructor(public patchS: FirebaseP2Service) {
   patchS.getDatos()
      .subscribe(datos =>{
        this.datos = datos; 
      });
  }


  public ngOnInit(): void {
    const ejecutar = interval(1000);
  
    ejecutar.subscribe( n => {
      if(this.tipo == 'mapa'){
        this.Actualizar();
      }
      else if(this.tipo == 'graficas' && (this.stock.length > 2)){
        var x = 0;
        var t = 100;
        if(this.stock.length == 8){
          this.chartLabels = [];
          this.chartData[0].data = [];
          this.chartData[0].data = [];
          this.chartData[1].data = [];
          this.chartData[2].data = [];
          this.chartData[3].data = [];
          this.chartData[4].data = [];
          this.chartData[5].data = [];
          this.chartData[6].data = [];
    
          for (let entry of this.datos) {
            if(t > entry.tiempo){
              x++;
            }
            if(entry.fecha == this.stock){
              this.chartLabels.push("Registro "+x);
              this.chartData[0].data.push(entry['velocidad']);
              this.chartData[1].data.push(entry['distancia']);
              this.chartData[2].data.push(entry['tiempo']);
              this.chartData[3].data.push(entry['objetosEN']);
              this.chartData[4].data.push(entry['objetosEV']);
              this.chartData[5].data.push(entry['objetosDER']);
              this.chartData[6].data.push(entry['decision']);
            }
            t = entry.tiempo;
          }
        }
        else if(this.stock.length == 3){
          this.chartLabels = [];
          this.chartData[0].data = [];
          this.chartData[0].data = [];
          this.chartData[1].data = [];
          this.chartData[2].data = [];
          this.chartData[3].data = [];
          this.chartData[4].data = [];
          this.chartData[5].data = [];
          this.chartData[6].data = [];
          var num = this.stock.split("#");
          for (let entry of this.datos) {
            if(t > entry.tiempo){
              x++;
            }
            if(num[1] == x.toString()){
              this.chartLabels.push(entry.fecha);
              this.chartData[0].data.push(entry['velocidad']);
              this.chartData[1].data.push(entry['distancia']);
              this.chartData[2].data.push(entry['tiempo']);
              this.chartData[3].data.push(entry['objetosEN']);
              this.chartData[4].data.push(entry['objetosEV']);
              this.chartData[5].data.push(entry['objetosDER']);
              this.chartData[6].data.push(entry['decision']);              
            }
            t = entry.tiempo;
          }
        }
      }
    });
  }

  stock = '';

  typeChanged(e) {
    const on = e.detail.checked;
    this.chartType = on ? 'bar' : 'line';
  }

  Actualizar(){
    var t = 100;
    for(var i = 0; i < this.datos.length; i++){
      var ultCoorx;
      var ultCoory;

      if(t > this.datos[i].tiempo){
        for(var k = 0; k < 30; k++){
          for(var j = 0; j < 15; j++){
            let dv:HTMLElement = document.getElementById('i'+k+'-'+j); 
            let ima:HTMLImageElement = dv.getElementsByTagName('img')[0];

            ima.src = "../../assets/icon/arbolAW.jpg";
          }
        }
      }
      if(this.datos[i].pos){
        var coordenadas = this.datos[i].pos.split(",");
        coordenadas[0] = this.cambio(coordenadas[0]);
        if(i == 0 && coordenadas[0] == '0' && coordenadas[1] == '0'){
          let dv:HTMLElement = document.getElementById('i0-10'); 
          let ima:HTMLImageElement = dv.getElementsByTagName('img')[0];
          ultCoorx = coordenadas[1];
          ultCoory = coordenadas[0];
          
          if(i == this.datos.length - 1){
            ima.src = "../../assets/icon/ubi.png";
          }
          else{
            ima.src = "../../assets/icon/carreteraAW.jpg";
          }
        }
        else{
          let dv:HTMLElement = document.getElementById('i'+coordenadas[1]+'-'+coordenadas[0]); 
          let ima:HTMLImageElement = dv.getElementsByTagName('img')[0];
          ultCoorx = coordenadas[1];
          ultCoory = coordenadas[0];
          
          if(i == this.datos.length - 1){
            ima.src = "../../assets/icon/ubi.png";
          }
          else{
            ima.src = "../../assets/icon/carreteraAW.jpg";
          }
        }
      }
      else{
        let dv:HTMLElement = document.getElementById('i'+ultCoorx+'-'+ultCoory); 
        let ima:HTMLImageElement = dv.getElementsByTagName('img')[0];
        ultCoorx = coordenadas[1];
        ultCoory = coordenadas[0];
        
        ima.src = "../../assets/icon/ubi.png";
      }
      t = this.datos[i].tiempo;
    }

  }

  cambio(x){
    if(x == '0'){
      x = '14';
    }
    else if(x == '1'){
      x = '13';
    }
    else if(x == '2'){
      x = '12';
    }
    else if(x == '3'){
      x = '11';
    }
    else if(x == '4'){
      x = '10';
    }
    else if(x == '5'){
      x = '9';
    }
    else if(x == '6'){
      x = '8';
    }
    else if(x == '7'){
      x = '7';
    }
    else if(x == '8'){
      x = '6';
    }
    else if(x == '9'){
      x = '5';
    }
    else if(x == '10'){
      x = '4';
    }
    else if(x == '11'){
      x = '3';
    }
    else if(x == '12'){
      x = '2';
    }
    else if(x == '13'){
      x = '1';
    }
    else if(x == '14'){
      x = '0';
    }
    return x;
  }
}
