#define SettingsWiFi
#include <WiFi.h>
#include <WiFiClient.h>
#ifndef Common
 #include "common.h"
#endif
#include <esp_wifi.h> 
#ifndef MyWebServer
 #include "MyWebServer.h"
#endif

const char* ssid2 = "SAN";
const char* password2 = "37212628";
const char* ssid1 = "ZTE54";
const char* password1 = "121211119";
const int WiFiTimeout = 5000;// ms

IPAddress ip(192,168,1,234);  
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);
IPAddress dns1(194,158,196,137);
IPAddress dns2(194,158,196,141);

unsigned long int tm;



String getSsidPass( String s ){
  String val = "NONE";  // if invalid, returns "NONE"
  s.toUpperCase();
  if( s.compareTo("SSID") == 0 )
  {
    wifi_config_t conf;
    esp_wifi_get_config(WIFI_IF_STA, &conf);
    val = String(reinterpret_cast<const char*>(conf.sta.ssid));
   }
  if( s.compareTo("PASS") == 0 )
   {
    wifi_config_t conf;
    esp_wifi_get_config(WIFI_IF_STA, &conf);
    val = String(reinterpret_cast<const char*>(conf.sta.password));
   }
  return val;
 }

void WiFiInit(void){
  WiFi.mode(WIFI_AP_STA);
  WiFi.config(ip, gateway, subnet, dns1, dns2);
  WiFi.begin(ssid1, password1);
  addds((String)"Conn to "+(String)ssid1);
  //addds(ssid1);
  tm=millis();
  ////////////////////////////////
  while ((WiFi.waitForConnectResult() != WL_CONNECTED) and (millis()<tm+ WiFiTimeout)){
   }
  if (!WiFi.isConnected()){
    tm=millis();
    WiFi.begin(ssid2, password2);
    addds((String)"Conn to "+(String)ssid2);
    //addds(ssid2);
    while ((WiFi.waitForConnectResult() != WL_CONNECTED) and (millis()<tm+ WiFiTimeout)){
     } 
 }
 ///////////////////////////////
   if (WiFi.isConnected()){
    IPAddress myIP = WiFi.localIP();    
    Serial.print("My IP address: ");
    Serial.println(myIP);  
    mIP=String(myIP[0])+String(".");
    mIP=mIP+String(myIP[1])+String(".");
    mIP=mIP+String(myIP[2])+String(".");
    mIP=mIP+String(myIP[3]);
    fStr1=mIP;//+" "+getSsidPass("SSID");
    initWebServer();
    addds("Connected.");
    Serial.println("Ready! Open http://192.168.1.234 in your browser");
    //addds("Starting UDP");
    udp.begin(localPort);
    //addds("UDP started.");
    beep(200,1000);
   }
   else{
     clrscr();
     fStr1="ERROR";
     addds("WiFi Failed :-(");
     beep(200,1000);
     delay(200);
     beep(200,1000);
     delay(200);
     beep(200,1000);
     delay(200);
    }
   
 

 }