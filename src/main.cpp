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
#define jumper 16

#define fingerprint "42 DC 8A 31 86 ED B5 31 D1 CF 87 21 96 CD 8A E7 A7 32 99 FE"
#define server_ip "rmote.app"
#define server_port 2443

MqTLS mqtls(fingerprint);
EzVault vault;
PController pc(PowerSW, server_ip, &mqtls, &vault);


const char *wl_status_to_string(wl_status_t status)
{
  switch (status)
  {
  case WL_NO_SHIELD:
    return "WL_NO_SHIELD";
  case WL_IDLE_STATUS:
    return "WL_IDLE_STATUS";
  case WL_NO_SSID_AVAIL:
    return "WL_NO_SSID_AVAIL";
  case WL_SCAN_COMPLETED:
    return "WL_SCAN_COMPLETED";
  case WL_CONNECTED:
    return "WL_CONNECTED";
  case WL_CONNECT_FAILED:
    return "WL_CONNECT_FAILED";
  case WL_CONNECTION_LOST:
    return "WL_CONNECTION_LOST";
  case WL_DISCONNECTED:
    return "WL_DISCONNECTED";
  }
}
bool wifi_boot()
{
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
  return true;
}

//WiFiUDP udp;
//NTPClient timeClient(udp, "time.google.com",0,6000);

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(0, INPUT);
  Serial.begin(9600);
  vault.init(false);
  // JUMPER recovery
  pinMode(jumper, INPUT_PULLDOWN_16);
  if(digitalRead(jumper) == 1){
    Recovery recovery(15, &mqtls, &vault);
  }
  pinMode(jumper, OUTPUT);

  //Recovery recovery(15, &mqtls, &vault);

  while (!wifi_boot())
  {
    Serial.println("Failed to connect to wifi!");
    WiFi.disconnect();
  }
  pc.initHTTP();
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
    Serial.println(wl_status_to_string(WiFi.status()));
    wifi_boot();
  }
}