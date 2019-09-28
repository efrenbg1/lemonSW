#ifndef PController_H
#define PController_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <MqTLS.h>
#include <EzVault.h>
#include <Recovery.h>
#include <GitUpdate.h>

class PController {
        bool action_off = false, action_on = false, action_force = false;
        unsigned int GPIO;
        unsigned int sample = 0;
        unsigned int timeout = 0;
        int samples[14] = {0};
        char stat = '0';
        char action = '6';
        String topic = WiFi.macAddress();
        String address = "";
        int failed = 0;
        MqTLS* mqtls;
        ESP8266WebServer http;
        EzVault* vault;
    public:
        PController(unsigned int, String, MqTLS*, EzVault*);
        void on(void);
        void off(void);
        void force(void);
        void loop(void);
        char getStatus(void);
        void indexHTTP(void);
        void actionHTTP(void);
        void statusHTTP(void);
        void initHTTP(void);
    private:
        void callback(String);
};

#endif