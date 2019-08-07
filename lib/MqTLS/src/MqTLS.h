#ifndef MQTLS_H
#define MQTLS_H

#include <Arduino.h>
#include <WiFiClientSecure.h>

class MqTLS {
        WiFiClientSecure client;
    public:
        MqTLS(unsigned int, String);
        int publish(String, String);
        int connect(String, int, String, String, String);
        int lastwill(String, String);
        int retrieve(String, String*);
        void disconnect(void);
    private:
        String getlength(String &);
};

#endif