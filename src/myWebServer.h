#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#ifndef common
 #include "common.h"
#endif 
#ifndef myWiFi
 #include "myWiFi.h"
#endif


ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;

void MyWebinit(void){
  
  httpUpdater.setup(&httpServer);
  httpServer.begin();
  //Serial.println(WiFi.localIP);
  Serial.print("HTTPUpdateServer ready! Open http://192.168.1.234/update in your browser\n");
 }