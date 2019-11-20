#ifndef MyTeleBot
#define MyTeleBot
//#ifndef myWiFi
// #include "myWiFi.h"
// #endif
//#define USING_AXTLS
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

//#include "WiFiClientSecureAxTLS.h"
//using namespace axTLS;
#include <UniversalTelegramBot.h>

#define BOTtoken "947749033:AAF00_fgJ0JTYF2XsZE_0zbz-8aZwtdHb-M"  //token of FlashledBOT
//#define BOTname "Lz42-8266"
//#define BOTusername "Lz428266Bot"

BearSSL::WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client); 
 
int Bot_mtbs = 1000; //mean time between scan messages
long Bot_lasttime;   //last time messages' scan has been done
bool Start = false;

const int ledPin = 13;
int ledStatus = 0; 

void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i=0; i<numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "") from_name = "Guest";

    if (text == "/ledon") {
      digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
      ledStatus = 1;
      bot.sendMessage(chat_id, "Led is ON", "");
    }

    if (text == "/ledoff") {
      ledStatus = 0;
      digitalWrite(ledPin, LOW);    // turn the LED off (LOW is the voltage level)
      bot.sendMessage(chat_id, "Led is OFF", "");
    }

    if (text == "/status") {
      if(ledStatus){
        bot.sendMessage(chat_id, "Led is ON", "");
      } else {
        bot.sendMessage(chat_id, "Led is OFF", "");
      }
    }

    if (text == "/start") {
      String welcome = "Welcome to Universal Arduino Telegram Bot library, " + from_name + ".\n";
      welcome += "This is Flash Led Bot example.\n\n";
      welcome += "/ledon : to switch the Led ON\n";
      welcome += "/ledoff : to switch the Led OFF\n";
      welcome += "/status : Returns current status of LED\n";
      bot.sendMessage(chat_id, welcome, "Markdown");
    }
  }
} 

void MyTeleBotInit(void){
  //pinMode(ledPin, OUTPUT); // initialize digital pin 2 as an output.
  client.setInsecure(); 
} 





#endif