#ifndef Recovery_H
#define Recovery_H

#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPUpdateServer.h>
#include <MqTLS.h>
#include <EzVault.h>
#include "HTML.h"

class Recovery {
        unsigned int timeout = 0;
        ESP8266WebServer* server;
        ESP8266HTTPUpdateServer* httpUpdater;
        MqTLS* mqtls;
        EzVault* vault;
        String ssid;
        String wifi_pw;
        String user;
        String pw;
    public:
        Recovery(unsigned int, MqTLS*, EzVault*);
    protected:
        void root(void);
        void scan(void);
        void test(void);
        void check_wifi(void);
        void mqtls_check(void);
        void save(void);
        void reboot(void);
        void off_wifi(void);
    private:
        String scan_wifi(void);
};

#endif