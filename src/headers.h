#include <ESP8266WiFi.h>
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

#define fingerprint "42 DC 8A 31 86 ED B5 31 D1 CF 87 21 96 CD 8A E7 A7 32 99 FE"
#define server_ip "rmote.app"
#define server_port 2443

#define eeprom_size 1024

