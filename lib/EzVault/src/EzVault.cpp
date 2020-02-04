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
  String defaults[11] = {"0", "0", "1", "ed", "", "ef", "", "192.168.43.200", "192.168.43.1", "255.255.255.0", "8.8.8.8"};
  save(defaults);
}

bool EzVault::init(bool avoid)
{
  if (avoid)
  {
    avoid_config();
  }

  if ((char)EEPROM.read(5) != '\0') //If db is in older version, update it to keep old config
  {
    Serial.println("Updating database to new version...");
    int oldSlotSize[slots] = {1, 1, 32, 128, 30, 30, 15, 15, 15, 15, 1};
    for (int i = 1; i < slots; i++)
    {
      slotSize[i] = oldSlotSize[i];
      slotStart[i] = slotEnd[i - 1] + 1;
      slotEnd[i] = slotStart[i] + slotSize[i];
    }
    String values[] = {read(0), read(1), "0", read(2), read(3), read(4), read(5), read(6), read(7), read(8), read(9), read(10)};
    int newSlotSize[slots] = {1, 1, 1, 32, 128, 30, 30, 15, 15, 15, 15};
    for (int i = 1; i < slots; i++)
    {
      slotSize[i] = newSlotSize[i];
      slotStart[i] = slotEnd[i - 1] + 1;
      slotEnd[i] = slotStart[i] + slotSize[i];
    }
    save(values);
    Serial.print("Done");
  }

  for (int i = 0; i < permanent; i++) //Verify those values necesary (wifi and settings)
  {
    values[i] = read(i);
    if (values[i] == "" && i < 5) //critical values are all before slot 5
    {
      Serial.println("Not configured...");
      return false;
    }
  }
  Serial.println("");
  Serial.println("\nCurrent settings:\n");
  Serial.println("-SSID: " + values[3]);
  Serial.println("-Account: " + values[5]);
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
      if (i == 0)
        return "";
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