#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <SoftwareSerial.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

//                  D2, D1
//                  Rx, Tx
SoftwareSerial wifi(4, 5);

ESP8266WiFiMulti WiFiMulti;

const char* ssid = "Moto E (4) Plus 7507";
const char* password = "yeetboi1";

void setup() {
  delay(10);
  Serial.begin(9600);
  wifi.begin(4800);

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);

  WiFi.begin(ssid, password);

  Serial.print("Conectando...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("Conexion establecida, ");
  Serial.print("Direccion IP: ");
  Serial.println(WiFi.localIP());
  pinMode(4, INPUT);
  pinMode(5, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  hacerGet();
  delay(5000);
}

void hacerGet() {
  if (WiFiMulti.run() == WL_CONNECTED) { //Check WiFi connection status
    WiFiClient client;
    HTTPClient http;
    if (http.begin(client, "http://proyectoarq.appspot.com")) {      //Indicamos el destino
      http.addHeader("Content-Type", "application/json"); //Preparamos el header text/plain si solo vamos a enviar texto plano sin un paradigma llave:valor.

      int codigo_respuesta = http.GET();   //Enviamos el post pasándole, los datos que queremos enviar. (esta función nos devuelve un código que guardamos en un int)

      if (codigo_respuesta > 0) {
        Serial.println("Código HTTP ► " + String(codigo_respuesta));   //Print return code

        if (codigo_respuesta == 200) {
          String cuerpo_respuesta = http.getString();
          Serial.println("El servidor respondió ▼ ");
          Serial.println(cuerpo_respuesta);
          if (cuerpo_respuesta != "nada0") {
            wifi.print(cuerpo_respuesta);
            wifi.print("\n");
          }
        }

      } else {

        Serial.print("Error enviando GET, código: ");
        Serial.println(codigo_respuesta);

      }

      http.end();  //libero recursos

    } else {

      Serial.println("Error en la conexión WIFI");
    }
  }

  delay(2000);
}
