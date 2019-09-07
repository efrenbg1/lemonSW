#include "MqTLS.h"

void MqTLS::disconnect(void)
{
  client.stop();
}

MqTLS::MqTLS(String thumbprint)
{
  client.setTimeout(2000);
  client.setFingerprint(thumbprint.c_str());
}

String MqTLS::getlength(String &var)
{
  if (var.length() < 10)
  {
    return ("0" + String(var.length()));
  }
  else if (var.length() < 100)
  {
    return (String(var.length()));
  }
  return "00";
}

//-1 not connected to server
//1 Publish done
int MqTLS::publish(String topic, String slot, String payload)
{
  if (!client.connected())
  {
    return (-1);
  }
  String command = "MQS1" + getlength(topic) + topic + slot + getlength(payload) + payload + "\n";
  //Serial.println(command);
  client.print(command);
  return (1);
}



//-1 not connected to server
//1 Publish done
int MqTLS::lastwill(String topic, String slot, String payload)
{
  if (!client.connected())
  {
    return (-1);
  }
  String command = "MQS3" + getlength(topic) + topic + slot + getlength(payload) + payload + "\n";
  client.print(command);
  String line = "";
  while (client.connected() || client.available() > 0)
  {
    if (client.available())
    {
      line = client.readStringUntil('\n');
      break;
    }
  }
  if (line.indexOf("MQS3") > -1)
  {
    return (1);
  }
  else
  {
    return (-1);
  }
}

//-3 protocol error
//-2 timed out
//-1 not connected to server
//2 retrieve done
//7 no data in topic
//8 no valid acls
//9 error auth
int MqTLS::retrieve(String topic, String slot, String *payload)
{
  if (!client.connected())
  {
    *payload = "";
    return (-1);
  }
  while (client.available() > 0)
  {
    client.readStringUntil('\n');
  }
  String command = "MQS2" + getlength(topic) + topic + slot + "\n";
  //Serial.println(command);
  client.print(command);
  String line = "";
  while (client.connected() || client.available() > 0)
    {
      if (client.available())
      {
        line = client.readStringUntil('\n');
        break;
      }
    }
  if (line.indexOf("MQS") == 0)
  {
    int resp = String(line.substring(3, 4)).toInt();
    if (resp == 2)
    {
      int pay_end = String(line.substring(4, 6)).toInt();
      *payload = line.substring(6, 6 + pay_end);
    }
    else
    {
      *payload = "";
    }
    return (resp);
  }
  *payload = "";
  return (-3);
}

//-3 protocol error
//-2 response timed out (2s)
//-1 connection error (server not available)
//0 connected
//9 error auth
int MqTLS::connect(String addr, int port, String user, String pw)
{
  if (!client.connected())
  {
    if (!client.connect(addr, port))
    {
      return (-1);
    }
  }
  if (client.connected())
  {
    client.print(String("MQS0" + getlength(user) + user + getlength(pw) + pw + "\n"));
    String line = "";
    while (client.connected() || client.available() > 0)
    {
      if (client.available())
      {
        line = client.readStringUntil('\n');
        break;
      }
    }
    if (line.indexOf("MQS0") == 0)
    {
      return (0);
    }
    else
    {
      return (9);
    }
  }
  else
  {
    return (-1);
  }
}