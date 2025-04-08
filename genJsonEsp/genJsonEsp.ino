// based on https://www.upesy.com/blogs/tutorials/how-to-connect-wifi-acces-point-with-esp32?srsltid=AfmBOoqek9YW4WWalHubtv7UCIRTNpTov-4Oxabz3SuVlXodg3P6zmHw


#include <WiFi.h>
#include "wlan_credicals.h"

struct myStruct1_t {
  String ip = "";
  unsigned long millis;
  int i1 = 4321;
  struct {
    String s2 = "s2";
    int i2 = 234;
  } nestedStruct;
  int arr1[3][2] = { 3,2,1 , 5,4,3 }; 
  struct{
      int i3;
      bool b1 = true;
      String s3 = "g";
  }  nestedStruct2 [2] = { 3 , true , "three" , 4 , false , "four" }; 

} myStruct1;


void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFi.setHostname("genJsonEsp"); //define hostname
  WiFi.mode(WIFI_STA);
  WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
  WiFi.begin(WLANSSID1, WLANPASS1);
  Serial.println("\nConnecting");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }

  Serial.println("\nConnected to the WiFi network");
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());

  webServer2_init();
}

void loop() {
  webServer2_run();
  myStruct1.ip = WiFi.localIP().toString();
  myStruct1.millis = millis();
}
