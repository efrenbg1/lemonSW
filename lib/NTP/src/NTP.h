#ifndef NTP_H
#define NTP_H

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

#define NTP_PACKET_SIZE 48

class NTP {
        WiFiUDP udp;
        NTPClient timeClient(udp, "time.google.com",-10800,6000);
    public:
        
        void loop(void);
    private:
        void sendNTPpacket(String);
};

#endif
