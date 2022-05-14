/*ORGUERRA.COM*/
//Libraires
#include <Arduino.h>
#include <WiFiManager.h> //https://github.com/tzapu/WiFiManager
#include <ArtnetWifi.h> //https://github.com/rstephan
#include <ESPDMX.h> //https://github.com/Rickgg/ESP-Dmx
//Modifier dans espdmx.cpp: "int sendPin = 2;" par "int sendPin = 4;" et ajouter "HardwareSerial DMXSerial(1);" dans ESPDMX.cpp et utiliser la broche D4

//Artnet
WiFiUDP UdpSend;
ArtnetWifi artnet;
//ESPDMX
DMXESPSerial dmx;

void setup(){
  Serial.begin(115200);
  //Wifi
  WiFi.mode(WIFI_STA);
  Serial.begin(115200);
  WiFiManager wm;
  bool res;
  res = wm.autoConnect("DMXDuino");
  if(!res) {
      Serial.println("Connexion echouée");
      // ESP.restart();
  } 
  else {
      //if you get here you have connected to the WiFi    
      Serial.println("Connexion réussie");
  }
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
