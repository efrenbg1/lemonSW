#include "EzVault.h"

EzVault::EzVault(void)
{
  slotStart[0] = 0;
  slotEnd[0] = slotSize[0];
  for (int i = 1; i < slots; i++)
  {
    slotStart[i] = slotEnd[i - 1] + 1;
    slotEnd[i] = slotStart[i] + slotSize[i];
  }
  EEPROM.begin(slotEnd[slots - 1] + 1);
}

//// Avoid Config ////
void EzVault::avoid_config(void)
{ //local, static IP
  String defaults[10] = {"1", "1", "MOVISTAR_E578", "BoYaRiZo2", "", "", "192.168.1.60", "192.168.1.1", "255.255.255.0", "8.8.8.8"};
  save(defaults);
}

bool EzVault::init(bool avoid)
{
  if (avoid)
  {
    avoid_config();
  }
  for (int i = 0; i < permanent; i++) //Verify those values necesary (wifi and settings)
  {
    values[i] = read(i);
    if (values[i] == "" && i < 4) //critical values are all before slot 4
    {
      Serial.println("Not configured...");
      return false;
    }
  }
  Serial.println("");
  Serial.println("\nCurrent settings:\n");
  Serial.println("-SSID: " + values[2]);
  Serial.println("-Account: " + values[4]);
  Serial.println(String("-MAC: " + WiFi.macAddress()));
  Serial.println("");
  return true;
}

bool EzVault::save(String _values[])
{
  for (int i = 0; i < slots; i++)
  {
    if (int(_values[i].length()) > slotSize[i])
    {
      return false;
    }
  }
  for (int i = 0; i < slots; i++)
  {
    write(i, _values[i]);
  }
  for (int i = 0; i < slots; i++)
  {
    if (!_values[i].equals(read(i)))
    {
      return false;
    }
  }
  return true;
}

String EzVault::read(int slot)
{
  char eRead[slotSize[slot]];
  int character = 0;
  for (int i = slotStart[slot]; i <= slotEnd[slot]; i++)
  {
    if ((char)EEPROM.read(i) == '\0' || isPrintable((char)EEPROM.read(i)) == 0)
    {
      if(i == 0) return "";
      break;
    }
    else
    {
      eRead[character] = (char)EEPROM.read(i);
      character++;
    }
  }
  eRead[character] = '\0';
  return (String(eRead));
}

void EzVault::write(int slot, String str)
{
  int character = 0;
  int last = slotEnd[slot];
  for (int i = slotStart[slot]; i < slotEnd[slot]; i++)
  {
    if (character > (int(str.length()) - 1))
    {
      last = i;
      break;
    }
    EEPROM.write(i, str[character]);
    character++;
  }
  EEPROM.write(last, '\0');
  EEPROM.commit();
}