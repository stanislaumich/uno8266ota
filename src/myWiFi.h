#define myWiFi

#ifndef STASSID
#define STASSID "SAN"
#define STAPSK  "37212628"
#endif

IPAddress ip(192,168,1,234);  
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);
IPAddress dns1(194,158,196,137);
IPAddress dns2(194,158,196,141);