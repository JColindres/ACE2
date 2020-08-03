
#include <ESP8266WiFi.h>
#include <WifiLocation.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <FirebaseArduino.h>
#include <time.h>
#include <WifiLocation.h>
#include <SoftwareSerial.h>

//                  D2, D1
//                  Rx, Tx
SoftwareSerial wifi(4, 5);

// Set these to run example.
#define GOOGLE_KEY "AIzaSyDbj7oOxG0DURFcUq9mwt-OD-ZbPxDTz-I" // Clave API Google Geolocation
#define FIREBASE_HOST "arq-wifi.firebaseio.com"
#define FIREBASE_AUTH "ejxNr2f3QrAbGwsDQlEalFdvjbrpcPNWNQQbzooe"
#define WIFI_SSID "AndroidAPcarlos"
#define WIFI_PASSWORD "hola1234"

// Llamada a la API de Google
//WifiLocation location(GOOGLE_KEY);
//location_t loc; // Estructura de datos que devuelve la librería WifiLocation

int timezone = 3;
int dst = 0;
String hora;

void setup() {
  Serial.begin(9600);
  wifi.begin(4800);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  configTime(1 * 3600, 0, "pool.ntp.org", "time.nist.gov");
  Serial.println("\nWaiting for time");
  while (!time(nullptr)) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
}

int idCOR = 100;
int idGPS = 100;
int idINC = 100;
int idLLUVIA = 100;
int idLUZ = 100;
int idPASOS = 100;
int idPES = 100;
int idSON = 100;

const int numpedazos = 8;
String pedazos[8];

int cont = 0;
int lastInd = 0;

float valCOR, valINC, valLL, valLUZ,valPAS, valPES, valSON = 0;
String valLLUVIA;

void loop() {
  // Obtenemos la geolocalización WiFi
  //loc = location.getGeoFromWiFi();
  
  // Mostramos la información en el monitor serie
  //Serial.println("Location request data");
  //location.getSurroundingWiFiJson();
  //Serial.println("Latitude: " + String(loc.lat, 7));
 // Serial.println("Longitude: " + String(loc.lon, 7));
//  Serial.println("Accuracy: " + String(loc.accuracy));
  
  time_t now = time(nullptr);
  String sz = String(ctime(&now));
  hora = sz.substring(11,20);
  Serial.println(hora);

  if(wifi.available() > 0){
    String input = wifi.readString();
    for(int i = 0; i< input.length(); i++){
      if(input.substring(i, i+1) == "/"){
        pedazos[cont] = input.substring(lastInd, i);
        lastInd = i+1;
        cont++;
      }
      if(i == input.length()-1){
        pedazos[cont] = input.substring(lastInd, i);
      }
    }

    input = " ";
    cont = 0;
    lastInd = 0;
  }
  Serial.println(pedazos[0]);
  Serial.println(pedazos[1]);
  Serial.println(pedazos[2]);
  valPES = pedazos[0].toFloat();
  valLUZ = pedazos[1].toFloat();
  valSON = pedazos[2].toFloat();
  if(pedazos[3] == "1"){
    valLLUVIA = "No";
  }
  else{
    valLLUVIA = "Si";
  }
  valPAS = pedazos[4].toFloat();
  valINC = pedazos[6].toFloat();
  valCOR = pedazos[7].toFloat();
  //if(idCOR < 204){
    COR();
    GPS();
    INC();
    LLUVIA();
    LUZ();
    PASOS();
    PES();
    SON();
  //}
}

void COR() {
  String a = "COR/C";
  a += idCOR;
  a += "/Fecha";
  String b = "COR/C";
  b += idCOR;
  b += "/Hora";
  String c = "COR/C";
  c += idCOR;
  c += "/sensor";

  Firebase.setString(a, "Viernes");
  // handle error
  if (Firebase.failed()) {
    Serial.print("pushing /logs failed:");
    Serial.println(Firebase.error());
    return;
  }
  delay(250);

  Firebase.setString(b, hora);
  // handle error
  if (Firebase.failed()) {
    Serial.print("pushing /logs failed:");
    Serial.println(Firebase.error());
    return;
  }
  delay(250);

  Firebase.setFloat(c, valCOR);
  // handle error
  if (Firebase.failed()) {
    Serial.print("pushing /logs failed:");
    Serial.println(Firebase.error());
    return;
  }
  delay(250);

  idCOR++;
}

void GPS() {
  String a = "GPS/G";
  a += idGPS;
  a += "/Fecha";
  String b = "GPS/G";
  b += idGPS;
  b += "/Hora";
  String c = "GPS/G";
  c += idGPS;
  c += "/lat";
  String d = "GPS/G";
  d += idGPS;
  d += "/lon";
  String e = "GPS/G";
  e += idGPS;
  e += "/nombre";
  String nom = "P";
  nom += idGPS;

  float lat, lon;
  long llat,llon;
  String la,lo;

  llat = random(587162,587172);
  llon = random(552820,552830);
  la = "14."+(String)llat;
  lo = "-90."+(String)llon; 
  lat = la.toFloat();
  lon = lo.toFloat();
  
  Firebase.setString(a, "Viernes");
  // handle error
  if (Firebase.failed()) {
    Serial.print("pushing /logs failed:");
    Serial.println(Firebase.error());
    return;
  }
  delay(250);

  Firebase.setString(b, hora);
  // handle error
  if (Firebase.failed()) {
    Serial.print("pushing /logs failed:");
    Serial.println(Firebase.error());
    return;
  }
  delay(250);

  Firebase.setFloat(c, lat);
  // handle error
  if (Firebase.failed()) {
    Serial.print("pushing /logs failed:");
    Serial.println(Firebase.error());
    return;
  }
  delay(250);
  
  Firebase.setFloat(d, lon);
  // handle error
  if (Firebase.failed()) {
    Serial.print("pushing /logs failed:");
    Serial.println(Firebase.error());
    return;
  }
  delay(250);
  
  Firebase.setString(e, nom);
  // handle error
  if (Firebase.failed()) {
    Serial.print("pushing /logs failed:");
    Serial.println(Firebase.error());
    return;
  }
  delay(250);

  idGPS++;
}

void INC() {
  String a = "INC/C";
  a += idINC;
  a += "/Fecha";
  String b = "INC/C";
  b += idINC;
  b += "/Hora";
  String c = "INC/C";
  c += idINC;
  c += "/sensor";

  Firebase.setString(a, "Viernes");
  // handle error
  if (Firebase.failed()) {
    Serial.print("pushing /logs failed:");
    Serial.println(Firebase.error());
    return;
  }
  delay(250);

  Firebase.setString(b, hora);
  // handle error
  if (Firebase.failed()) {
    Serial.print("pushing /logs failed:");
    Serial.println(Firebase.error());
    return;
  }
  delay(250);

  Firebase.setFloat(c, valINC);
  // handle error
  if (Firebase.failed()) {
    Serial.print("pushing /logs failed:");
    Serial.println(Firebase.error());
    return;
  }
  delay(250);

  idINC++;
}

void LLUVIA() {
  String a = "LLUVIA/C";
  a += idLLUVIA;
  a += "/Fecha";
  String b = "LLUVIA/C";
  b += idLLUVIA;
  b += "/Hora";
  String c = "LLUVIA/C";
  c += idLLUVIA;
  c += "/sensor";

  Firebase.setString(a, "Viernes");
  // handle error
  if (Firebase.failed()) {
    Serial.print("pushing /logs failed:");
    Serial.println(Firebase.error());
    return;
  }
  delay(250);

  Firebase.setString(b, hora);
  // handle error
  if (Firebase.failed()) {
    Serial.print("pushing /logs failed:");
    Serial.println(Firebase.error());
    return;
  }
  delay(250);

  Firebase.setString(c, valLLUVIA);
  // handle error
  if (Firebase.failed()) {
    Serial.print("pushing /logs failed:");
    Serial.println(Firebase.error());
    return;
  }
  delay(250);

  idLLUVIA++;
}

void LUZ() {
  String a = "LUZ/C";
  a += idLUZ;
  a += "/Fecha";
  String b = "LUZ/C";
  b += idLUZ;
  b += "/Hora";
  String c = "LUZ/C";
  c += idLUZ;
  c += "/sensor";

  Firebase.setString(a, "Viernes");
  // handle error
  if (Firebase.failed()) {
    Serial.print("pushing /logs failed:");
    Serial.println(Firebase.error());
    return;
  }
  delay(250);

  Firebase.setString(b, hora);
  // handle error
  if (Firebase.failed()) {
    Serial.print("pushing /logs failed:");
    Serial.println(Firebase.error());
    return;
  }
  delay(250);

  Firebase.setFloat(c, valLUZ);
  // handle error
  if (Firebase.failed()) {
    Serial.print("pushing /logs failed:");
    Serial.println(Firebase.error());
    return;
  }
  delay(250);

  idLUZ++;
}

void PASOS() {
  String a = "PASOS/C";
  a += idPASOS;
  a += "/Fecha";
  String b = "PASOS/C";
  b += idPASOS;
  b += "/Hora";
  String c = "PASOS/C";
  c += idPASOS;
  c += "/sensor";

  Firebase.setString(a, "Viernes");
  // handle error
  if (Firebase.failed()) {
    Serial.print("pushing /logs failed:");
    Serial.println(Firebase.error());
    return;
  }
  delay(250);

  Firebase.setString(b, hora);
  // handle error
  if (Firebase.failed()) {
    Serial.print("pushing /logs failed:");
    Serial.println(Firebase.error());
    return;
  }
  delay(250);

  Firebase.setFloat(c, valPAS);
  // handle error
  if (Firebase.failed()) {
    Serial.print("pushing /logs failed:");
    Serial.println(Firebase.error());
    return;
  }
  delay(250);

  idPASOS++;
}

void PES() {
  String a = "PES/C";
  a += idPES;
  a += "/Fecha";
  String b = "PES/C";
  b += idPES;
  b += "/Hora";
  String c = "PES/C";
  c += idPES;
  c += "/sensor";

  Firebase.setString(a, "Viernes");
  // handle error
  if (Firebase.failed()) {
    Serial.print("pushing /logs failed:");
    Serial.println(Firebase.error());
    return;
  }
  delay(250);

  Firebase.setString(b, hora);
  // handle error
  if (Firebase.failed()) {
    Serial.print("pushing /logs failed:");
    Serial.println(Firebase.error());
    return;
  }
  delay(250);

  Firebase.setFloat(c, valPES);
  // handle error
  if (Firebase.failed()) {
    Serial.print("pushing /logs failed:");
    Serial.println(Firebase.error());
    return;
  }
  delay(250);

  idPES++;
}

void SON() {
  String a = "SON/C";
  a += idSON;
  a += "/Fecha";
  String b = "SON/C";
  b += idSON;
  b += "/Hora";
  String c = "SON/C";
  c += idSON;
  c += "/sensor";

  Firebase.setString(a, "Viernes");
  // handle error
  if (Firebase.failed()) {
    Serial.print("pushing /logs failed:");
    Serial.println(Firebase.error());
    return;
  }
  delay(250);

  Firebase.setString(b, hora);
  // handle error
  if (Firebase.failed()) {
    Serial.print("pushing /logs failed:");
    Serial.println(Firebase.error());
    return;
  }
  delay(250);

  Firebase.setFloat(c, valSON);
  // handle error
  if (Firebase.failed()) {
    Serial.print("pushing /logs failed:");
    Serial.println(Firebase.error());
    return;
  }
  delay(250);

  idSON++;
}
