/*
  To upload through terminal you can use: curl -F "image=@firmware.bin" esp8266-webupdate.local/update
*/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
////////////////
#ifndef common
 #include "common.h"
#endif 
#ifndef myWiFi
 #include "myWiFi.h"
#endif


const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;

void setup(void) {
  Serial.begin(9600);
  Serial.println();
  Serial.println("Booting Sketch...");
  WiFi.mode(WIFI_AP_STA);
  WiFi.config(ip, gateway, subnet, dns1, dns2);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
    Serial.println("WiFi failed, retrying.");
  }
  httpUpdater.setup(&httpServer);
  httpServer.begin();
  //Serial.println(WiFi.localIP);
  Serial.print("HTTPUpdateServer ready! Open http://192.168.1.234/update in your browser\n");
}

void loop(void) {
  httpServer.handleClient();
  
}