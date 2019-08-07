#include "headers.h"
#include "WiFiHelpers.h"

MqTLS mqtls(5000, fingerprint);
EzVault vault(eeprom_size);
PController pc(PowerSW, &mqtls, &vault);
WiFiUDP udp;
NTPClient timeClient(udp, "time.google.com",0,6000);

void setup() {
  pinMode(LED,OUTPUT);
  Serial.begin(9600);
  vault.init(true);
  //WiFi.setSleepMode(WIFI_MODEM_SLEEP);
  while(!wifi_boot(vault.getSSID(), vault.getWiFipw())){
    Serial.println("Failed to connect to wifi!");
    Recovery recovery(2, "1Q2w3e4r", &mqtls, &vault);
  }
  //timeClient.begin(); 
}

void loop() {
  delay(150);
  /*timeClient.update();
  Serial.println(timeClient.getFormattedTime());*/
  pc.loop();
}