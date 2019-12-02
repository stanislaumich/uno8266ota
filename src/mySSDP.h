#ifndef mySSDP
  #define mySSDP
#include <ESP8266SSDP.h>

void MySSDPInit(void) {
    //Если версия  2.0.0 закoментируйте следующую строчку
  SSDP.setDeviceType("upnp:rootdevice");
  SSDP.setSchemaURL("description.xml");
  SSDP.setHTTPPort(80);
  SSDP.setName("Uno8266ClockOTA");
  SSDP.setSerialNumber("280119780945");
  SSDP.setURL("/");
  SSDP.setModelName("Uno8266ClockOTA1");
  SSDP.setModelNumber("000000000001");
  SSDP.setModelURL("http://192.168.0.234");
  SSDP.setManufacturer("Lz42");
  SSDP.setManufacturerURL("http://192.168.0.234");
  SSDP.begin();
}
 #endif 