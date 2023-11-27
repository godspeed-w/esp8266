#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

bool initConnectWifi()
{
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
  if (WiFi.status() != WL_CONNECTED)
  {
    return false;
  }
  return true;
}

void syncNetWorkTime()
{
  const char *ntpServer = "pool.ntp.org";
  long gmtOffset_sec = 8 * 3600;
  int daylightOffset_sec = 0;
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

void printLocalTime()
{
  char datetime[128];
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time");
  }
  strftime(datetime, 128, "%Y-%m-%d %H:%M:%S", &timeinfo);
  Serial.printf("%s\n", datetime); // 格式化输出
}

void setup()
{
  Serial.begin(115200);
  initConnectWifi();

  syncNetWorkTime();
  printLocalTime();
}

void loop()
{
  delay(1000);
  printLocalTime();
}
