#include <PController.h>

void PController::callback(void) {
  String msg;
  int resp = mqtls->retrieve(topic, "1", &msg);
  if(resp == -1){
    Serial.print("Connecting to server...");
    if(mqtls->connect(address, 2443, vault->getUser(), vault->getPW()) == 0){
        mqtls->lastwill(topic, "0", "9");
        Serial.println("Done");
        failed = 0;
    } else {
        failed++;
        Serial.println("Failed");
        if(failed > 15){
          failed = 0;
          mqtls->disconnect();
          Recovery recovery(2, "SuperPowers4All", mqtls, vault);
        }
    }
  } else if(resp != 2 && resp != 7){
    Serial.print("Failed to retrive data: ");
    Serial.println(resp);
  } else {
    Serial.print("Response: ");
    Serial.println(msg);
  if(msg.equals("0")){
    Serial.print("Publish: ");
    Serial.println(mqtls->publish(topic, "1", "4"));
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
          mqtls->publish(topic, "1", "5");
    }
  } else if(msg.equals("1")){
    force();
  } else if(msg.equals("2")){
    force();
    delay(5000);
    loop();
    on();
  } else if(msg.equals("9")){
    mqtls->publish(topic, "0", "8");
    mqtls->publish(topic, "1", "6");
    delay(500);
    mqtls->disconnect();
    delay(5000);
    Recovery recovery(2, vault->getPW(), mqtls, vault);
  }
  }
}