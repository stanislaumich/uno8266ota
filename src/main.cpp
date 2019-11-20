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

void loop(void) {
  if (millis() > Bot_lasttime + Bot_mtbs)  {
    Serial.println("Bot time");
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
   
    while(numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    Serial.println("Bot time stop");
    Bot_lasttime = millis();
  } 
  /////////////////////////


  httpServer.handleClient();
  clok();
  if (millis()-interval1>prevmillis){
    prevmillis=millis();
    Serial.print(hour);Serial.print(":");
    Serial.print(mins);Serial.print(":");
    Serial.println(sec);    
  }

   
}