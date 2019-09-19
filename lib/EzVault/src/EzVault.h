#ifndef EzVault_H
#define EzVault_H

#include <EEPROM.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>

class EzVault {
    String ssid, wifi_pw, user, pw;
    public:
        EzVault(unsigned int);
        bool init(bool);
        bool save(String, String, String, String);
        String getSSID(void);
        String getWiFipw(void);
        String getUser(void);
        String getPW(void);
    private:
        String read(int, int);
        void avoid_config(void);
        void write(unsigned int, String);
};

#endif

