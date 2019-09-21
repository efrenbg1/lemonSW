#include "Recovery.h"

void Recovery::root(void)
{
  timeout = millis();
  server->send_P(200, "text/html", index_html);
}

void Recovery::scan(void)
{
  timeout = millis();
  int n = WiFi.scanNetworks();
  if (n == 0)
  {
    server->send(204, "text/plain", "");
  }
  else
  {
    String list = "{";
    for (int i = 0; i < n; ++i)
    {
      if (list.indexOf("\"" + WiFi.SSID(i) + "\"") == -1)
      {
        list += "\"" + String(WiFi.SSID(i)) + "\": ";
        list += "\"" + String(WiFi.RSSI(i)) + "\", ";
      }
      yield();
    }
    list.remove(list.length() - 2, 2);
    list += "}";
    server->send(200, "application/json", list);
  }
}

void Recovery::test(void)
{
  timeout = millis();
  server->send(200, "text/plain", "");
  ssid = server->arg("ssid");
  wifi_pw = server->arg("pw");
  delay(1000);
  WiFi.disconnect();
  WiFi.begin((ssid).c_str(), (wifi_pw).c_str());
}

void Recovery::check_wifi(void)
{
  timeout = millis();
  delay(500);
  if (WiFi.SSID().length() == 0)
  {
    server->send(204, "text/plain", ".");
  }
  else
  {
    if (WiFi.status() != WL_CONNECTED)
    {
      server->send(200, "text/plain", ".");
    }
    else
    {
      server->send(200, "text/plain", WiFi.SSID());
    }
  }
}

void Recovery::mqtls_check(void)
{
  timeout = millis();
  user = server->arg("user");
  pw = server->arg("pw");
  server->send(200, "text/plain", String(mqtls->connect("rmote.app", 2443, user, pw)));
}

void Recovery::save(void)
{
  timeout = millis();
  String values[] = {server->arg("local"), server->arg("static"), ssid, wifi_pw, user, pw, server->arg("ip"), server->arg("gateway"), server->arg("netmask"), server->arg("dns")};
  if (vault->save(values))
  {
    server->send(200, "text/plain", "");
  }
  else
  {
    server->send(403, "text/plain", "");
  }
}

void Recovery::reboot(void)
{
  server->send_P(200, "text/html", reboot_html);
  delay(5000);
  Serial.println("Rebooting...");
  ESP.restart();
}

void Recovery::off_wifi(void)
{
  timeout = millis();
  WiFi.disconnect();
}