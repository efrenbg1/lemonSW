#include "MqTLS.h"

MqTLS::MqTLS(String thumbprint)
{
	client.setTimeout(3000);
	client.setFingerprint(thumbprint.c_str());
}

String MqTLS::enc(String &var)
{
	if (var.length() < 10)
	{
		return "0" + String(var.length()) + var;
	}
	else if (var.length() < 100)
	{
		return String(var.length()) + var;
	}
	return "00";
}

//-1 not connected to server
//1 Publish done
int MqTLS::publish(String topic, String slot, String payload)
{
	if (!client.connected())
	{
		return -1;
	}
	String command = "MQS1" + enc(topic) + slot + enc(payload) + "\n";
	client.print(command);
	String line = "";
	unsigned long start = millis();
	while (client.connected())
	{
		if (client.available())
		{
			line = client.readStringUntil('\n');
			if (line.indexOf("MQS1") > -1)
				return 1;
			if (secBuff.length() < 1000)
				secBuff += line;
		}
		if ((millis() - start) > 2000)
			break;
	}
	return -1;
}

//-1 not connected to server
//1 Lastwill added
int MqTLS::lastwill(String topic, String slot, String payload)
{
	if (!client.connected())
	{
		return (-1);
	}
	String command = "MQS3" + enc(topic) + slot + enc(payload) + "\n";
	client.print(command);
	String line = "";
	unsigned long start = millis();
	while (client.connected())
	{
		if (client.available())
		{
			line = client.readStringUntil('\n');
			if (line.indexOf("MQS3") > -1)
				return 1;
			if (secBuff.length() < 1000)
				secBuff += line;
		}
		if ((millis() - start) > 2000)
			break;
	}
	return (-1);
}

//-1 not connected to server
//1 Watch added
int MqTLS::watch(String topic)
{
	if (!client.connected())
	{
		return -1;
	}
	String command = "MQS4" + enc(topic) + "\n";
	client.print(command);
	String line = "";
	unsigned long start = millis();
	while (client.connected())
	{
		if (client.available())
		{
			line = client.readStringUntil('\n');
			if (line.indexOf("MQS4") > -1)
				return 1;
			if (secBuff.length() < 1000)
				secBuff += line;
		}
		if ((millis() - start) > 2000)
			break;
	}
	return -1;
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
	String command = "MQS2" + enc(topic) + slot + "\n";
	client.print(command);
	String line = "";
	unsigned long start = millis();
	while (client.connected())
	{
		if (client.available())
		{
			line = client.readStringUntil('\n');
			if (line.indexOf("MQS2") > -1)
				break;
			if (line.indexOf("MQS7") > -1)
				break;
			if (line.indexOf("MQS8") > -1)
				break;
			if (secBuff.length() < 1000)
				secBuff += line;
		}
		if ((millis() - start) > 2000)
			return -2;
	}

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

//-3 protocol error
//-1 not connected to server
//5 watch retrieve done
//7 no data received
int MqTLS::callback(String *slot, String *payload)
{
	*payload = "";
	if (!client.connected())
		return -1;

	int i = secBuff.indexOf('\n');
	String line = "";

	if (i > -1)
	{
		line = secBuff.substring(0, i + 1);
		secBuff = secBuff.substring(i + 1);
	}
	else
	{
		if (client.available() == 0)
			return 7;
		line = client.readStringUntil('\n');
		secBuff = "";
	}
	Serial.println(line);
	if (line.length() > 7 && line.indexOf("MQS5") == 0)
	{
		*slot = String(line.substring(4, 5)).toInt();
		unsigned int pay_end = String(line.substring(5, 7)).toInt();
		if (line.length() > (7 + pay_end - 1))
		{
			*payload = line.substring(7, 7 + pay_end);
			return 5;
		}
	}
	return -3;
}

//-3 protocol error
//-2 response timed out (2s)
//-1 connection error (server not available)
//0 connected
//9 error auth
int MqTLS::connect(String addr, int port, String user, String pw, bool qos)
{
	if (!client.connected())
	{
		if (!client.connect(addr, port))
		{
			return -1;
		}
	}
	if (client.connected())
	{
		secBuff = "";
		if (client.available())
		{
			client.readString();
		}
		client.print(String("MQS0" + enc(user) + enc(pw) + (qos ? "1" : "0") + "\n"));
		String line = "";
		unsigned long start = millis();
		while (client.connected())
		{
			if (client.available())
			{
				line = client.readStringUntil('\n');
				if (line.indexOf("MQS0") > -1)
					return 0;
			}
			if ((millis() - start) > 2000)
				break;
		}
		return 9;
	}
	return -1;
}