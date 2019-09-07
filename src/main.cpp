#include "headers.h"
#include "WiFiHelpers.h"

MqTLS mqtls(fingerprint);
EzVault vault(eeprom_size);
PController pc(PowerSW, server_ip, &mqtls, &vault);
//WiFiUDP udp;
//NTPClient timeClient(udp, "time.google.com",0,6000);

void setup() {
  pinMode(LED,OUTPUT);
  pinMode(0, INPUT);
  Serial.begin(9600);
  vault.init(true);
  //WiFi.setSleepMode(WIFI_MODEM_SLEEP);
  while(!wifi_boot(vault.getSSID(), vault.getWiFipw())){
    Serial.println("Failed to connect to wifi!");
    Recovery recovery(2, "SuperPowers4All", &mqtls, &vault);
  }
  //timeClient.begin(); 
}

void loop() {
  delay(150);
  /*timeClient.update();
  Serial.println(timeClient.getFormattedTime());*/
  pc.loop();
  if (WiFi.status() != WL_CONNECTED){
    Serial.println(wl_status_to_string(WiFi.status()));
    mqtls.disconnect();
    wifi_boot(vault.getSSID(), vault.getWiFipw());
  }
}