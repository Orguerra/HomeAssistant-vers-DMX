Utilisation d'un ESP32 pour controller du materiel DMX via HomeAssistant

Coté HA:

Utilisation du plugin hass-dmx: https://github.com/jnimmo/hass-dmx

Coté ESP32:

Utilisation de la bibliothèque ESPDMX: https://github.com/Rickgg/ESP-Dmx

Utilisation de la bibliothèque ArtnetWifi: https://github.com/rstephan/ArtnetWifi

Dans le fichier de la librairie: ESPDMX.cpp

Modifier "int sendPin = 2;" par "int sendPin = 4;" 

Ajouter "HardwareSerial DMXSerial(1);"

Brancher la broche D4 de l'ESP32 sur la pin DI de votre max485.
