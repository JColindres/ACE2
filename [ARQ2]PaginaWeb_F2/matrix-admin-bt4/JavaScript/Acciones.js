function ActivarAntiRobo(){
    //alert("Modo Antirrobo activado");
    var objct='{"triceps":4,"curl":4,"lateral":4,"repExtra":3}';
    httpPatch('https://arq-wifi.firebaseio.com/Incorrectos/.json',objct,function(response){
            var response1 = JSON.parse(response);
            if(response1==true){
                //toastr.success('Agregado correctamente', 'Usuario');
                alert("Modo Antirrobo activado");
            }else if(response1==false){
                alert("Modo Antirrobo activado desactivado");
            }
            //alert(response1);
    });
}

		
var array_cor = [];
var array_peso = [];
var array_fecha = [];
var array_repe = [];
var fecha;
var feho;
var ejer = 0;

function obtenerF(){
	var theurl = 'https://arq-wifi.firebaseio.com/Registro/.json';
	var client = new HttpClient();
	client.get(theurl, function (response) {
		// do something with response
		response1 = JSON.parse(response,function(key,value){
			if(key=="corazon"){
				array_cor.push(value);
			}
			else if(key=="peso"){
				array_peso.push(value);
			}
			else if(key=="fecha"){
				fecha = value.substring(0,2);
				if(fecha == "16"){
					feho = "J-";
				}
				else if(fecha == "17"){
					feho = "V-";
				}
				else if(fecha == "18"){
					feho = "S-";
				}
				else if(fecha == "19"){
					feho = "D-";
				}
				else if(fecha == "20"){
					feho = "L-";
				}
			}
			else if(key=="hora"){
				feho += value;
				array_fecha.push(feho);
			}
			else if(key=="repeticion"){
				array_repe.push(value);
			}
		});      
	});
	//alert(array_fecha.length+","+array_cor.length+","+array_peso.length+","+array_repe.length);
}

function obtenerF2(){
	var theurl = 'https://arq-wifi.firebaseio.com/Registro/.json';
	var client = new HttpClient();
	client.get(theurl, function (response) {
		// do something with response
		response1 = JSON.parse(response,function(key,value){
			if(key=="corazon"){
				array_cor.push(value);
			}
			else if(key=="ejercicio"){
				ejer = value;				
			}
			else if(key=="peso"){
				array_peso.push(value);
			}
			else if(key=="fecha"){
				fecha = value.substring(0,2);
				if(fecha == "16"){
					feho = "J-";
				}
				else if(fecha == "17"){
					feho = "V-";
				}
				else if(fecha == "18"){
					feho = "S-";
				}
				else if(fecha == "19"){
					feho = "D-";
				}
				else if(fecha == "20"){
					feho = "L-";
				}
			}
			else if(key=="hora"){
				feho += value;
				array_fecha.push(feho);
			}
			else if(key=="repeticion"){
				array_repe.push(value);
				if(ejer != 1){
					array_cor.pop();
					array_peso.pop();
					array_repe.pop();
					array_cor.push(0);
					array_peso.push(0);
					array_repe.push(0);
				}
			}
		});      
	});
	//alert(array_fecha.length+","+array_cor.length+","+array_peso.length+","+array_repe.length);
}

function obtenerF3(){
	var theurl = 'https://arq-wifi.firebaseio.com/Registro/.json';
	var client = new HttpClient();
	client.get(theurl, function (response) {
		// do something with response
		response1 = JSON.parse(response,function(key,value){
			if(key=="corazon"){
				array_cor.push(value);
			}
			else if(key=="ejercicio"){
				ejer = value;				
			}
			else if(key=="peso"){
				array_peso.push(value);
			}
			else if(key=="fecha"){
				fecha = value.substring(0,2);
				if(fecha == "16"){
					feho = "J-";
				}
				else if(fecha == "17"){
					feho = "V-";
				}
				else if(fecha == "18"){
					feho = "S-";
				}
				else if(fecha == "19"){
					feho = "D-";
				}
				else if(fecha == "20"){
					feho = "L-";
				}
			}
			else if(key=="hora"){
				feho += value;
				array_fecha.push(feho);
			}
			else if(key=="repeticion"){
				array_repe.push(value);
				if(ejer != 2){
					array_cor.pop();
					array_peso.pop();
					array_repe.pop();
					array_cor.push(0);
					array_peso.push(0);
					array_repe.push(0);
				}
			}
		});      
	});
	//alert(array_fecha.length+","+array_cor.length+","+array_peso.length+","+array_repe.length);
}

function obtenerF4(){
	var theurl = 'https://arq-wifi.firebaseio.com/Registro/.json';
	var client = new HttpClient();
	client.get(theurl, function (response) {
		// do something with response
		response1 = JSON.parse(response,function(key,value){
			if(key=="corazon"){
				array_cor.push(value);
			}
			else if(key=="ejercicio"){
				ejer = value;				
			}
			else if(key=="peso"){
				array_peso.push(value);
			}
			else if(key=="fecha"){
				fecha = value.substring(0,2);
				if(fecha == "16"){
					feho = "J-";
				}
				else if(fecha == "17"){
					feho = "V-";
				}
				else if(fecha == "18"){
					feho = "S-";
				}
				else if(fecha == "19"){
					feho = "D-";
				}
				else if(fecha == "20"){
					feho = "L-";
				}
			}
			else if(key=="hora"){
				feho += value;
				array_fecha.push(feho);
			}
			else if(key=="repeticion"){
				array_repe.push(value);
				if(ejer != 3){
					array_cor.pop();
					array_peso.pop();
					array_repe.pop();
					array_cor.push(0);
					array_peso.push(0);
					array_repe.push(0);
				}
			}
		});      
	});
	//alert(array_fecha.length+","+array_cor.length+","+array_peso.length+","+array_repe.length);
}

function hooola(){
    alert("Obteniendo Información");
    var theurl = 'https://arq-wifi.firebaseio.com/Actual.json';
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

            if(key=="corazon"){
				                
            }
			alert(key + "," + value);
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

//-------------------------------------------DELETE----------------------------------------
function httpDelete(url,callback){
    var xmlHttp= new XMLHttpRequest ();
    xmlHttp.open("DELETE",url,true);
    xmlHttp.setRequestHeader('Content-Type','application/json; charset=UTF-8');
    xmlHttp.onreadystatechange=function(){

        if(xmlHttp.readyState==4 && xmlHttp.status ==200)
        callback(xmlHttp.responseText);
    }
    xmlHttp.send();
}
//---------------------------------------------POST----------------------------------------
function httpPatch(url,obj,callback){
    var xmlHttp= new XMLHttpRequest ();
    xmlHttp.open("PATCH",url,true);
    xmlHttp.setRequestHeader('Content-Type','application/json; charset=UTF-8');
    xmlHttp.onreadystatechange=function(){

        if(xmlHttp.readyState==4 && xmlHttp.status ==200)
        callback(xmlHttp.responseText);
    }
    xmlHttp.send(obj);
}