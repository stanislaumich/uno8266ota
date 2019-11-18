#define MyWebServer
#include <WebServer.h>
#include <Update.h>
#include "SPIFFS.h"
#include "FS.h"
#include "MyTime.h"
#ifndef Common
 #include "common.h"
#endif 
//#define FS_NO_GLOBALS
WebServer server(80);
File fsUploadFile;
String XML;
const char* serverIndex = "<form method='POST' action='/update' enctype='multipart/form-data'><input type='file' name='update'><input type='submit' value='Update'></form>";
//////////////////////////////////////////////

void FS_init(void){ 
  SPIFFS.begin();
  addds("SPIFFS.begin()");
  prefs.begin("alarm_h",false);
  prefs.begin("alarm_m",false);
 }

String getContentType(String filename) {
  if (server.hasArg("download")) return "application/octet-stream";
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
    size_t sent = server.streamFile(file, contentType);
    file.close();
    return true;
  }
  return false;
 }

void handleFileUpload() {
  addds("Upload file");
  if (server.uri() != "/edit") return;
  HTTPUpload& upload = server.upload();
  if (upload.status == UPLOAD_FILE_START) {
    String filename = upload.filename;
    if (!filename.startsWith("/")) filename = "/" + filename;
    fsUploadFile = SPIFFS.open(filename, "w");
    filename = String();
  } else if (upload.status == UPLOAD_FILE_WRITE) {
    //DBG_OUTPUT_PORT.print("handleFileUpload Data: "); DBG_OUTPUT_PORT.println(upload.currentSize);
    if (fsUploadFile)
      fsUploadFile.write(upload.buf, upload.currentSize);
  } else if (upload.status == UPLOAD_FILE_END) {
    if (fsUploadFile)
      fsUploadFile.close();
  }
 }

void handleFileDelete() {
  addds("Delete file");
  if (server.args() == 0) return server.send(500, "text/plain", "BAD ARGS");
  String path = server.arg(0);
  if (path == "/")
    return server.send(500, "text/plain", "BAD PATH");
  if (!SPIFFS.exists(path))
    return server.send(404, "text/plain", "FileNotFound");
  SPIFFS.remove(path);
  server.send(200, "text/plain", "");
  path = String();
 }
void handleFileCreate() {
  addds("Create file");
  if (server.args() == 0)
    return server.send(500, "text/plain", "BAD ARGS");
  String path = server.arg(0);
  if (path == "/")
    return server.send(500, "text/plain", "BAD PATH");
  if (SPIFFS.exists(path))
    return server.send(500, "text/plain", "FILE EXISTS");
  File file = SPIFFS.open(path, "w");
  if (file)
    file.close();
  else
    return server.send(500, "text/plain", "CREATE FAILED");
 server.send(200, "text/plain", "");
  path = String();  
 }


void handleFileList() {  
  if (!server.hasArg("dir")) {
    server.send(500, "text/plain", "BAD ARGS");
    return;
  }
  // https://techtutorialsx.com/2019/02/24/esp32-arduino-listing-files-in-a-spiffs-file-system-specific-path/
  String path = server.arg("dir");
  File dir = SPIFFS.open(path);
  path = String();
  String output = "[";
  while (File entry=dir.openNextFile()) {
    //File entry = dir.openNextFile();
    if (output != "[") output += ',';
    bool isDir = false;
    output += "{\"type\":\"";
    output += (isDir) ? "dir" : "file";
    output += "\",\"name\":\"";
    output += String(entry.name()).substring(1);
    output += "\"}";
    entry.close();
  }
  output += "]";  
  server.send(200, "text/json", output);
 }



String millis2time(){
  String Time="";
  unsigned long ss;
  byte mm,hh;
  ss=millis()/1000;
  hh=ss/3600;
  mm=(ss-hh*3600)/60;
  ss=(ss-hh*3600)-mm*60;
  if(hh<10)Time+="0";
  Time+=(String)hh+":";
  if(mm<10)Time+="0";
  Time+=(String)mm+":";
  if(ss<10)Time+="0";
  Time+=(String)ss;
  return Time;
 }



void handle_Button() {
  int state = server.arg("state").toInt();
  Button(state);
  server.sendHeader("Connection", "close");
  server.send(200, "text/plain", "Ok");  
 }

String alert_h(){
  String Time ="";
  int m=0;
  int h=0;
  h = prefs.getInt("alarm_h", 0);
  m = prefs.getInt("alarm_m",0);
  Time+= (String)h+":";
  Time+= (String)m; 
  return Time;
 }

String XmlTime(void) {
  String Time ="";
  uint16_t m = ( ntp_time / 60 ) % 60;
  uint16_t h = ( ntp_time / 3600 ) % 24;
  Time+= (String)h+":";
  Time+= (String)m; 
  return Time;
 }

void handlebeep(void){
  int t1 = server.arg("t1").toInt();
  int t2 = server.arg("t2").toInt();
  beep(t1,t2);
  server.sendHeader("Connection", "close");
  server.send(200, "text/plain", "Ok beep "); 
 }  
void handle_Time() {
  int h = server.arg("h").toInt();
  int m = server.arg("m").toInt();
  String Time ="";
  Time+= (String)h+":";
  Time+= (String)m; 
  size_t q1 = prefs.putInt("alarm_h", h);
  size_t q2 = prefs.putInt("alarm_m", m);
  h = prefs.getInt("alarm_h",0);
  m = prefs.getInt("alarm_m", 0);
  Time="";
  Time+= (String)h+":";
  Time+= (String)m; 
 }
void buildXML(){
  XML="<?xml version='1.0'?>";
  XML+="<Donnees>"; 
    XML+="<response>";
    XML+=millis2time();
    XML+="</response>";
    XML+="<alert_time>";
    XML+=alert_h();
    XML+="</alert_time>";
    XML+="<time>";
    XML+=XmlTime();
    XML+="</time>";
    XML+="<b0>";
    XML+=XMLb0;
    XML+="</b0>";
    XML+="<b1>";
    XML+=XMLb1;
    XML+="</b1>";
    XML+="<b2>";
    XML+=XMLb2;
    XML+="</b2>";
  XML+="</Donnees>"; 
 }
void handleXML(){
  buildXML();
  server.send(200,"text/xml",XML);
 }
void handlereboot(){
  String s="Rebooting, refresh page";
  server.send(200,"text/html",s);
  ESP.restart();
 }
void handleShowTime(void){
  screentimeout=50000;
  String s="Long time ago...";
  addds(s);
  server.sendHeader("Connection", "close");
  server.send(200,"text/html",s);
 }
void initWebServer(void){
  addds("initWebServer");
  server.on("/reboot",handlereboot);
  server.on("/xml",handleXML);
  server.on("/list", HTTP_GET, handleFileList);
  server.on("/Time", HTTP_GET, handle_Time);
  server.on("/Button", handle_Button);
  server.on("/beep",handlebeep);
  server.on("/time",handleShowTime);
  server.on("/edit", HTTP_GET, []() {
    if (!handleFileRead("/edit.htm")) server.send(404, "text/plain", "FileNotFound");
  });
  //Создание файла
  server.on("/edit", HTTP_PUT, handleFileCreate);
  //Удаление файла
  server.on("/edit", HTTP_DELETE, handleFileDelete);
  //first callback is called after the request has ended with all parsed arguments
  //second callback handles file uploads at that location
  server.on("/edit", HTTP_POST, []() {
    server.sendHeader("Connection", "close");//my
    server.send(200, "text/plain", "");
  }, handleFileUpload);
   /////////////////////
   server.onNotFound([]() {
    if (!handleFileRead(server.uri()))
      server.send(404, "text/plain", "FileNotFound");      
  });
  ///////////////////////
    server.on("/update", HTTP_POST, []() {      
      server.sendHeader("Connection", "close");
      server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
      ESP.restart();
    }, []() {
      HTTPUpload& upload = server.upload();
      if (upload.status == UPLOAD_FILE_START) {
        Serial.setDebugOutput(true);
        Serial.printf("Update: %s\n", upload.filename.c_str());
        beep(200,50);
        fStr="UPDATING.....";
        addds(upload.filename.c_str());
        addds("");
        addds("");
        addds("Wait....");
        //wrds();
        if (!Update.begin()) { //start with max available size
          Update.printError(Serial);
        }
      } else if (upload.status == UPLOAD_FILE_WRITE) {
        if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
          Update.printError(Serial);
        }
      } else if (upload.status == UPLOAD_FILE_END) {
        if (Update.end(true)) { //true to set the size to the current progress
          Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
        } else {
          Update.printError(Serial);
        }
        Serial.setDebugOutput(false);
      } else {
        Serial.printf("Update Failed Unexpectedly (likely broken connection): status=%d\n", upload.status);
      }
    });

    server.begin();
    addds("begin WebServer");
 }