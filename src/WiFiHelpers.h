#ifndef WiFiHelpers_H
#define WiFiHelpers_H

#include "headers.h"

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