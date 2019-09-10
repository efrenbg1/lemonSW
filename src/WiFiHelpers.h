#ifndef WiFiHelpers_H
#define WiFiHelpers_H

#include "headers.h"

const char* wl_status_to_string(wl_status_t status) {
  switch (status) {
    case WL_NO_SHIELD: return "WL_NO_SHIELD";
    case WL_IDLE_STATUS: return "WL_IDLE_STATUS";
    case WL_NO_SSID_AVAIL: return "WL_NO_SSID_AVAIL";
    case WL_SCAN_COMPLETED: return "WL_SCAN_COMPLETED";
    case WL_CONNECTED: return "WL_CONNECTED";
    case WL_CONNECT_FAILED: return "WL_CONNECT_FAILED";
    case WL_CONNECTION_LOST: return "WL_CONNECTION_LOST";
    case WL_DISCONNECTED: return "WL_DISCONNECTED";
  }
}

bool wifi_boot(String ssid, String pw){
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pw);
    digitalWrite(LED, LOW);
    Serial.print("Connecting to wifi...");
    int timeout = 0;
    while (WiFi.status() != WL_CONNECTED){
        timeout++;
        yield();
        if(timeout > 45){
            return false;
        }
        delay(250);
        digitalWrite(LED, HIGH);
        Serial.print(".");
        delay(250);
        digitalWrite(LED, LOW);
    }
    digitalWrite(LED, HIGH);
    Serial.println("Connected.");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    return true;
}

#endif