#ifndef myButton
 #define myButton

#ifndef common
 #include "common.h"
 #endif 
#include <Arduino.h>
const byte buttonpin=12;//NODEMCU_D6; //gpio12

volatile bool redbutton;
/*
ICACHE_RAM_ATTR void myEventListener() {
redbutton=true; //
//beep(125,125);
}
*/
void myButtonInit(void){
 pinMode(buttonpin, INPUT);
 //attachInterrupt(digitalPinToInterrupt(buttonpin), myEventListener, CHANGE);// RISING FALLING CHANGE
 
}

void myButtonReInit(int q){
 //detachInterrupt(buttonpin);
 //buttonpin=q;
 //pinMode(buttonpin, INPUT);
 //attachInterrupt(buttonpin, myEventListener, RISING);// RISING FALLING CHANGE
}

bool myButtonWork(void){
  redbutton=digitalRead(buttonpin);  
  if(redbutton){redbutton=false;return true;}else{return false;}
 }
 
 

 #endif