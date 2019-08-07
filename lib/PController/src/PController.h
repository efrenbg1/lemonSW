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
        unsigned int last = 2;
        unsigned int check = 0;
        unsigned int changes = 0;
        char stat = '0';
        String status = WiFi.macAddress();
        String action = "_" + status;
        String settings = "!" + status;
        MqTLS* mqtls;
        EzVault* vault;
    public:
        PController(unsigned int, MqTLS*, EzVault*);
        void on(void);
        void off(void);
        void force(void);
        void loop(void);
        char getStatus(void);
    private:
        void callback(void);
};

#endif