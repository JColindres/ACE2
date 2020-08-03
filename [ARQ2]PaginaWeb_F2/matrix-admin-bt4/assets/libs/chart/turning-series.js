//var mensaje='{"lunes":{"label": "lunes","data": [[1988, 100], [1989, 200], [1990, 100], [1991, 200], [1992, 100],[1993, 200], [2006, 100]]},"martes": {"label": "martes","data": [[5, 100],[10, 200],[15, 100],[20, 200],[95, 100]]}}';
var mensaje='';
var lunes='';
var martes='';
var miercoles='';
var jueves='';
var viernes='';
var sabado='';
var domingo='';
var completa='';
var completaAux='';
var CatchHora=false;
var CatchSensor=false;
var ActivoPeso=false;
var dia="";
var cuenta=1;
var cuentaLun=1;
var cuentaMar=1;
var cuentaMie=1;
var cuentaJue=1;
var cuentaVie=1;
var cuentaSab=1;
var cuentaDom=1;

var array_fechas = [];
//var mensaje="";
function ObtenerPeso(){
    alert("Obteniendo pesos");
    var theurl = 'https://arq-wifi.firebaseio.com/.json';
    var client = new HttpClient();
    client.get(theurl, function (response) {
        // do something with response
        response1 = JSON.parse(response,function(key,value){
            /*if (key == "city") {
              return value.toUpperCase();
            } else {
              return value;
            }*/
            //alert(key +","+value);
            if(ActivoPeso==true){
                //alert("esta activo "+ key+","+value);
                
            }
            if(key=="PES"){
                ActivoPeso=false;
                //alert("Se encontro PES");
            }
            if(key=="PASOS"){
                ActivoPeso=true;

            }
          
            if(key=="Hora" && CatchHora==true && ActivoPeso==true){
                CatchHora=false;
                
                if(dia=="Lunes"){
                    array_fechas.push("Lunes, "+value);
                    lunes=lunes+'['+cuentaLun;
                    completaAux=completaAux+'['+cuenta;
                    cuentaLun=cuentaLun+1;
                    cuenta=cuenta+1;
                }else if(dia=="Martes"){
                    array_fechas.push("Martes, "+value);
                    martes=martes+'['+cuentaMar;
                    completaAux=completaAux+'['+cuenta;
                    cuentaMar=cuentaMar+1;
                    cuenta=cuenta+1;
                }else if(dia=="Miercoles"){
                    array_fechas.push("Miercoles, "+value);
                    miercoles=miercoles+'['+cuentaMie;
                    completaAux=completaAux+'['+cuenta;
                    cuentaMie=cuentaMie+1;
                    cuenta=cuenta+1;
                }else if(dia=="Jueves"){
                    array_fechas.push("Jueves, "+value);
                    jueves=jueves+'['+cuentaJue;
                    completaAux=completaAux+'['+cuenta;
                    cuentaJue=cuentaJue+1;
                    cuenta=cuenta+1;
                }else if(dia=="Viernes"){
                    array_fechas.push("Viernes, "+value);
                    viernes=viernes+'['+cuentaVie;
                    completaAux=completaAux+'['+cuenta;
                    cuentaVie=cuentaVie+1;
                    cuenta=cuenta+1;
                }else if(dia=="Sabado"){
                    array_fechas.push("Sabado, "+value);
                    sabado=sabado+'['+cuentaSab;
                    completaAux=completaAux+'['+cuenta;
                    cuentaSab=cuentaSab+1;
                    cuenta=cuenta+1;
                }

            }
            if(key=="sensor" && CatchSensor==true && ActivoPeso==true){
                CatchSensor=false;
                
                if(dia=="Lunes"){
                    lunes=lunes+','+value+'],';
                    completaAux=completaAux+','+value+'],';
                }else if(dia=="Martes"){
                    martes=martes+','+value+'],';
                    completaAux=completaAux+','+value+'],';
                }else if(dia=="Miercoles"){
                    miercoles=miercoles+','+value+'],';
                    completaAux=completaAux+','+value+'],';
                }else if(dia=="Jueves"){
                    jueves=jueves+','+value+'],';
                    completaAux=completaAux+','+value+'],';
                }else if(dia=="Viernes"){
                    viernes=viernes+','+value+'],';
                    completaAux=completaAux+','+value+'],';
                }else if(dia=="Sabado"){
                    sabado=sabado+','+value+'],';
                    completaAux=completaAux+','+value+'],';
                }
            }

            if(key=="Fecha" && ActivoPeso==true){
                if(value=="Lunes"){
                    //alert("entra caca");
                    CatchHora=true;
                    CatchSensor=true;
                    dia="Lunes";
                }else if(value=="Martes"){
                    CatchHora=true;
                    CatchSensor=true;
                    dia="Martes";
                }else if(value=="Miercoles"){
                    CatchHora=true;
                    CatchSensor=true;
                    dia="Miercoles";
                }
                else if(value=="Jueves"){
                    CatchHora=true;
                    CatchSensor=true;
                    dia="Jueves";
                }
                else if(value=="Viernes"){
                    CatchHora=true;
                    CatchSensor=true;
                    dia="Viernes";
                }
                else if(value=="Sabado"){
                    CatchHora=true;
                    CatchSensor=true;
                    dia="Sabado";
                }
                
            }
          });
        //alert(response1.PES[0].Fecha);
        /*var sigue=true;
        Contador
        while(sigue){
            if(response1.PES.){

            }
        }*/
        //alert(response1.jsonNodoAVL[0]);
        //if(response1.PES[0].ID=="nulo"){

        //}else{
            //var tabla="";
            
            //document.getElementById("txt2").value=response1[response1.length-1].name;
        //}        
    });
    
}
function MostrarCompleto(){
    completa='{"Com":{"label": "Com","data":[';
    completa=completa+completaAux.substr(0,completaAux.length-1);
    completa=completa+']}}';
    alert(completa);
    var tabla="<table border=\"1\">";
    tabla+="<tr>";
    for(i=0;i<array_fechas.length;i++){
        if(i%10==0){
            tabla+="</tr>";
            tabla+="<tr>";
            tabla+="<td>"+(i+1)+") "+array_fechas[i]+"</td>";

        }else{
            tabla+="<td>"+(i+1)+") "+array_fechas[i]+"</td>";
        }

    }
    tabla+="</tr>";
    tabla+="</table>";
    document.getElementById("resultado").innerHTML=tabla;

    var datasets =JSON.parse(completa);
    // hard-code color indices to prevent them from shifting as
    // countries are turned on/off
    var i = 0;
    $.each(datasets, function(key, val) {
        val.color = i;
        ++i;
    });

    // insert checkboxes 
    var choiceContainer = $("#choices");
    $.each(datasets, function(key, val) {
        choiceContainer.append('<input type="checkbox" name="' + key +
            '" checked="checked" id="id' + key + '">' +
            '<label for="id' + key + '">' +
            val.label + '</label>');
    });
    choiceContainer.find("input").click(plotAccordingToChoices);


    function plotAccordingToChoices() {
        var data = [];

        choiceContainer.find("input:checked").each(function() {
            var key = $(this).attr("name");
            if (key && datasets[key])
                data.push(datasets[key]);
        });

        if (data.length > 0)
            $.plot($("#placeholder"), data, {
                yaxis: { min: 0 },
                xaxis: { tickDecimals: 0 }
            });
    }

    plotAccordingToChoices();
}

function MostrarMensaje(){
    mensaje='{';
    var tirar=true;
    if(lunes!=''){
        lunes='"lunes":{"label": "lunes","data":['+lunes.substr(0,lunes.length-1)+']}';
        mensaje=mensaje+lunes;
        tirar=true;
    }
    if(martes!=''){
        if(tirar==true){
            mensaje=mensaje+',';
        }
        martes='"martes":{"label": "martes","data":['+martes.substr(0,martes.length-1)+']}';
        mensaje=mensaje+martes;
        tirar=true;
    }
    if(miercoles!=''){
        if(tirar==true){
            mensaje=mensaje+',';
        }
        miercoles='"miercoles":{"label": "miercoles","data":['+miercoles.substr(0,miercoles.length-1)+']}';
        mensaje=mensaje+miercoles;
        tirar=true;
    }
    if(jueves!=''){
        if(tirar==true){
            mensaje=mensaje+',';
        }
        jueves='"jueves":{"label": "jueves","data":['+jueves.substr(0,jueves.length-1)+']}';
        mensaje=mensaje+jueves;
        tirar=true;
    }
    if(viernes!=''){
        if(tirar==true){
            mensaje=mensaje+',';
        }
        viernes='"viernes":{"label": "viernes","data":['+viernes.substr(0,viernes.length-1)+']}';
        mensaje=mensaje+viernes;
        tirar=true;
    }
    if(sabado!=''){
        if(tirar==true){
            mensaje=mensaje+',';
        }
        sabado='"sabado":{"label": "sabado","data":['+sabado.substr(0,sabado.length-1)+']}';
        mensaje=mensaje+sabado;
        tirar=true;
    }


    mensaje=mensaje+'}';
    alert(mensaje);
    var tabla="<table border=\"1\">";
    tabla+="<tr>";
    for(i=0;i<array_fechas.length;i++){
        if(i%10==0){
            tabla+="</tr>";
            tabla+="<tr>";
            tabla+="<td>"+(i+1)+") "+array_fechas[i]+"</td>";

        }else{
            tabla+="<td>"+(i+1)+") "+array_fechas[i]+"</td>";
        }

    }
    tabla+="</tr>";

    /*for(i=0;i<10;i++){
        tabla+="<tr>";
        tabla+="<td>"+(i+1)+ "</td>";
        for(j=0;j<20;j++){
            if((i+j)<array_fechas.length){
                tabla+="<td>"+array_fechas[]+ "</td>";
            } 
            
        }
        tabla+="</tr>";
    }*/
    tabla+="</table>";
    document.getElementById("resultado").innerHTML=tabla;

    var datasets =JSON.parse(mensaje);
    // hard-code color indices to prevent them from shifting as
    // countries are turned on/off
    var i = 0;
    $.each(datasets, function(key, val) {
        val.color = i;
        ++i;
    });

    // insert checkboxes 
    var choiceContainer = $("#choices");
    $.each(datasets, function(key, val) {
        choiceContainer.append('<input type="checkbox" name="' + key +
            '" checked="checked" id="id' + key + '">' +
            '<label for="id' + key + '">' +
            val.label + '</label>');
    });
    choiceContainer.find("input").click(plotAccordingToChoices);


    function plotAccordingToChoices() {
        var data = [];

        choiceContainer.find("input:checked").each(function() {
            var key = $(this).attr("name");
            if (key && datasets[key])
                data.push(datasets[key]);
        });

        if (data.length > 0)
            $.plot($("#placeholder"), data, {
                yaxis: { min: 0 },
                xaxis: { tickDecimals: 0 }
            });
    }

    plotAccordingToChoices();
}

//---------------------------------------------Peticiones--------------------------------
//--------------------------------------------GET----------------------------------------
var HttpClient = function () {
    this.get = function (aUrl, aCallback) {
        var anHttpRequest = new XMLHttpRequest();
        
        anHttpRequest.onreadystatechange = function () {
            if (anHttpRequest.readyState == 4 && anHttpRequest.status == 200)
                aCallback(anHttpRequest.responseText);
        }

        anHttpRequest.open("GET", aUrl, true);
        anHttpRequest.setRequestHeader('Content-Type','application/json; charset=UTF-8');
        anHttpRequest.send();
    }
}

$(function() {
    
    var datasets =JSON.parse(mensaje);/* {
        "martes": {
            label: "martes",
            data: [
                [5, 100],
                [10, 200],
                [15, 100],
                [20, 200],
                [25, 100],
                [30, 200],
                [35, 100],
                [40, 200],
                [45, 100],
                [50, 200],
                [55, 100],
                [60, 200],
                [65, 100],
                [70, 200],
                [75, 100],
                [80, 200],
                [85, 100],
                [90, 200],
                [95, 100]
            ]
        },
        
        "miercoles": {
            label: "miercoles",
            data: [
                [5, 120],
                [10, 210],
                [15, 180],
                [20, 260],
                [25, 100],
                [30, 230],
                [35, 400],
                [40, 200],
                [45, 180],
                [50, 290],
                [55, 120],
                [60, 300],
                [65, 400],
                [70, 240],
                [75, 150],
                [80, 255],
                [85, 177],
                [90, 275],
                [95, 180]
            ]
        },/*
        "germany": {
            label: "Germany",
            data: [
                [1988, 55627],
                [1989, 55475],
                [1990, 58464],
                [1991, 55134],
                [1992, 52436],
                [1993, 47139],
                [1994, 43962],
                [1995, 43238],
                [1996, 42395],
                [1997, 40854],
                [1998, 40993],
                [1999, 41822],
                [2000, 41147],
                [2001, 40474],
                [2002, 40604],
                [2003, 40044],
                [2004, 38816],
                [2005, 38060],
                [2006, 36984]
            ]
        },
        "denmark": {
            label: "Denmark",
            data: [
                [1988, 3813],
                [1989, 3719],
                [1990, 3722],
                [1991, 3789],
                [1992, 3720],
                [1993, 3730],
                [1994, 3636],
                [1995, 3598],
                [1996, 3610],
                [1997, 3655],
                [1998, 3695],
                [1999, 3673],
                [2000, 3553],
                [2001, 3774],
                [2002, 3728],
                [2003, 3618],
                [2004, 3638],
                [2005, 3467],
                [2006, 3770]
            ]
        },
        "sweden": {
            label: "Sweden",
            data: [
                [1988, 6402],
                [1989, 6474],
                [1990, 6605],
                [1991, 6209],
                [1992, 6035],
                [1993, 6020],
                [1994, 6000],
                [1995, 6018],
                [1996, 3958],
                [1997, 5780],
                [1998, 5954],
                [1999, 6178],
                [2000, 6411],
                [2001, 5993],
                [2002, 5833],
                [2003, 5791],
                [2004, 5450],
                [2005, 5521],
                [2006, 5271]
            ]
        },
        "norway": {
            label: "Norway",
            data: [
                [1988, 4382],
                [1989, 4498],
                [1990, 4535],
                [1991, 4398],
                [1992, 4766],
                [1993, 4441],
                [1994, 4670],
                [1995, 4217],
                [1996, 4275],
                [1997, 4203],
                [1998, 4482],
                [1999, 4506],
                [2000, 4358],
                [2001, 4385],
                [2002, 5269],
                [2003, 5066],
                [2004, 5194],
                [2005, 4887],
                [2006, 4891]
            ]
        }
    };*/
   /* var dataSet = [
    {label: "USA", color: "#005CDE" },
    {label: "Russia", color: "#005CDE" },
    { label: "UK", color: "#00A36A" },
    { label: "Germany", color: "#7D0096" },
    { label: "Denmark", color: "#992B00" },
    { label: "Sweden", color: "#DE000F" },
    { label: "Norway", color: "#ED7B00" }    
];*/
    // hard-code color indices to prevent them from shifting as
    // countries are turned on/off
    var i = 0;
    $.each(datasets, function(key, val) {
        val.color = i;
        ++i;
    });

    // insert checkboxes 
    var choiceContainer = $("#choices");
    $.each(datasets, function(key, val) {
        choiceContainer.append('<input type="checkbox" name="' + key +
            '" checked="checked" id="id' + key + '">' +
            '<label for="id' + key + '">' +
            val.label + '</label>');
    });
    choiceContainer.find("input").click(plotAccordingToChoices);


    function plotAccordingToChoices() {
        var data = [];

        choiceContainer.find("input:checked").each(function() {
            var key = $(this).attr("name");
            if (key && datasets[key])
                data.push(datasets[key]);
        });

        if (data.length > 0)
            $.plot($("#placeholder"), data, {
                yaxis: { min: 0 },
                xaxis: { tickDecimals: 0 }
            });
    }

    plotAccordingToChoices();
});