#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include <Arduino.h>
#include <EzVault.h>
#include <MqTLS.h>
#include <PController.h>
#include <Recovery.h>

#define LED 2
#define PowerSW 4
#define PC_LED 0
#define jumper 16

#define fingerprint "42 DC 8A 31 86 ED B5 31 D1 CF 87 21 96 CD 8A E7 A7 32 99 FE"

#define server_ip "rmote.app"
#define server_port 2443

#define avoid_settings false

#define AO_affinity 5

int tries = 0;

MqTLS mqtls(fingerprint);
EzVault vault;
PController pc(PowerSW, server_ip, &mqtls, &vault);

bool wifi_boot()
{
    if (vault.getLocal())
        pc.stopHTTP();
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
            if (vault.getAO())
            {
                int n = WiFi.scanNetworks();
                bool found = false;
                for (int i = 0; i < n; ++i)
                {
                    if (WiFi.SSID(i) == vault.getSSID())
                        found = true;
                }
                if (!found)
                {
                    tries++;
                    Serial.print("WiFi not found: ");
                    Serial.println(tries);
                    if (pc.getStatus() == '1' && tries > AO_affinity)
                        pc.off();
                }
            }
            return false;
        }
        delay(250);
        digitalWrite(LED, HIGH);
        Serial.print(".");
        pc.loop();
        delay(250);
        digitalWrite(LED, LOW);
        pc.loop();
    }
    digitalWrite(LED, HIGH);
    Serial.println("Connected.");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    if (vault.getLocal())
        pc.initHTTP();
    tries = 0;
    return true;
}

void setup()
{
    pinMode(LED, OUTPUT);
    pinMode(0, INPUT);
    Serial.begin(9600);
    WiFi.mode(WIFI_STA);

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
}

void loop()
{
    delay(150);
    pc.loop();
    while (WiFi.status() != WL_CONNECTED)
    {
        wifi_boot();
    }
}