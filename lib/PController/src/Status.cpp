#include "PController.h"

char PController::getStatus(void){
    return stat;
}

void PController::loop(void){
    if(sample < 14){
        if(analogRead(A0) > 200){
            check++;
            if(last == 0){
                changes++;
            }
            last = 1;
        } else {
            if(last == 1){
                changes++;
            }
            last = 0;
        }
        sample++;
    } else {
        callback();
        sample = 0;
        if(changes == 0){
            if(check == 14){
                stat = '1';
            } else if(check == 0){
                stat = '0';
            } else if(check > 0 && check < 14){
                stat = '2';
            }
        } else if(changes == 1){
            if(analogRead(A0) > 200){
                if(last == 0){
                    changes++;
                }
                last = 1;
            } else {
                if(last == 1){
                    changes++;
                }
                last = 0;
            }
            if(changes == 1){
                if(last == 1){
                    stat = '1';
                } else {
                    stat = '0';
                }
            } else {
                stat = '2'; 
            }
        } else {
            stat = '2';
        }
        if(action_force == true && (millis()-timeout)>5000){
            timeout = 0;
            action_force = false;
            digitalWrite(GPIO,LOW);
            pinMode(4,INPUT);
            delay(100);
            action_off = true;
            action_on = false;
            timeout = 15;
        }
        if(action_off == true){
            timeout++;
            if(stat == '2'){
                action_off = false;
                timeout=0;
                mqtls->publish(action, "6");
            } else if (stat == '0'){
                action_off = false;
                timeout=0;
                mqtls->publish(action, "6");
            } else if (stat == '1'){
                if(timeout > 15){
                    action_off = false;
                    mqtls->publish(action, "5");
                }
            }
        }
        if(action_on == true){
            action_on = false;
            if(stat == '2'){
                mqtls->publish(action, "5");
            } else if (stat == '0'){
                mqtls->publish(action, "5");
            } else if (stat == '1'){
                mqtls->publish(action, "6");
            }
        }
        mqtls->publish(status, String(stat));
        check = 0;
        changes = 0;
        last = 2;
    }
}