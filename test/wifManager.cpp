/*
  使用WiFiManager配置互联网连接
*/
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

void setup()
{
  Serial.begin(9600);
  // 建立WiFiManager对象
  WiFiManager wifiManager;
  // wifiManager.resetSettings();
  // 自动连接WiFi。以下语句的参数是连接ESP8266时的WiFi名称
  wifiManager.autoConnect("小猪佩奇");
  // WiFi连接成功后将通过串口监视器输出连接成功信息
  Serial.println("");
  Serial.print("ESP8266 Connected to ");
  Serial.println(WiFi.SSID()); // WiFi名称
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP()); // 打印出IP
}

void loop()
{
}