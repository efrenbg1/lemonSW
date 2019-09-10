#ifndef PController_H
#define PController_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <MqTLS.h>
#include <EzVault.h>
#include <Recovery.h>

class PController {
        bool action_off = false, action_on = false, action_force = false;
        unsigned int GPIO;
        unsigned int sample = 0;
        unsigned int timeout = 0;
        int samples[10];
        char stat = '0';
        String topic = WiFi.macAddress();
        String address = "";
        int failed = 0;
        MqTLS* mqtls;
        EzVault* vault;
    public:
        PController(unsigned int, String, MqTLS*, EzVault*);
        void on(void);
        void off(void);
        void force(void);
        void loop(void);
        char getStatus(void);
    private:
        void callback(void);
};

#endif