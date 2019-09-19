#include "PController.h"

void PController::initHTTP(void)
{
    http.on("/status", std::bind(&PController::statusHTTP, this));
    http.on("/action", std::bind(&PController::actionHTTP, this));
    http.onNotFound(std::bind(&PController::indexHTTP, this));
    http.begin();
}


void PController::indexHTTP(void)
{
    http.send_P(200, "text/html", "hey");
}

void PController::actionHTTP(void)
{
    String payload = http.arg("payload");
    callback(payload);
    http.send(200, "text/plain", "");
}

void PController::statusHTTP(void)
{
    char response[32];
    Serial.println(sprintf(response, "{'status': '%c', 'action': '%c'}", '0', '1'));
    http.send(200, "application/json", response);
}