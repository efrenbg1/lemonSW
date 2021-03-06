#ifndef MQTLS_H
#define MQTLS_H

#include <Arduino.h>
#include <WiFiClientSecure.h>

class MqTLS
{
    WiFiClientSecure client;
    String secBuff;

public:
    MqTLS(String);
    int publish(String, String, String);
    int connect(String, int, String, String, bool);
    int lastwill(String, String, String);
    int watch(String);
    int retrieve(String, String, String *);
    int callback(String *, String *);

private:
    String enc(String &);
};

#endif