#include <PController.h>

void PController::callback(String msg)
{
    Serial.print("Command: ");
    Serial.println(msg);
    if (msg.equals("0"))
    {
        action = '4';
        if (!vault->getLocal())
            mqtls->publish(topic, "1", String(action));
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
        if (!vault->getLocal())
            mqtls->publish(topic, "1", String(action));
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