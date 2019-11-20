/*
  To upload through terminal you can use: curl -F "image=@firmware.bin" esp8266-webupdate.local/update
*/
#include <ESP8266WiFi.h>
//#include <WiFiClient.h>
#include <WiFiClientSecure.h>
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
#ifndef myTime
 #include "myTime.h"
 #endif
#ifndef MyTeleBot
  #include "myTeleBot.h"
 #endif
unsigned long prevmillis;
#define interval1 1000


void setup(void) {
  initCommon();
  beep(125,50);
  Serial.begin(115200);
  Serial.println();
  Serial.println("Booting Sketch...");
  MyWiFiInit();
  MyTimeInit();
  MyWebinit();
  MyTeleBotInit();
  beep(125,50); 
}

void goSerialTime(void){
if (millis()-interval1>prevmillis){
    prevmillis=millis();
    Serial.print(hour);Serial.print(":");
    Serial.print(mins);Serial.print(":");
    Serial.println(sec);    
  }
}

void loop(void) {
  goBot();
  httpServer.handleClient();
  clok();
  goSerialTime();   
}