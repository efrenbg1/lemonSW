#include "GitUpdate.h"

#define LED 2

GitUpdate::GitUpdate(void)
{
    digitalWrite(LED, LOW);
    WiFiClient client;

    ESPhttpUpdate.setLedPin(LED_BUILTIN, LOW);

    IPAddress host;
    WiFi.hostByName("rmote.app", host);
    String url = "http://" + host.toString() + "/firmware.bin";

    Serial.println("Downloading update from: " + url);

    t_httpUpdate_return ret = ESPhttpUpdate.update(client, url);
    switch (ret)
    {
    case HTTP_UPDATE_FAILED:
        Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s\n", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
        break;
    case HTTP_UPDATE_NO_UPDATES:
        Serial.println("HTTP_UPDATE_NO_UPDATES");
        break;
    case HTTP_UPDATE_OK:
        Serial.println("HTTP_UPDATE_OK");
        break;
    }
    ESP.restart();
}