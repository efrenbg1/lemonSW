#include "PController.h"

char PController::getStatus(void)
{
    return stat;
}

void PController::loop(void)
{
    if (sample < 15)
    {
        samples[sample] = analogRead(A0);
        sample++;
        if (vault->getLocal())
        {
            http.handleClient();
        }
        else
        {
            int status = mqtls->callback(&slot, &msg);
            if (status == 7)
            {
                return;
            }
            else if (status == -1)
            {
                if (WiFi.status() != WL_CONNECTED)
                    return; //Let the main loop handle the reconnect
                Serial.print("Connecting to server...");
                digitalWrite(2, LOW);
                int result = mqtls->connect(address, 2443, vault->getUser(), vault->getPW());
                if (result == 0)
                {
                    mqtls->lastwill(topic, "0", "9");
                    mqtls->watch(topic);
                    mqtls->publish(topic, "1", "6");
                    mqtls->publish(topic, "2", "5"); //version running
                    Serial.println("Done");
                    failed = 0;
                }
                else if (result == 9)
                {
                    stopHTTP();
                    Recovery recovery(5, mqtls, vault);
                    ESP.restart();
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
                        ESP.restart();
                    }
                }
                digitalWrite(2, HIGH);
            }
            else if (status != 5)
            {
                Serial.print("Failed to retrive data: ");
                Serial.println(status);
                return;
            }
            if (slot == "1")
                callback(msg);
        }
    }
    else
    {
        sample = 0;
        int last = samples[0];
        int changes = 0;
        int high = 0;
        //String debug = "";
        for (int i = 0; i < 15; i++)
        {
            //debug = debug + "/" + (String)samples[i];
            if (samples[i] > 500)
            { //high
                high++;
                if ((samples[i] - last) > 200) //going higher (correcting for capacitance)
                {
                    changes++;
                }
                last = samples[i];
            }
            else
            {                                  //low
                if ((last - samples[i]) > 200) //going lower (correcting for capacitance)
                {
                    changes++;
                }
                last = samples[i];
            }
        }
        //status checker
        if (changes == 0)
        {
            if (high == 15)
            {
                stat = '1';
            }
            else if (high == 0)
            {
                stat = '0';
            }
        }
        else if (changes < 2)
        {
            if (last == 1)
            {
                stat = '1';
            }
            else
            {
                stat = '0';
            }
        }
        else
        {
            stat = '2';
        }

        char oldAction = action;

        //actions cheker
        if (action_force == true)
        {
            action_force = false;
            (stat == '0') ? action = '6' : action = '5';
        }

        if (action_off == true)
        {
            timeout++;
            if (stat == '0' || stat == '2')
            {
                action_off = false;
                action = '6';
            }
            else if (timeout > 20)
            {
                action_off = false;
                action = '5';
            }
        }

        if (action_on == true)
        {
            timeout++;
            if (stat == '1')
            {
                action_on = false;
                action = '6';
            }
            else if (timeout > 2)
            {
                action_on = false;
                action = '5';
            }
        }

        if (!vault->getLocal() && WiFi.status() == WL_CONNECTED)
        {
            mqtls->publish(topic, "0", String(stat));
            if (oldAction != action)
            {
                mqtls->publish(topic, "1", String(action));
            }
            //For debugging purposes only
            //debug = debug + "|" + changes + "|" + on;
            //Serial.println(debug);
            //mqtls->publish(topic, "2", debug);
        }

        if (vault->getAO() && WiFi.status() == WL_CONNECTED)
        {
            if (getStatus() == '0' || getStatus() == '2')
                on();
        }
    }
}
