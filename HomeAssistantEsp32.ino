/*
------------ ARTNET
Stephan Ruloff 2016,2019
https://github.com/rstephan
------------ ESPDMX
Copyright (C) 2015  Rick <ricardogg95@gmail.com> (edited by Marcel Seerig)
Documentation and samples are available at https://github.com/Rickgg/ESP-Dmx
*/
//Libraires
#include <ArtnetWifi.h>
#include <Arduino.h>
#include <ESPDMX.h> //Modifier "int sendPin = 2;" par "int sendPin = 4;" et ajouter "HardwareSerial DMXSerial(1);" dans ESPDMX.cpp et utiliser la broche D4

//Paramètres WIFI
const char* ssid = "SSID";
const char* password = "PASS_WIFI";
//Artnet
WiFiUDP UdpSend;
ArtnetWifi artnet;
//ESPDMX
DMXESPSerial dmx;

//Connexion au reseau wifi
boolean ConnectWifi(void){
  boolean state = true;
  int i = 0;
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connexion au réseau WiFi");  
  Serial.print("Connexion");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 20){
      state = false;
      break;
    }
    i++;
  }
  if (state) {
    Serial.println("");
    Serial.print("Connecté à ");
    Serial.println(ssid);
    Serial.print("Adresse IP: ");
    Serial.println(IPAddress(WiFi.localIP()));
  } else {
    Serial.println("");
    Serial.println("Problème de connexion.");
  }  
  return state;
}

void setup(){
  Serial.begin(115200);
  //Wifi
  ConnectWifi();
  //Artnet
  artnet.begin();
  //Espdmx
  dmx.init();
}
void loop(){
  //Reception des données de HA
  artnet.read();
  //Conversion des données Artnet en emision DMX
  artnet.setArtDmxFunc([](DMX_FUNC_PARAM){
    for (int i = 0; i < 512; i++) {
      byte valeur = data[i];
      dmx.write(i+1, valeur);//+1 car décalage des valeurs (HA part de zéro)
    }
    dmx.update();
  });
  //On maintient l'envoi du signal DMX
  dmx.update();
}
