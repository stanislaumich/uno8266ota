#define common
#include <EEPROM.h>
#define pinp D2

int XMLb0;
int XMLb1;
int XMLb2;

void beep(int t1,int t2){
 unsigned long h;
  h=millis();
  while (millis()-h<t1){
   digitalWrite(pinp,HIGH);
   delayMicroseconds(t2);
   digitalWrite(pinp,LOW);
   delayMicroseconds(t2);
  }
 }

void mLog(String s){
  Serial.println(s);
 }

void Button(int state){
 switch (state) {
    case 2:
      //digitalWrite(rele1, HIGH);
      //digitalWrite(rele2, LOW);
      //digitalWrite(rele3, HIGH);
      mLog("State 2 switched");
      XMLb2?XMLb2=0:XMLb2=1;
      EEPROM.write(10+state,XMLb2);
      EEPROM.commit();
      break;
    case 1:
      //digitalWrite(rele1, LOW);
      //digitalWrite(rele2, HIGH);
      //digitalWrite(rele3, HIGH);
      mLog("State 1 switched");
      XMLb1?XMLb1=0:XMLb1=1;
      EEPROM.write(10+state,XMLb1);
      EEPROM.commit();
      break;
    case 0:
      //digitalWrite(rele1, HIGH);
      //digitalWrite(rele2, HIGH);
      //digitalWrite(rele3, HIGH);
      mLog("State 0 switched");
      XMLb0?XMLb0=0:XMLb0=1;
      EEPROM.write(10+state,XMLb0);
      EEPROM.commit();
      break;
  }
 } 

void initCommon(void){
  EEPROM.begin(512);
  XMLb0=EEPROM.read(10);
  XMLb1=EEPROM.read(11);
  XMLb2=EEPROM.read(12);
  pinMode(pinp,OUTPUT);
  digitalWrite(pinp,LOW);
 }
 int getButton(int b){
  return EEPROM.read(10+b);
  }
