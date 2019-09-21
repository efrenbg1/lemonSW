#include "PController.h"

PController::PController(unsigned int _GPIO, String _server, MqTLS* _mqtls, EzVault* _vault){
    GPIO = _GPIO;
    mqtls = _mqtls;
    vault = _vault;
    address = _server;
    //initHTTP();
}

void PController::on(void){
    pinMode(GPIO,OUTPUT);
    digitalWrite(GPIO,HIGH);
    delay(500);
    digitalWrite(GPIO,LOW);
    pinMode(GPIO,INPUT);
    action_off = false;
    action_on = true;
    action_force = false;
    sample = 0;
    timeout = 0;
}

void PController::off(void){
    mqtls->publish(topic,"1", "4");
    pinMode(GPIO,OUTPUT);
    digitalWrite(GPIO,HIGH);
    delay(500);
    digitalWrite(GPIO,LOW);
    pinMode(GPIO,INPUT);
    action_off = true;
    action_force = false;
    action_on = false;
    sample = 0;
    timeout = 0;
}

void PController::force(void){
    mqtls->publish(topic,"1", "4");
    pinMode(GPIO,OUTPUT);
    digitalWrite(GPIO,HIGH);
    delay(4000);
    digitalWrite(GPIO,LOW);
    pinMode(GPIO,INPUT);
    action_force = true;
    action_on = false;
    action_off = false;
    sample = 0;
}