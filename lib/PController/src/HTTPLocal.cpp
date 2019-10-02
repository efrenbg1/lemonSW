#include "PController.h"

const char status_html[] PROGMEM = "<!DOCTYPE html>\r\n"
"<html lang=en>\r\n"
"<meta name=viewport content=\"width=device-width, initial-scale=1\">\r\n"
"<head>\r\n"
"<title>lemonSW minDashboard</title>\r\n"
"<style>h1{text-shadow:2px 1.5px red;font-family:\"Georgia\",Times,serif;padding-bottom:25px;margin-top:.2rem;text-align:center}h2{font-family:\"Georgia\",Times,serif;margin:5%;text-align:center}body{background-color:#2b3e4c;color:#fff;padding-left:0;padding-top:100px}.b1{margin-left:auto;padding:8px 16px;border:0;background:red;color:#f2f2f2;text-transform:uppercase;letter-spacing:.09em;border-radius:2px}.b2{margin-left:auto;padding:8px 16px;border:0;background:#00bcd4;color:#f2f2f2;text-transform:uppercase;letter-spacing:.09em;border-radius:2px}.sub{font-size:5px;text-align:center}</style>\r\n"
"</head>\r\n"
"<body>\r\n"
"<center clas=sub>\r\n"
"PC is:\r\n"
"<h1 id=status style=margin-bottom:4rem>Loading...</h1>\r\n"
"<h2 id=action style=margin-bottom:4rem>Loading...</h2>\r\n"
"</center>\r\n"
"<div style=float:center;text-align:center;margin-bottom:4rem>\r\n"
"<button class=b1 type=button onclick=power()>POWER</button>\r\n"
"</div>\r\n"
"<div style=float:center;text-align:center>\r\n"
"<button class=b2 type=button onclick=force()>Force off</button>\r\n"
"<button class=b2 type=button onclick=recovery()>Recovery</button>\r\n"
"<button class=b2 type=button onclick=update()>Update</button>\r\n"
"</div>\r\n"
"</body>\r\n"
"<script>var actionHTML=document.getElementById(\"action\");var statusHTML=document.getElementById(\"status\");function power(){actionHTML.innerText=\"Waiting for response...\";req('/action?payload=0',function(status,response){if(status!==200){actionHTML.innerText=\"Failed to communicate!\"}else{actionHTML.innerText=\"Turning on/off...\"}});}\r\n"
"function force(){if(confirm(\"Are your sure? This will cut power to the PC losing any unsaved files\")){actionHTML.innerText=\"Waiting for response...\";req('/action?payload=1',function(status,response){if(status!==200){actionHTML.innerText=\"Failed to communicate!\"}});}}\r\n"
"window.setInterval(refresh,1000);function refresh(){req('/status',function(status,response){if(status===200){var stats={'0':'OFF','1':'ON','2':'SUSPENDED'};var actions={'0':'Working on it...','1':'Turning on/off...','4':'Turning on/off...','5':'Command failed!','6':'Waiting for command'};statusHTML.innerHTML=stats[response['status']];actionHTML.innerHTML=actions[response['action']];}});}\r\n"
"function update(){if(confirm(\"Are your sure? The board needs an active Internet connection and uninterrupted power\")){actionHTML.innerText=\"Waiting for response...\";req('/action?payload=8',function(status,response){if(status!==200){actionHTML.innerText=\"Failed to communicate!\"}else{actionHTML.innerText=\"Board is updating\";}});}}\r\n"
"function recovery(){if(confirm(\"Are your sure? Recovery creates a HotSpot to change the settings\")){actionHTML.innerText=\"Waiting for response...\";req('/action?payload=9',function(status,response){if(status!==200){actionHTML.innerText=\"Failed to communicate!\"}else{actionHTML.innerText=\"Board is in recovery\";}});}}\r\n"
"function show(object){object.style.display='inline';object.style.visibility='visible';}\r\n"
"function hide(object){object.style.display='none';}\r\n"
"var ip=\"\";function req(url,callback){let r=new XMLHttpRequest();r.open('GET',ip+url,true);r.responseType='json';r.onreadystatechange=function(){if(r.readyState==4){callback(r.status,r.response);}}.bind(this);r.send();}</script>\r\n"
"</html>\r\n";

void PController::initHTTP(void)
{
    http.on("/status", std::bind(&PController::statusHTTP, this));
    http.on("/action", std::bind(&PController::actionHTTP, this));
    http.onNotFound(std::bind(&PController::indexHTTP, this));
    http.begin();
}


void PController::indexHTTP(void)
{
    http.send_P(200, "text/html", status_html);
}

void PController::actionHTTP(void)
{
    String payload = http.arg("payload");
    http.send(200, "text/plain", "");
    callback(payload);
}

void PController::statusHTTP(void)
{
    char response[32];
    sprintf(response, "{\"status\": \"%c\", \"action\": \"%c\"}", stat, action);
    http.send(200, "application/json", response);
}