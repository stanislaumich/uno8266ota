//#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <fs.h>
#ifndef common
 #include "common.h"
#endif 
#ifndef myWiFi
 #include "myWiFi.h"
#endif


ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;

String getContentType(String filename) {
  if (httpServer.hasArg("download")) return "application/octet-stream";
  else if (filename.endsWith(".htm")) return "text/html";
  else if (filename.endsWith(".html")) return "text/html";
  else if (filename.endsWith(".css")) return "text/css";
  else if (filename.endsWith(".js")) return "application/javascript";
  else if (filename.endsWith(".png")) return "image/png";
  else if (filename.endsWith(".gif")) return "image/gif";
  else if (filename.endsWith(".jpg")) return "image/jpeg";
  else if (filename.endsWith(".ico")) return "image/x-icon";
  else if (filename.endsWith(".xml")) return "text/xml";
  else if (filename.endsWith(".pdf")) return "application/x-pdf";
  else if (filename.endsWith(".zip")) return "application/x-zip";
  else if (filename.endsWith(".gz")) return "application/x-gzip";
  return "text/plain";
 }


bool handleFileRead(String path) {  
  if (path.endsWith("/")) path += "index.htm";
  String contentType = getContentType(path);
  String pathWithGz = path + ".gz";
  
  if (SPIFFS.exists(pathWithGz) || SPIFFS.exists(path)) {
    if (SPIFFS.exists(pathWithGz))
      path += ".gz";
    File file = SPIFFS.open(path, "r");
    size_t sent = httpServer.streamFile(file, contentType);
    file.close();
    return true;
  }
  
  return false;
 }





void MyWebinit(void){
  
  httpUpdater.setup(&httpServer);
 
  


  httpServer.onNotFound([]() {
    if (!handleFileRead(httpServer.uri()))
      httpServer.send(404, "text/plain", "FileNotFound");      
  });


  httpServer.begin();
  //Serial.println(WiFi.localIP);
  Serial.print("HTTPUpdateServer ready! Open http://192.168.1.234/update in your browser\n");
 }