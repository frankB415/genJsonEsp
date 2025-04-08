#include <WebServer.h>

WebServer server2(80);

/* *********************************************
*/
void webServer2_init() {
  // webserver starten
  server2.on("/", wwwHandleRoot);
  server2.begin();
  Serial.println("Web Server listening");
}

/* *********************************************
*/
void webServer2_run() {
  server2.handleClient();
}

/* *********************************************
*/
void prepareHeaderJson() {
  //https://www.esp8266.com/viewtopic.php?f=8&t=16830&start=4
  server2.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server2.sendHeader("Pragma", "no-cache");
  server2.sendHeader("Expires", "-1");
  server2.setContentLength(CONTENT_LENGTH_UNKNOWN);
  server2.send(200, "application/json; charset=UTF-8", "");
}

/* *********************************************
*/
void wwwHandleRoot() {
  prepareHeaderJson();
  String str = myStruct1_t_json(&myStruct1);
  server2.sendContent(str);
  server2.sendContent(F(""));  // this tells web client that transfer is done
  server2.client().stop();
}
