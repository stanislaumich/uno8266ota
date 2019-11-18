#define common

#define pinp D2

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
void initCommon(void){
  pinMode(pinp,OUTPUT);
  digitalWrite(pinp,LOW);
 }
