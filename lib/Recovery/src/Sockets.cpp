#include "Recovery.h"

String Recovery::scan_wifi(void){
  String wifi_list = "";
  int n = WiFi.scanNetworks();
  if (n == 0) {
    wifi_list = "None";
  } else {
    for (int i = 0; i < n; ++i) {
      wifi_list += String(WiFi.SSID(i));
      wifi_list += "/";
      wifi_list += String(WiFi.RSSI(i));
      wifi_list += "#";
      delay(10);
    }
  }
  return wifi_list;
}

void Recovery::root(void) {
    timeout = millis();
    server->send_P(200, "text/html", index_html);
}


void Recovery::scan(void) {
  timeout = millis();
  server->send(200, "text/plain", scan_wifi());
}


void Recovery::test(void) {
  timeout = millis();
  server->send(200, "text/plain", "OK");
  ssid = server->arg("ssid");
  wifi_pw = server->arg("pass");
  delay(1000);
  WiFi.disconnect();
  WiFi.begin((ssid).c_str(), (wifi_pw).c_str());
}

void Recovery::check_wifi(void){
  timeout = millis();
  delay(200);
  if (WiFi.status() != WL_CONNECTED){
    server->send(200, "text/plain", ".");
  } else {
    server->send(200, "text/plain", WiFi.SSID());
  }
}


void Recovery::mqtls_check(void){
  timeout = millis();
  user = server->arg("user");
  pw = server->arg("pw");
  server->send(200, "text/plain", String(mqtls->connect("rmote.app", 2443, user, pw, "95")));
}

void Recovery::save(void){
  timeout = millis();
  if(WiFi.status() == WL_CONNECTED && wifi_pw.length() < 64 && ssid.length() < 33 && user.length() < 31 && pw.length() < 27) {
     if(vault->save(ssid, wifi_pw, user, pw)){
     server->send(200, "text/plain", "OK");
     } else {
       server->send(200, "text/plain", "Error");
     }
  } else {
    server->send(200, "text/plain", "Error");
  }
  }

void Recovery::reboot(void){
server->send_P(200, "text/html", reboot_html);
delay(5000);
Serial.println("Rebooting...");
  ESP.restart();
}

void Recovery::off_wifi(void){
  timeout = millis();
  WiFi.disconnect();
}