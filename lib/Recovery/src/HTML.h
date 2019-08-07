#ifndef HTML_H
#define HTML_H

#include "Arduino.h"

const char index_html[] PROGMEM = "<!DOCTYPE html>\r\n"
"<html lang=en>\r\n"
"<meta name=viewport content=\"width=device-width, initial-scale=1\">\r\n"
"<head>\r\n"
"<title>lemonSW recovery</title>\r\n"
"<style>.footer{position:fixed;bottom:0;text-align:center;width:100%;display:block}h1{text-shadow:2px 1.5px red;font-family:\"Georgia\",Times,serif;margin:5%;text-align:center}body{font:normal 18px/1.5 \"Fira Sans\",\"Helvetica Neue\",sans-serif;background-color:#2b3e4c;color:#fff;padding-left:0;padding-top:100px}.container{width:80%;max-width:1200px;margin:0 auto}.container *{box-sizing:border-box}.flex-outer,.flex-inner{list-style-type:none;padding:0}.flex-outer{max-width:800px;margin:0 auto}.flex-outer li,.flex-inner{display:flex;flex-wrap:wrap;align-items:center}.flex-inner{padding:0 8px;justify-content:space-between}.flex-outer>li:not(:last-child){margin-bottom:20px}.flex-outer li label,.flex-outer li p{padding:8px;font-weight:300;letter-spacing:.09em;text-transform:uppercase}.flex-outer>li>label,.flex-outer li p{flex:1 0 120px;max-width:220px}.flex-outer>li>label+*,.flex-inner{flex:1 0 220px}.flex-outer li p{margin:0}.flex-outer li input:not([type='checkbox']),.flex-outer li textarea{padding:15px;border:0}.flex-outer li button{margin-left:auto;padding:8px 16px;border:0;background:red;color:#f2f2f2;text-transform:uppercase;letter-spacing:.09em;border-radius:2px}button{margin-left:auto;padding:8px 16px;border:0;background:red;color:#f2f2f2;text-transform:uppercase;letter-spacing:.09em;border-radius:2px}.flex-inner li{width:100px}@media screen and (max-width:600px){.col-25,.col-75,input[type=submit]{width:100%;margin-top:0}}.custom-select{position:relative}.custom-select select{display:none}.select-selected{background-color:#fff;color:#000}.select-selected:after{position:absolute;content:\"\";top:14px;right:10px;width:0;height:0;border:6px solid transparent;border-color:#000 transparent transparent transparent}.select-selected.select-arrow-active:after{border-color:transparent transparent #000 transparent;top:7px}.select-items div,.select-selected{color:#000;padding:8px 16px;border:1px solid transparent;border-color:transparent transparent rgba(0,0,0,0.1) transparent;cursor:pointer;user-select:none}.select-items{flex:1 0 120px;max-width:800px;position:absolute;background-color:#fff;top:100%;left:0;right:0;z-index:99}.select-hide{display:none}.select-items div:hover,.same-as-selected{background-color:rgba(0,0,0,0.1)}.container2{width:auto;margin:-50px 0 auto -35px}.progressbar{counter-reset:step}.progressbar li{list-style-type:none;width:33.3%;float:left;font-size:12px;position:relative;text-align:center;text-transform:uppercase;color:#7d7d7d}.progressbar li:before{width:30px;height:30px;content:counter(step);counter-increment:step;line-height:30px;border:2px solid #7d7d7d;display:block;text-align:center;margin:0 auto 10px auto;border-radius:50%;background-color:white}.progressbar li:after{width:100%;height:2px;content:'';position:absolute;background-color:#7d7d7d;top:15px;left:-50%;z-index:-1}.progressbar li:first-child:after{content:none}.progressbar li.active{color:green}.progressbar li.active:before{border-color:#55b776}.progressbar li.active+li:after{background-color:#55b776}.switch{position:relative;display:inline-block;width:60px;height:34px}.switch input{display:none}.slider{position:absolute;cursor:pointer;top:0;left:0;right:0;bottom:0;background-color:#7d7d7d;-webkit-transition:.4s;transition:.4s}.slider:before{position:absolute;content:\"\";height:26px;width:26px;left:4px;bottom:4px;background-color:white;-webkit-transition:.4s;transition:.4s}input:checked+.slider{background-color:#000}input:focus+.slider{box-shadow:0 0 1px #000}input:checked+.slider:before{-webkit-transform:translateX(26px);-ms-transform:translateX(26px);transform:translateX(26px)}.slider.round{border-radius:34px}.slider.round:before{border-radius:50%}</style>\r\n"
"</head>\r\n"
"<body>\r\n"
"<p class=footer id=copyright></p>\r\n"
"<div class=container2>\r\n"
"<ul class=progressbar>\r\n"
"<li id=1 class=active>WiFi</li>\r\n"
"<li id=2>Account</li>\r\n"
"<li id=3>Options</li>\r\n"
"</ul>\r\n"
"</div>\r\n"
"<br><br><br><br>\r\n"
"<div id=done>\r\n"
"<h1>All done!<br></h1><center>For the moment there are no options. Click on the button to save the configuration data.</center><br></div>\r\n"
"<h1 id=scanning>Scanning...<br></h1>\r\n"
"<h1 id=error>Something went wrong while communicating with the board...<br></h1>\r\n"
"<div id=connecting>\r\n"
"<h1>Connecting... <br></h1><center>(Your computer can disconnect from the WiFi. Don't close the page and check your computer's connected)</center><br><br></div>\r\n"
"<h1 id=mq_connecting>Connecting... <br></h1>\r\n"
"<div id=timeout>\r\n"
"<h1>It is taking too long to connect... <br></h1><center>(You can still wait as the board keeps trying to connect, but password may be wrong)</center><br></div>\r\n"
"<h1 id=connected><br></h1>\r\n"
"<form action id=wifi>\r\n"
"<ul class=\"flex-outer container\">\r\n"
"<li id=select>\r\n"
"<label>SSID:</label>\r\n"
"<div class=custom-select>\r\n"
"<select id=wifi_ssid placeholder>\r\n"
"</select>\r\n"
"</div>\r\n"
"</li>\r\n"
"<li id=custom>\r\n"
"<label>Hiden SSID:</label>\r\n"
"<input id=wifi_custom type=text name=# value placeholder>\r\n"
"</li>\r\n"
"<li>\r\n"
"<label>Password:</label>\r\n"
"<input id=wifi_pw type=text name=# value placeholder>\r\n"
"</li>\r\n"
"<li id=connect>\r\n"
"<button type=button onclick=connect()>Connect</button>\r\n"
"</li>\r\n"
"</ul>\r\n"
"</form>\r\n"
"<form action id=mq>\r\n"
"<ul class=\"flex-outer container\">\r\n"
"<li>\r\n"
"<label>Username:</label>\r\n"
"<input id=mq_user type=text name=# value placeholder>\r\n"
"</li>\r\n"
"<li>\r\n"
"<label>Password:</label>\r\n"
"<input id=mq_pw type=text name=# value placeholder>\r\n"
"</li>\r\n"
"</ul>\r\n"
"<br></form>\r\n"
"<button id=back type=button onclick=\"if(step>1){step=step-1;}progress()\">Previous</button>\r\n"
"<div style=float:right;text-align:right>\r\n"
"<button id=mq_connect type=button onclick='show(\"mq_connecting\");mq_connect()'>Connect</button>\r\n"
"<button id=save type=button onclick=save()>Save</button>\r\n"
"</div>\r\n"
"<div style=float:right;text-align:right>\r\n"
"<button id=next type=button onclick=\"step=step+1;progress()\">Next</button>\r\n"
"</div>\r\n"
"</body>\r\n"
"<script>var d=new Date();document.getElementById(\"copyright\").innerHTML=(\"Copyright &copy \"+d.getFullYear()+\" Efren Boyarizo\");function show(c){try{var a=document.getElementById(c);a.removeAttribute(\"style\")}catch(b){console.log(b)}}function hide(c){try{var a=document.getElementById(c);a.style.display=\"none\"}catch(b){console.log(b)}}function sleep(a){var c=new Date().getTime();for(var b=0;b<10000000;b++){if((new Date().getTime()-c)>a){break}}}var HttpClient=function(){this.get=function(c,a){var b=new XMLHttpRequest();b.onreadystatechange=function(){if(b.readyState===4&&b.status===200){a(b.responseText)}else{if(b.readyState===4&&(b.status<200||b.status>=304)){a(\",\")}}};b.open(\"GET\",c,true);b.send(null)}};function hideall(){hide(\"done\");hide(\"scanning\");hide(\"error\");hide(\"connecting\");hide(\"mq_connecting\");hide(\"timeout\");hide(\"connected\");hide(\"mq_connecting\");hide(\"wifi\");hide(\"mq\");hide(\"mq_connect\");hide(\"save\");hide(\"next\")}var interval=\"\";var step=1;hideall();var scan_tries=0;function update(){show(\"scanning\");var a=new HttpClient();a.get(\"http://192.168.1.1/scan\",function(e){if(e===\",\"){if(scan_tries>0){hideall();show(\"error\")}else{scan_tries=1;update()}}else{var b=document.getElementById(\"wifi_ssid\");if(e!==\"None\"){var j=(e).split(\"#\");var f=0;while(f<j.length&&j[f]!==\"\"){var h=j[f].split(\"/\");var g=document.createElement(\"option\");g.text=h[0]+\" (Signal: \"+h[1]+\")\";g.id=h[0];b.add(g);f=f+1}}var g=document.createElement(\"option\");g.text=\"Custom wifi...\";g.id=\"\";b.add(g);list();hide(\"scanning\");show(\"connect\");show(\"wifi\");custom();interval=setInterval(custom,200);var c=new HttpClient();c.get(\"http://192.168.1.1/check\",function(k){if(k!==\".\"&&k!==\",\"){hide(\"connecting\");document.getElementById(\"connected\").innerHTML=\"Connected to: \"+k;clearInterval(interval);show(\"connected\");show(\"next\")}else{var i=new HttpClient();i.get(\"http://192.168.1.1/check\",function(l){if(l!==\".\"&&l!==\",\"){hide(\"connecting\");document.getElementById(\"connected\").innerHTML=\"Connected to: \"+l;clearInterval(interval);show(\"connected\");show(\"next\")}else{if(l===\",\"){hideall();show(\"error\")}}})}})}})}update();function custom(){var a=document.getElementById(\"wifi_ssid\");if(a.options[a.selectedIndex].id!==\"\"){hide(\"custom\")}else{show(\"custom\")}}function connect(){clearInterval(interval);hideall();show(\"connecting\");var e=document.getElementById(\"wifi_ssid\");var b=document.getElementById(\"wifi_pw\");var f=document.getElementById(\"wifi_custom\");if(e.options[e.selectedIndex].id!==\"\"){var c=\"http://192.168.1.1/test?ssid=\"+e.options[e.selectedIndex].id+\"&pass=\"+b.value;console.log(c)}else{var c=\"http://192.168.1.1/test?ssid=\"+f.value+\"&pass=\"+b.value;console.log(c)}var a=new HttpClient();a.get(c,function(g){if(g===\",\"){console.log(\"Something went wrong while communicating with the board...\")}else{console.log(this.responseText);check()}})}var timeout=0;function check(){var a=new HttpClient();a.get(\"http://192.168.1.1/check\",function(b){if(b===\",\"){clearInterval(interval);alert(\"Reconnect to the WiFi before continuing...\");sleep(2000);check()}else{if(b===\".\"){timeout=timeout+1;show(\"connecting\");if(timeout>25){show(\"timeout\");hide(\"connecting\")}check()}else{hide(\"connecting\");document.getElementById(\"connected\").innerHTML=\"Connected to: \"+b;show(\"connected\");show(\"next\")}}console.log(b)})}function progress(){var b=document.getElementById(\"1\");var a=document.getElementById(\"2\");var c=document.getElementById(\"3\");if(step===1){b.classList.add(\"active\");a.classList.remove(\"active\");c.classList.remove(\"active\");hideall();location.reload()}else{if(step===2){b.classList.add(\"active\");a.classList.add(\"active\");c.classList.remove(\"active\");hideall();hide(\"next\");show(\"mq_connect\");show(\"mq\")}else{if(step===3){b.classList.add(\"active\");a.classList.add(\"active\");c.classList.add(\"active\");hideall();show(\"done\");show(\"save\")}}}}function mq_connect(){var c=document.getElementById(\"mq_user\").value;var b=document.getElementById(\"mq_pw\").value;var a=\"http://192.168.1.1/mqtt?user=\"+c+\"&pw=\"+b;check_connection(a)}function check_connection(b){var a=new HttpClient();a.get(b,function(c){if(c===\",\"){hideall();show(\"error\")}else{var e=Number(c);console.log(e);if(e===9){alert(\"Wrong user or password\");hide(\"mq_connecting\")}else{if(e<0){alert(\"Can't reach server, please check WiFi\");hide(\"mq_connecting\")}else{if(e===0){alert(\"Connected!\");step=3;progress()}else{alert(\"Something went wrong :(\");hide(\"mq_connecting\")}}}}})}function save(){var a=new HttpClient();a.get(\"http://192.168.1.1/save\",function(b){if(b===\"OK\"){window.location.replace(\"http://192.168.1.1/reboot\")}else{alert(\"Something went wrong\")}})}</script>\r\n"
"<script>function list(){var f,l,k,h,g,e,m;f=document.getElementsByClassName(\"custom-select\");for(l=0;l<f.length;l++){h=f[l].getElementsByTagName(\"select\")[0];g=document.createElement(\"DIV\");g.setAttribute(\"class\",\"select-selected\");g.innerHTML=h.options[h.selectedIndex].innerHTML;f[l].appendChild(g);e=document.createElement(\"DIV\");e.setAttribute(\"class\",\"select-items select-hide\");for(k=0;k<h.length;k++){m=document.createElement(\"DIV\");m.innerHTML=h.options[k].innerHTML;m.addEventListener(\"click\",function(n){var o,b,a,j,c;j=this.parentNode.parentNode.getElementsByTagName(\"select\")[0];c=this.parentNode.previousSibling;for(b=0;b<j.length;b++){if(j.options[b].innerHTML==this.innerHTML){j.selectedIndex=b;c.innerHTML=this.innerHTML;o=this.parentNode.getElementsByClassName(\"same-as-selected\");for(a=0;a<o.length;a++){o[a].removeAttribute(\"class\")}this.setAttribute(\"class\",\"same-as-selected\");break}}c.click()});e.appendChild(m)}f[l].appendChild(e);g.addEventListener(\"click\",function(a){a.stopPropagation();closeAllSelect(this);this.nextSibling.classList.toggle(\"select-hide\");this.classList.toggle(\"select-arrow-active\")})}document.addEventListener(\"click\",closeAllSelect)}function closeAllSelect(e){var a,f,c,b=[];a=document.getElementsByClassName(\"select-items\");f=document.getElementsByClassName(\"select-selected\");for(c=0;c<f.length;c++){if(e==f[c]){b.push(c)}else{f[c].classList.remove(\"select-arrow-active\")}}for(c=0;c<a.length;c++){if(b.indexOf(c)){a[c].classList.add(\"select-hide\")}}};</script>\r\n"
"</html>\r\n";

const char reboot_html[] PROGMEM = "<!DOCTYPE html>\r\n"
"<html>\r\n"
"<head>\r\n"
"<style>body{height:100vh;padding:0;margin:0;overflow:hidden;background-color:#2b3e4c}.wrapper{position:relative;top:50%;width:100%;text-align:center;-webkit-transform:translateY(-50%);transform:translateY(-50%);z-index:1}.bubbles{position:absolute;top:0;width:44px;height:44px;margin:auto;border-radius:100%;-webkit-animation-name:up-down;animation-name:up-down;-webkit-animation-duration:1.3s;animation-duration:1.3s;-webkit-animation-timing-function:cubic-bezier(.42,0,.58,1);animation-timing-function:cubic-bezier(.42,0,.58,1);-webkit-animation-iteration-count:infinite;animation-iteration-count:infinite;-webkit-animation-fill-mode:both;animation-fill-mode:both;-webkit-animation-direction:alternate;animation-direction:alternate}.tube{position:relative;display:inline-block;width:45px;height:200px;background-color:grey;border-radius:22px;overflow:hidden}.colored-tube{position:absolute;top:-80%;width:100%;height:100%;border-radius:22px;-webkit-animation-name:up-down;animation-name:up-down;-webkit-animation-duration:1.3s;animation-duration:1.3s;-webkit-animation-timing-function:cubic-bezier(.42,0,.58,1);animation-timing-function:cubic-bezier(.42,0,.58,1);-webkit-animation-iteration-count:infinite;animation-iteration-count:infinite;-webkit-animation-fill-mode:both;animation-fill-mode:both;-webkit-animation-direction:alternate;animation-direction:alternate}.ck1{background-color:#bc86e2}.ck2{background-color:#2bb3e8;-webkit-animation-delay:200ms;animation-delay:200ms}.ck3{background-color:#4eda7b;-webkit-animation-delay:300ms;animation-delay:300ms}.ck4{background-color:#ffd30e;-webkit-animation-delay:400ms;animation-delay:400ms}.ck5{background-color:#ff5a58;-webkit-animation-delay:500ms;animation-delay:500ms}#b1{background-color:#8861a4}#b2{background-color:#2495c1;-webkit-animation-delay:200ms;animation-delay:200ms}#b3{background-color:#48bb6d;-webkit-animation-delay:300ms;animation-delay:300ms}#b4{background-color:#f1c500;-webkit-animation-delay:400ms;animation-delay:400ms}#b5{background-color:#f35957;-webkit-animation-delay:500ms;animation-delay:500ms}@-webkit-keyframes up-down{0%{top:0}100%{top:156px}}@keyframes up-down{0%{top:0}100%{top:156px}}h1{font-size:xx-large;color:#fff;width:100%;text-align:center;margin:0;position:absolute;top:15px;left:50%;transform:translate(-50%,-50%);letter-spacing:4px;top:30%;font-weight:bold}h2{font-size:large;color:#fff;width:100%;text-align:center;margin:0;position:absolute;top:50%;left:50%;transform:translate(-50%,-50%);letter-spacing:4px;top:80%;font-weight:bold}h3{font-size:large;color:#fff;width:100%;text-align:center;margin:0;position:absolute;top:50%;left:50%;transform:translate(-50%,-50%);letter-spacing:4px;top:85%;font-weight:bold}</style>\r\n"
"<meta charset=UTF-8>\r\n"
"</head>\r\n"
"<body>\r\n"
"<h1>All settings saved. Rebooting...</h1>\r\n"
"<div class=\"danBkg display-none\"></div>\r\n"
"<meta name=viewport content=\"width=device-width, initial-scale=1\">\r\n"
"<div class=wrapper>\r\n"
"<div class=tube>\r\n"
"<div class=\"colored-tube ck1\"></div>\r\n"
"<div class=bubbles id=b1></div>\r\n"
"</div>\r\n"
"<div class=tube>\r\n"
"<div class=\"colored-tube ck2\"></div>\r\n"
"<div class=bubbles id=b2></div>\r\n"
"</div>\r\n"
"<div class=tube>\r\n"
"<div class=\"colored-tube ck3\"></div>\r\n"
"<div class=bubbles id=b3></div>\r\n"
"</div>\r\n"
"<div class=tube>\r\n"
"<div class=\"colored-tube ck4\"></div>\r\n"
"<div class=bubbles id=b4></div>\r\n"
"</div>\r\n"
"<div class=tube>\r\n"
"<div class=\"colored-tube ck5\"></div>\r\n"
"<div class=bubbles id=b5></div>\r\n"
"</div>\r\n"
"</div>\r\n"
"<div class=\"danBkg display-none\"></div>\r\n"
"<h3></h3>\r\n"
"</body>\r\n"
"</html>\r\n";

#endif