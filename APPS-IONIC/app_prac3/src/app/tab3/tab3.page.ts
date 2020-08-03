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
  chartData: ChartDataSets[] = [{ data: [], label: 'Puntos' },{ data: [], label: 'Esquivados' },{ data: [], label: 'Tiempo Total' },{ data: [], label: 'Movimientos' }];
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
  tipo = 'registros';

  constructor(public patchS: FirebaseP2Service) {
   patchS.getEstadisticas()
      .subscribe(datos =>{
        this.datos = datos; 
      });
  }


  public ngOnInit(): void {
    const ejecutar = interval(1000);
  
    ejecutar.subscribe( n => {
      if(this.tipo == 'graficas' && (this.stock.length > 2)){
        var x = 0;
        var t = 100;
        if(this.stock.length >= 8){
          this.chartLabels = [];
          this.chartData[0].data = [];
          this.chartData[1].data = [];
          this.chartData[2].data = [];
          this.chartData[3].data = [];
    
          for (let entry of this.datos) {
            x++;
            if(entry.Fecha == this.stock){
              this.chartLabels.push("Partida "+x);
              this.chartData[0].data.push(entry['Puntos']);
              this.chartData[1].data.push(entry['Esquivados']);
              this.chartData[2].data.push(entry['Tiempo']);
              this.chartData[3].data.push(entry['movAb']+entry['movAr']+entry['movIzq']+entry['movDer']);
            }
          }
        }
        else if(this.stock.length == 3){
          this.chartLabels = [];
          this.chartData[0].data = [];
          this.chartData[1].data = [];
          this.chartData[2].data = [];
          this.chartData[3].data = [];
          var num = this.stock.split("#");
          for (let entry of this.datos) {
            x++
            if(num[1] == x.toString()){
              this.chartLabels.push(entry.Fecha);
              this.chartData[0].data.push(entry['Puntos']);
              this.chartData[1].data.push(entry['Esquivados']);
              this.chartData[2].data.push(entry['Tiempo']);
              this.chartData[3].data.push(entry['movAb']+entry['movAr']+entry['movIzq']+entry['movDer']);
            }
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
}
