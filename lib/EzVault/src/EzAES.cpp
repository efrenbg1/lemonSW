#include "EzVault.h"

#define aes_iv {10,227,48,208,47,33,9,165,145,162,24,229,167,243,140,162}

//// Encryption ////

void EzVault::aes_init_dec(String data) {
  yield();
  byte iv[N_BLOCK] = aes_iv;
  aesLib.gen_iv(iv);
  decrypt(strdup(data.c_str()));
}

void EzVault::aes_init_enc(String data) {
  yield();
  byte iv[N_BLOCK] = aes_iv;
  aesLib.gen_iv(iv);
  encrypt(strdup(data.c_str()));
}

String EzVault::encrypt(char * msg) { 
  yield(); 
  byte iv[N_BLOCK] = aes_iv;
  int msgLen = strlen(msg);
  char encrypted[4 * msgLen];
  aesLib.encrypt64(msg, encrypted, aes_key, iv);
  return String(encrypted);
}

String EzVault::decrypt(char * msg) {
  yield();
  byte iv[N_BLOCK] = aes_iv;
  int msgLen = strlen(msg);
  char decrypted[msgLen];
  aesLib.decrypt64(msg, decrypted, aes_key, iv);
  return String(decrypted);
}