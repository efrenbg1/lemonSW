#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include <WiFiUdp.h>
#include <Arduino.h>
#include <EzVault.h>
#include <MqTLS.h>
#include <PController.h>
#include <Recovery.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

#define LED 2
#define PowerSW 4
#define PC_LED 0
#define jumper 16

#define fingerprint "42 DC 8A 31 86 ED B5 31 D1 CF 87 21 96 CD 8A E7 A7 32 99 FE"

#define server_ip "rmote.app"
#define server_port 2443

#define avoid_settings false

MqTLS mqtls(fingerprint);
EzVault vault;
PController pc(PowerSW, server_ip, &mqtls, &vault);

bool wifi_boot()
{
    if (vault.getLocal())
        pc.stopHTTP();
    WiFi.mode(WIFI_STA);
    WiFi.begin(vault.getSSID(), vault.getWiFipw());
    if (vault.getStatic())
    {
        WiFi.config(vault.getIP(), vault.getGateway(), vault.getNetmask(), vault.getDNS());
    }
    digitalWrite(LED, LOW);
    Serial.print("Connecting to wifi...");
    int timeout = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        timeout++;
        yield();
        if (timeout > 45)
        {
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
    if (vault.getLocal())
        pc.initHTTP();
    return true;
}
//WiFiUDP udp;
//NTPClient timeClient(udp, "time.google.com",0,6000);

void setup()
{
    pinMode(LED, OUTPUT);
    pinMode(0, INPUT);
    Serial.begin(9600);

    // JUMPER recovery
    pinMode(jumper, INPUT_PULLDOWN_16);
    if (digitalRead(jumper) == 1)
    {
        Recovery recovery(15, &mqtls, &vault);
    }
    pinMode(jumper, OUTPUT);

    if (!vault.init(avoid_settings))
        Recovery recovery(15, &mqtls, &vault);

    if (!wifi_boot())
    {
        Serial.println("Failed to connect to wifi!");
        WiFi.disconnect();
        Recovery recovery(2, &mqtls, &vault);
        ESP.restart();
    }

    //timeClient.begin();
}

void loop()
{
    delay(150);
    /*timeClient.update();
  Serial.println(timeClient.getFormattedTime());*/
    pc.loop();
    if (WiFi.status() != WL_CONNECTED)
    {
        int wait = 0;
        while (WiFi.status() != WL_CONNECTED)
        {
            wait++;
            yield();
            if (wait > 30)
            {
                ESP.restart();
            }
            delay(500);
        }
    }
}