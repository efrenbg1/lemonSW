#include "EzVault.h"

//// Getters ////
bool EzVault::getLocal()
{
    return values[0].equals("1");
}

bool EzVault::getStatic()
{
    if (values[1].equals("1"))
    {
        for (int i = 0; i < 4; i++)
        {
            if (!staticIP[i].fromString(read(6 + i)))
            {
                Serial.println("\nStatic IP not properly configured!!!\n");
                return false;
            }
        }
        Serial.println("\nStatic IP:\n");
        Serial.println("-IP: " + staticIP[0].toString());
        Serial.println("-Gateway: " + staticIP[1].toString());
        Serial.println("-Netmask: " + staticIP[2].toString());
        Serial.println("-DNS: " + staticIP[3].toString());
        Serial.println("");
        return true;
    }
    return false;
}
IPAddress EzVault::getIP(void)
{
    return staticIP[0];
}
IPAddress EzVault::getGateway(void)
{
    return staticIP[1];
}
IPAddress EzVault::getNetmask(void)
{
    return staticIP[2];
}
IPAddress EzVault::getDNS(void)
{
    return staticIP[3];
}


String EzVault::getSSID(void)
{
    return values[2];
}
String EzVault::getWiFipw(void)
{
    return values[3];
}
String EzVault::getUser(void)
{
    return values[4];
}
String EzVault::getPW(void)
{
    return values[5];
}