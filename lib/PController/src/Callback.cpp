#include <PController.h>

void PController::callback(String msg)
{
    if (msg.equals("") && !vault->getLocal())
    {
        int status = mqtls->retrieve(topic, "1", &msg);
        if (status == -1)
        {
            if(WiFi.status() != WL_CONNECTED) return; //Let the main loop handle the reconnect
            Serial.print("Connecting to server...");
            digitalWrite(2, LOW);
            if (mqtls->connect(address, 2443, vault->getUser(), vault->getPW()) == 0)
            {
                mqtls->lastwill(topic, "0", "9");
                mqtls->publish(topic, "1", "6");
                mqtls->publish(topic, "2", "3"); //version running
                Serial.println("Done");
                failed = 0;
            }
            else
            {
                failed++;
                Serial.println("Failed");
                if (failed > 15)
                {
                    failed = 0;
                    stopHTTP();
                    Recovery recovery(2, mqtls, vault);
                }
            }
            digitalWrite(2, HIGH);
        }
        else if (status != 2 && status != 7)
        {
            Serial.print("Failed to retrive data: ");
            Serial.println();
            return;
        }
    }
    Serial.print("Response: ");
    Serial.println(msg);
    if (msg.equals("0"))
    {
        action = '4';
        if(!vault->getLocal()) mqtls->publish(topic, "1", String(action));
        switch (getStatus())
        {
        case '0':
            on();
            break;
        case '1':
            off();
            break;
        case '2':
            on();
            break;
        }
    }
    else if (msg.equals("1"))
    {
        action = '4';
        if(!vault->getLocal()) mqtls->publish(topic,"1", String(action));
        force();
    }
    else if (msg.equals("8"))
    {
        if (vault->getLocal())
        {
            stopHTTP();
        }
        else
        {
            mqtls->lastwill(topic, "0", "7");
            mqtls->publish(topic, "1", "6");
        }
        GitUpdate update;
    }
    else if (msg.equals("9"))
    {
        if (vault->getLocal())
        {
            stopHTTP();
        }
        else
        {
            mqtls->publish(topic, "0", "8");
            mqtls->publish(topic, "1", "6");
            mqtls->lastwill(topic, "0", "8");
        }
        delay(5000);
        Recovery recovery(5, mqtls, vault);
    }
}