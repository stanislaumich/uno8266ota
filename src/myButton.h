#ifndef myButton
 #define myButton

#ifndef common
 #include "common.h"
 #endif 

int buttonpin=10; //gpio12

volatile bool redbutton;

ICACHE_RAM_ATTR void myEventListener() {
redbutton=true; //
beep(125,125);
}

void myButtonInit(void){
 pinMode(buttonpin, INPUT);
 attachInterrupt(buttonpin, myEventListener, RISING);// RISING FALLING CHANGE
}

void myButtonReInit(int q){
 detachInterrupt(buttonpin);
 buttonpin=q;
 pinMode(buttonpin, INPUT);
 attachInterrupt(buttonpin, myEventListener, RISING);// RISING FALLING CHANGE
}

bool myButtonWork(void){

 //digitalRead(buttonpin)?b= true:b= false;
 return redbutton;
 redbutton=false;
}

 #endif