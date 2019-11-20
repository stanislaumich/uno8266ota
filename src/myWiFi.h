#define myWiFi
#include <ESP8266WiFi.h>
//#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include "place.h"


#ifdef home
#ifndef STASSID
#define STASSID "ZTE54"
#define STAPSK  "121211119"
#endif
IPAddress ip(192,168,1,234);  
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);
IPAddress dns1(194,158,196,206);
IPAddress dns2(194,158,196,205);
#endif
#ifdef work
#ifndef STASSID
#define STASSID "SAN"
#define STAPSK  "37212628"
#endif
IPAddress ip(192,168,0,234);  
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,255,0);
IPAddress dns1(194,158,196,137);
IPAddress dns2(194,158,196,141);
#endif


const char* ssid = STASSID;
const char* password = STAPSK;

void MyWiFiInit(void){
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP("Uno266-234");
  WiFi.config(ip, gateway, subnet, dns1, dns2);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
    Serial.println("WiFi failed, retrying...");
  }
 }

 String IP_to_String(IPAddress ip)
{
  return(String(ip[0])+"."+String(ip[1])+"."+String(ip[2])+"."+String(ip[3]));
}

IPAddress String_to_IP(String strIP)
{
int Parts[4] = {0,0,0,0};
int Part = 0;
for ( byte i=0; i<strIP.length(); i++ )
{
  char c = strIP.charAt(i);
  if ( c == '.' )
  {
    Part++;
    continue;
  }
  if ( c<48 || c>57 ) continue; // не цифровой символ
   
  Parts[Part] *= 10;
  Parts[Part] += c - '0';
}
IPAddress ip_str( Parts[0], Parts[1], Parts[2], Parts[3] );
return(ip_str);
}