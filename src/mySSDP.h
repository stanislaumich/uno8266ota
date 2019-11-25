#ifndef mySSDP
  #define mySSDP
#include <ESP8266SSDP.h>
void MySSDPInit(void) {

  SSDP.setSchemaURL("description.xml");
  SSDP.setHTTPPort(80);
  SSDP.setName("Uno8266Clock1");
  SSDP.setSerialNumber("001788102201");
  SSDP.setURL("/");
  SSDP.setModelName("Uno8266Clock2");
  SSDP.setModelNumber("000000000001");
  SSDP.setModelURL("http://192.168.0.234");
  SSDP.setManufacturer("Lz42");
  SSDP.setManufacturerURL("http://192.168.0.234");
  SSDP.begin();
}
 #endif 