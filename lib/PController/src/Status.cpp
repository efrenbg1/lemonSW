#include "PController.h"

char PController::getStatus(void)
{
    return stat;
}

void PController::loop(void)
{
    if (sample < 10)
    {
        samples[sample] = analogRead(A0);
        sample++;
    }
    else
    {
        sample = 0;
        callback();
        int last = 2;
        int changes = 0;
        int on = 0;
        String debug = "";
        for (int i = 0; i < 10; i++)
        {
            debug = debug + "/" + (String)samples[i];
            if (samples[i] > 300)
            { //high
                on++;
                if (last == 0)
                {
                    changes++;
                }
                last = 1;
            }
            else
            { //low
                if (last == 1)
                {
                    changes++;
                }
                last = 0;
            }
        }
        //status checker
        if (changes == 0)
        {
            if (on == 10)
            {
                stat = '1';
            }
            else if (on == 0)
            {
                stat = '0';
            }
        }
        else if (changes < 2)
        {
            if (on > 7)
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

        

        mqtls->publish(topic, "0", String(stat));

        //For debugging purposes only
        debug = debug + "|" + changes + "|" + on;
        Serial.println(debug);
        mqtls->publish(topic, "2", debug);


        //actions cheker
        if (action_force == true)
        {
            action_force = false;
            if (stat == '0')
            {
                mqtls->publish(topic, "1", "6");
            }
            else
            {
                mqtls->publish(topic, "1", "5");
            }
        }

        if (action_off == true)
        {
            timeout++;
            if (timeout > 10)
            {
                action_off = false;
                switch (stat)
                {
                case '2':
                    mqtls->publish(topic, "1", "6");
                    break;
                case '1':
                    mqtls->publish(topic, "1", "5");
                    break;
                case '0':
                    mqtls->publish(topic, "1", "6");
                    break;
                }
            }
        }

        if (action_on == true)
        {
            action_on = false;
            switch (stat)
            {
            case '2':
                mqtls->publish(topic, "1", "5");
                break;
            case '1':
                mqtls->publish(topic, "1", "6");
                break;
            case '0':
                mqtls->publish(topic, "1", "5");
                break;
            }
        }
    }
}


