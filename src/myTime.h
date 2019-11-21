#define myTime
#ifndef common
 #include "common.h"
#endif 
#ifndef myWiFi
 #include "myWiFi.h"
#endif
#ifndef MyTeleBot
  #include "myTeleBot.h"
 #endif
#include <WiFiUdp.h>
#include <EEPROM.h>

unsigned long localPort = 2390;  
unsigned long ntp_time = 0;
long  t_correct        = 0;
unsigned long cur_ms   = 0;
unsigned long ms1      = 0;
unsigned long ms2      = 10000000UL;
unsigned long t_cur    = 0;
bool          points   = true;
unsigned int err_count = 0;
int gh;
int gm;
char* wd[7]={"SU","MO","TU","WE","TH","FR","SA"};
int weekday;
uint8_t hour, mins, sec;
bool z=true;
#define TIMEZONE 3
String timestr;
int budilo=0;

IPAddress timeServerIP; 
const char* ntpServerName = "time.nist.gov";
const int NTP_PACKET_SIZE = 48; 
byte packetBuffer[NTP_PACKET_SIZE]; 
WiFiUDP udp;
unsigned long prevmillis;
#define interval1 1000

  // Каждые 0.5 секунды выдаем время
void DisplayTime(void) {
  uint16_t m = ( ntp_time / 60 ) % 60;
  uint16_t h = ( ntp_time / 3600 ) % 24;
  
  int th = EEPROM.read(0);
  int tm = EEPROM.read(1);  
  if (th == h && tm == m && budilo<3) {
    //addds("ALARMA!!!!");
    Serial.write("ALARMA!!!!");
    beep(200,250);
    delay(300);
    beep(200,250);
    delay(300);
    beep(200,250);
    delay(300);
    budilo++;
  }
  else{budilo=0;}
  if (gm!=m){
    String Time ="";
    if (h<10){Time+= "0"+(String)h+":";}else{Time+= (String)h+":";}
    if (m<10){Time+= "0"+(String)m;}else{Time+= (String)m;} 
    timestr=Time+(String)" "+(String)wd[weekday];
    Serial.println(timestr);
    //addds(timestr);    
    }
  if ((m==0)&&(gh!=h)){beep(150,125);z=true;bot.sendMessage(myTele, "Zero Time!!", "");}  
  if ((m==30)&&(z)){beep(150,50);delay(50);beep(150,50);z=false;}  
  gh=h;
  gm=m;
  
 }


unsigned long sendNTPpacket(IPAddress& address) {
  Serial.println("sending NTP packet...");
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  packetBuffer[0] = 0b11100011;   
  packetBuffer[1] = 0;     
  packetBuffer[2] = 6;     
  packetBuffer[3] = 0xEC;  
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;
  udp.beginPacket(address, 123);
  udp.write(packetBuffer, NTP_PACKET_SIZE);
  udp.endPacket();
  return 0;  
 }


bool GetNTP(void) {
  WiFi.hostByName(ntpServerName, timeServerIP);
  sendNTPpacket(timeServerIP);
  delay(1000);
  int cb = udp.parsePacket();
  if (!cb) {
    Serial.println("No packet yet");
    return false;
  }
  else {
    Serial.print("packet received, length=");
    Serial.println(cb);
    udp.read(packetBuffer, NTP_PACKET_SIZE);
    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
    // Конвертируем два слова в переменную long
    unsigned long secsSince1900 = highWord << 16 | lowWord;
    // Конвертируем в UNIX-таймстамп (число секунд от 01.01.1970
    const unsigned long seventyYears = 2208988800UL;
    unsigned long epoch = secsSince1900 - seventyYears;
    // Делаем поправку на местную тайм-зону
    ntp_time = epoch + TIMEZONE * 3600;
    weekday=(epoch/60/60/24+4)%7; // day week, 0-sunday
    //Serial.print("Unix time = ");
    //Serial.println(ntp_time);
  }
  return true;
 }


void clok() {
  cur_ms       = millis();
  t_cur        = cur_ms / 1000;
  // Каждые 60 секунд считываем время в интернете
  if ( cur_ms < ms2 || (cur_ms - ms2) > 60000 ) {
    err_count++;
    // Делаем три  попытки синхронизации с интернетом
    if ( GetNTP() ) {
      ms2       = cur_ms;
      err_count = 0;
      t_correct = ntp_time - t_cur;
    }
  }
  if ( cur_ms < ms1 || (cur_ms - ms1) > 500 ) {
    ms1 = cur_ms;
    ntp_time    = t_cur + t_correct;
    mins = ( ntp_time / 60 ) % 60;
    hour = ( ntp_time / 3600 ) % 24;
    sec=ntp_time % 60;
    points = !points;
   }
   DisplayTime();  
 }


void goSerialTime(void){
  if (millis()-interval1>prevmillis){
    prevmillis=millis();
    Serial.print(hour);Serial.print(":");
    Serial.print(mins);Serial.print(":");
    Serial.println(sec);    
   }
 }

void MyTimeInit(void){
     udp.begin(localPort);
}

