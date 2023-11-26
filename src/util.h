#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>


String httpClientRequest(String URL);
bool initConnectWifi();

void initOled(Adafruit_SSD1306 dispaly);
void oledShow(Adafruit_SSD1306 dispaly, int TextSize, int x, int y, String content);