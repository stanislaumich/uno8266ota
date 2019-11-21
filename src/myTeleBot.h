#ifndef MyTeleBot
#define MyTeleBot
#ifndef common
  #include "common.h"
 #endif
#ifndef myTime
  #include "myTime.h"
 #endif 
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#define myTele "357390016"

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

    if (text == "/b0") {
      //digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
      //ledStatus = 1;
      Button(0);
      bot.sendMessage(chat_id, "Button 0", "");
    }

    if (text == "/b1") {
      //ledStatus = 0;
     // digitalWrite(ledPin, LOW);    // turn the LED off (LOW is the voltage level)
      Button(1);
      bot.sendMessage(chat_id, "Button 1", "");
    }

    if (text == "/b2") {
      //ledStatus = 0;
      //digitalWrite(ledPin, LOW);    // turn the LED off (LOW is the voltage level)
      Button(2);
      bot.sendMessage(chat_id, "Button 2", "");
    }
    
    //String part01 = getValue(application_command,';',0);
    if (text.indexOf("/bud")==0) {
      String sa = getValue(text,' ',1);
      String mess="\n";
      if (sa=="?"){
        int tph = getBud(0);
        int tpm = getBud(1);        
        mess+=String(tph)+":"+String(tpm);
      }else{
      String sh = getValue(text,' ',1);
      String sm = getValue(text,' ',2);
      setBud(sh.toInt(),sm.toInt());
      mess+="Установлено";
      }
      bot.sendMessage(chat_id, from_name+", "+mess, "");
    }

    if (text == "/beep") {
      beep(250,125);
      bot.sendMessage(chat_id, from_name+", I'm beeping, "/*+chat_id*/, "");
    }

    if (text == "/status") {
      String mess="";
      mess+="Bu 0 - "+String(getButton(0))+"\n";
      mess+="Bu 1 - "+String(getButton(1))+"\n";
      mess+="Bu 2 - "+String(getButton(2))+"\n";
      bot.sendMessage(chat_id, from_name+",\n"+mess, "");
    }

    if (text == "/start") {
      String welcome = "Welcome to Universal Arduino Telegram Bot library, " + from_name + ".\n";
      welcome += "This is Flash Led Bot example.\n\n";
      welcome += "/b1 : to switch the button N\n";
      welcome += "/beep : to beep\n";
      welcome += "/status : Returns current status of buttons\n";
      bot.sendMessage(chat_id, welcome, "Markdown");
    }
  }
} 

void MyTeleBotInit(void){
  //pinMode(ledPin, OUTPUT); // initialize digital pin 2 as an output.
  client.setInsecure(); 
} 

void goBot(void){
    if (millis() > Bot_lasttime + Bot_mtbs)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
   
    while(numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    Bot_lasttime = millis();
  } 
}



#endif