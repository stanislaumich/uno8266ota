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
#ifndef myButton
 #include "myButton.h"
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
 
#ifndef mySSDP
  #include "mySSDP.h"
 #endif 


void setup(void) {
  initCommon();
  beep(125,50);
  Serial.begin(115200);
  Serial.println();
  Serial.println("Booting Sketch...");
  MyWiFiInit();
  MyTimeInit();
  MySSDPInit();
  MyWebinit();
  MyTeleBotInit();
  bot.sendMessage(myTele, "Бот запущен: "+IP_to_String(WiFi.localIP()), "");
  beep(125,50);
   delay(50);
  beep(125,50); 
}



void loop(void) {
  goBot();
  httpServer.handleClient();
  clok();
  goSerialTime();
  if (myButtonWork()){bot.sendMessage(myTele, "Button!!!!", "");}   
}