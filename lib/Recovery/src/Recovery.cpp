#include "Recovery.h"

#define LED 2

Recovery::Recovery(unsigned int timeout_reboot, String pw, MqTLS* _mqtls, EzVault* _vault){
  timeout_reboot = timeout_reboot * 60 * 1000;
  digitalWrite(LED, LOW);
  WiFi.disconnect();
  delay(200);
  IPAddress ip(192,168,1,1);
  IPAddress gateway(192,168,1,2);
  IPAddress subnet(255,255,255,0);
  Serial.println("");
  Serial.println("Entering recovery...");
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig (ip, gateway, subnet);
  WiFi.softAP((WiFi.macAddress()).c_str(), pw.c_str());
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("HotSpot IP: ");
  Serial.println(myIP);
  ESP8266WebServer _server(80);
  ESP8266HTTPUpdateServer _httpUpdater(true);
  server = &_server;
  httpUpdater = &_httpUpdater;
  mqtls = _mqtls;
  vault = _vault;
  server->on("/", std::bind(&Recovery::root, this));
  server->on("/scan", std::bind(&Recovery::scan, this));
  server->on("/check", std::bind(&Recovery::check_wifi, this));
  server->on("/test", std::bind(&Recovery::test, this));
  server->on("/mqtt", std::bind(&Recovery::mqtls_check, this));
  server->on("/save", std::bind(&Recovery::save, this));
  server->on("/reboot", std::bind(&Recovery::reboot, this));
  server->on("/off", std::bind(&Recovery::off_wifi, this));
  httpUpdater->setup(server);
  server->begin();
  timeout = millis();
while(true){
  yield();
  server->handleClient();
  if((millis() - timeout) > timeout_reboot){
    digitalWrite(LED, HIGH);
    return;
  }
}
}