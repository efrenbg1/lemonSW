#ifndef MQTLS_H
#define MQTLS_H

#include <Arduino.h>
#include <WiFiClientSecure.h>

class MqTLS {
        WiFiClientSecure client;
    public:
        MqTLS(String);
        int publish(String, String, String);
        int connect(String, int, String, String);
        int lastwill(String, String, String);
        int retrieve(String, String, String*);
        void disconnect(void);
    private:
        String getlength(String &);
};

#endif