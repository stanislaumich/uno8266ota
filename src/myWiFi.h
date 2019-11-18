#define myWiFi
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#ifndef STASSID
#define STASSID "SAN"
#define STAPSK  "37212628"
#endif

IPAddress ip(192,168,0,234);  
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,255,0);
IPAddress dns1(194,158,196,137);
IPAddress dns2(194,158,196,141);


const char* ssid = STASSID;
const char* password = STAPSK;

void MyWiFiInit(void){
  WiFi.mode(WIFI_AP_STA);
  WiFi.config(ip, gateway, subnet, dns1, dns2);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
    Serial.println("WiFi failed, retrying...");
  }
 }