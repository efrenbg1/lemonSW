#ifndef EzVault_H
#define EzVault_H

#include <EEPROM.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>

#define slots 10
#define permanent 6

class EzVault {
    int slotStart[slots];
    int slotEnd[slots];
    int slotSize[slots] = {1, 1, 32, 128, 30, 30, 15, 15, 15, 15};
    String values[permanent];
    IPAddress staticIP[4];
    public:
        EzVault(void);
        bool init(bool);
        bool save(String[]);
        String getSSID(void);
        String getWiFipw(void);
        String getUser(void);
        String getPW(void);
        bool getLocal(void);
        bool getStatic(void);
        IPAddress getIP(void);
        IPAddress getGateway(void);
        IPAddress getNetmask(void);
        IPAddress getDNS(void);
    private:
        String read(int);
        void avoid_config(void);
        void write(int, String);
};

#endif

