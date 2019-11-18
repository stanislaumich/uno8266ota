/*
  To upload through terminal you can use: curl -F "image=@firmware.bin" esp8266-webupdate.local/update
*/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
////////////////
#ifndef common
 #include "common.h"
#endif 
#ifndef myWiFi
 #include "myWiFi.h"
#endif
#ifndef myWeb
 #include "myWebServer.h"
#endif



void setup(void) {
  Serial.begin(9600);
  Serial.println();
  Serial.println("Booting Sketch...");
  MyWiFiInit();
  MyWebinit();
}

void loop(void) {
  httpServer.handleClient();
  
}