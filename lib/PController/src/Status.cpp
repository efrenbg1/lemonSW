#include "PController.h"

char PController::getStatus(void)
{
    return stat;
}

void PController::loop(void)
{
    if (sample < 14)
    {
        samples[sample] = analogRead(A0);
        sample++;
        if(vault->getLocal()) http.handleClient();
    }
    else
    {
        sample = 0;
        if(!vault->getLocal()) callback("");
        int last = samples[0];
        int changes = 0;
        int on = 0;
        //String debug = "";
        for (int i = 0; i < 14; i++)
        {
            //debug = debug + "/" + (String)samples[i];
            if (samples[i] > 500)
            { //high
                on++;
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
            if (on == 14)
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

        if (!vault->getLocal())
        {
            mqtls->publish(topic, "0", String(stat));

            //For debugging purposes only
            //debug = debug + "|" + changes + "|" + on;
            //Serial.println(debug);
            //mqtls->publish(topic, "2", debug);

            if(oldAction != action){
                mqtls->publish(topic, "1", String(action));
            }
        }
    }
}
