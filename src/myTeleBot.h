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

#define BOTtoken "947749033:AAF00_fgJ0JTYF2XsZE_0zbz-8aZwtdHb-M"
//#define BOTname "Lz42-8266"
//#define BOTusername "Lz428266Bot"

BearSSL::WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client); 
 
String Esp32Clock="Lz42Esp32Clock";
String S868 ="519049530";
String addme="=947749033=";
int Bot_mtbs = 1000; 
long Bot_lasttime;   
bool Start = false;

const int ledPin = 13;
int ledStatus = 0; 

void sendtobot(String ch_id, String mess){
  String m="="+ch_id+"="+mess;
  bot.sendMessage(S868, m, "");
}

void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i=0; i<numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "") from_name = "Неизвестный";

    if (text == "/b0") {
      Button(0);
      bot.sendMessage(chat_id, "Button 0", "");
    }

    if (text == "/b1") {
      Button(1);
      bot.sendMessage(chat_id, "Button 1", "");
    }

    if (text == "/b2") {
      Button(2);
      bot.sendMessage(chat_id, "Button 2", "");
    }
    
    if (text.indexOf("/send")==0) {
      String sa1 = getValue(text,' ',1);
      String sa2 = getValue(text,' ',2);
      String sa3 = getValue(text,' ',3);
      String sa4 = getValue(text,' ',4);      
      sendtobot(Esp32Clock,sa1+' '+sa2+' '+sa3+' '+sa4+addme);
      bot.sendMessage(chat_id, "Sending!", "");      
    }

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
      bot.sendMessage(chat_id, from_name+", I'm beeping, ", "");
    }
    if (text == "/chat") {
      beep(250,125);
      bot.sendMessage(chat_id, from_name+", "+chat_id, "");
    }

    if (getValue(text,' ',0) == "/int") {
      String sa = getValue(text,' ',1);
      int q=sa.toInt();
      myButtonReInit(q);
      beep(250,125);
      bot.sendMessage(chat_id, from_name+" "+sa, "");
    }

    if (text == "/status") {
      String mess="";
      mess+="Bu 0 - "+String(getButton(0))+"\n";
      mess+="Bu 1 - "+String(getButton(1))+"\n";
      mess+="Bu 2 - "+String(getButton(2))+"\n";
      bot.sendMessage(chat_id, from_name+",\n"+mess, "");
    }
     
    if (text == "/reboot") {
      String mess="System is going to reboot NOW!";
      bot.sendMessage(chat_id, from_name+",\n"+mess, "");
      //yield(2000);
      //ESP.restart(); //циклический ребут начинается - не отмечает сообщение
    }

    if (text == "/start") {
      String welcome = "Arduino 8266 UNO Bot, " + from_name + ".\n";
      welcome += "/b1 : to switch the button N\n";
      welcome += "/beep : to beep\n";
      welcome += "/chat : to return chat_id\n";
      welcome += "/bud ? : to see ringer\n";
      welcome += "/bud 18 00 : to set ringer\n";
      welcome += "/status : Returns current status of buttons\n";
      bot.sendMessage(chat_id, welcome, "Markdown");
    }
  }
 } 

void MyTeleBotInit(void){
  client.setInsecure(); // иначе не соединяется без этой команды
 } 

void goBot(void){
    if (millis() > Bot_lasttime + Bot_mtbs)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    while(numNewMessages) {
      //Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    Bot_lasttime = millis();
  } 
 }



#endif