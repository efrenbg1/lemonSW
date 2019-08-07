#include "PController.h"

PController::PController(unsigned int _GPIO, MqTLS* _mqtls, EzVault* _vault){
    GPIO = _GPIO;
    mqtls = _mqtls;
    vault = _vault;
}

void PController::on(void){
    pinMode(GPIO,OUTPUT);
    digitalWrite(GPIO,HIGH);
    delay(100);
    digitalWrite(GPIO,LOW);
    pinMode(GPIO,INPUT);
    delay(100);
    action_off = false;
    action_on = true;
    action_force = false;
    sample = 0;
    check = 0;
}

void PController::off(void){
    mqtls->publish(action, "4");
    pinMode(GPIO,OUTPUT);
    digitalWrite(GPIO,HIGH);
    delay(100);
    digitalWrite(GPIO,LOW);
    pinMode(GPIO,INPUT);
    delay(100);
    action_off = true;
    action_force = false;
    action_on = false;
    sample = 0;
    check = 0;
}

void PController::force(void){
    mqtls->publish(action, "4");
    pinMode(GPIO,OUTPUT);
    digitalWrite(GPIO,HIGH);
    action_force = true;
    action_on = false;
    action_off = false;
    timeout = millis();
    sample = 0;
    check = 0;
}