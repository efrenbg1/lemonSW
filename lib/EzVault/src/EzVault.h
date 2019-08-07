#ifndef EzVault_H
#define EzVault_H

#include <EEPROM.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <AESLib.h>

class EzVault {
    AESLib aesLib;
    String ssid, wifi_pw, user, pw;
    byte aes_key[16];
    String privkey = "privkey";
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
        void aes_init_dec(String);
        void aes_init_enc(String);
        String encrypt(char *);
        String decrypt(char *);
        void avoid_config(void);
        void write(unsigned int, String);
};

#endif

