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
    alert("Obteniendo Información");
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
            if(key=="SON"){
                ActivoPeso=false;
                //alert("Se encontro PES");
            }
            if(key=="PES"){
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
});