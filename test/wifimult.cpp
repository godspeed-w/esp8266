/*
    通过wifimulti连接多个固定的网络
*/
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti WiFiMulti;

void setup()
{
    Serial.begin(115200);
    Serial.println();
    Serial.println();
    Serial.println();

    for (uint8_t t = 4; t > 0; t--)
    {
        Serial.printf("[SETUP] WAIT %d...\n", t);
        Serial.flush();
        delay(500);
    }

    WiFi.mode(WIFI_STA);
    WiFiMulti.addAP("WJ", "wj1234567");
    WiFiMulti.addAP("TEST", "password");
    if ((WiFiMulti.run() == WL_CONNECTED))
    {
        Serial.print("ESP8266 Connected to ");
        Serial.println(WiFi.SSID()); // WiFi名称
        Serial.print("IP address:\t");
        Serial.println(WiFi.localIP()); // 打印出IP
    }
}

void loop()
{
}