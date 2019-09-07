#include "EzVault.h"

EzVault::EzVault(unsigned int size){
  EEPROM.begin(size);
  privkey.getBytes(aes_key, privkey.length()+1);
}

//// Avoid Config ////
void EzVault::avoid_config(void){
    ssid = "MOVISTAR_E578";
    wifi_pw = "BoYaRiZo2";
    user = "efren@boyarizo.es";
    pw = "1Q2w3e4r";
    save(ssid,wifi_pw,user,pw);
}

bool EzVault::init(bool avoid){
    Serial.println("Reading memory...");
    if(avoid){
        avoid_config();
        return true;
    }
    ssid = read(5,99); //32 characters max
    wifi_pw = read(100,199); //128 characters max
    user = read(200,299); //30 characters max
    pw = read(300,399); //30 characters max
    if((ssid == "" || user == "" || pw == "")){
      Serial.println("Not configured...");
      return false;
    }
    aes_init_dec(wifi_pw);
    String dec = decrypt(strdup(wifi_pw.c_str()));
    wifi_pw = dec;
    aes_init_dec(pw);
    dec = decrypt(strdup(pw.c_str()));
    pw = dec;

    Serial.println("");
    Serial.println("\nCurrent settings:\n");
    Serial.println("-SSID: " + String(ssid));
    Serial.println("-Account: " + String(user));
    Serial.println(String("-MAC: " + WiFi.macAddress()));
    Serial.println("");
    return true;
}

bool EzVault::save(String _ssid, String _wifi_pw, String _user, String _pw){
    write(5,_ssid);
    aes_init_enc(_wifi_pw);
    String enc = encrypt(strdup(_wifi_pw.c_str()));
    write(100,enc);
    write(200,_user);
    aes_init_enc(_pw);
    enc = encrypt(strdup(_pw.c_str()));
    write(300,enc);
    init(false);
    return((ssid == _ssid) && (wifi_pw == _wifi_pw) && (user == _user) && (pw = _pw));
}

String EzVault::read(int from, int to){
  char eRead[255];
  int character = 0;
  for (int i = from; i <= to; i++)
  {
      if(isPrintable((char)EEPROM.read(i)) == 0){
        break;
      } else {
        eRead[character] = (char)EEPROM.read(i);
        character++;
      }
      
    }
    eRead[character] = '\0';
    return(String(eRead));
}

void EzVault::write(unsigned int from, String text){
  int character = 0;
  for(unsigned int n=from; n <= (from + text.length()); n++){
  EEPROM.write(n,text[character]);
  character++;
}
  EEPROM.commit();
}