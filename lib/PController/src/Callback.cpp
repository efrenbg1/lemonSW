#include <PController.h>

void PController::callback(void) {
  String msg;
  int resp = mqtls->retrieve(action, &msg);
  if(resp == -1){
    Serial.print("Connecting to server...");
    if(mqtls->connect("rmote.app", 2443, vault->getUser(), vault->getPW(), "95") == 0){
        //PUT LAST-WILL
        Serial.println("Done");
    } else {
        Serial.println("Failed");
    }
  } else if(resp != 2 && resp != 7){
    Serial.print("Failed to retrive data: ");
    Serial.println(resp);
  } else {
    Serial.print("Response: ");
    Serial.println(msg);
  if(msg.equals("0")){
    Serial.print("Publish: ");
    Serial.println(mqtls->publish(action, "4"));
    char stat = getStatus();
    switch(stat){
      case '0':
          on();
          break;
      case '1':
          off();
          break;
      case '2': 
          on();
          break;
      default:
          mqtls->publish(action, "5");
    }
  } else if(msg.equals("1")){
    force();
  } else if(msg.equals("2")){
    force();
    delay(5000);
    loop();
    on();
  } else if(msg.equals("9")){
    mqtls->publish(WiFi.macAddress(), "8");
    mqtls->publish(action, "6");
    delay(500);
    mqtls->disconnect();
    delay(5000);
    Recovery recovery(2, vault->getPW(), mqtls, vault);
  }
  }
}