/*To upload through terminal you can use: curl -F "image=@firmware.bin" esp8266-webupdate.local/update*/
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <Update.h>
#include <FS.h>
#ifndef Common
 #include "common.h"
#endif
#ifndef SettingsWiFi
 #include "SettingsWiFi.h"
#endif 
#ifndef MyWebServer
 #include "MyWebServer.h"
#endif
#ifndef MyTime
#include "MyTime.h"
#endif

 

//int interval=1000;

void setup(void) {
  Button_init();
  beep(200,2000);
  FS_init();
  addds("Starting :-)");
  Serial.begin(115200);
  Serial.println();
  Serial.println("Starting :-)");  
  WiFiInit();
  screentimeout=50000;
 }

void loop(void) {  
  server.handleClient();
  clok();
  if (millis()>screencur+screentimeout){
   screentimeout=screentimeoutr; 
   screenoff();
  }
}