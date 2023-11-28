#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/*!
    @brief  通过wifiManager配置wifi连接
*/
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

/*!
  @brief 同步服务器时间
*/
void syncNetWorkTime()
{
  const char *ntpServer = "pool.ntp.org";
  long gmtOffset_sec = 8 * 3600;
  int daylightOffset_sec = 0;
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

/*!
  @brief 串口打印本地时间
*/
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

/*!
    @brief 初始化Oled
*/
void initOled(Adafruit_SSD1306 *display)
{
  if (!display->begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println(F("SSD1306 allocation failed"));
  }
  display->clearDisplay();
  display->setTextColor(WHITE);
}

/*!
    @brief oled显示,字体大小（1~8), 坐标x，坐标y，显示内容
*/
void oledShow(Adafruit_SSD1306 *display, int TextSize, int x, int y, String content)
{
  display->setTextSize(TextSize); // 设置字体大小（1~8）
  display->setCursor(x, y);       // 设置坐标
  display->print(content);        // 显示内容
}

/*!
    @brief oled显示,字体大小（1~8), 坐标x，坐标y，显示内容
*/
void oledShowDateAndTime(Adafruit_SSD1306 *display, int TextSize, int x, int y)
{
  display->setTextSize(TextSize); // 设置字体大小（1~8）
  display->setCursor(x, y);       // 设置坐标
  char datetime[128];
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time");
  }
  strftime(datetime, 128, "%Y-%m-%d %H:%M:%S", &timeinfo);
  display->print(datetime); // 显示内容
}

/***************全局变量**********************************/
Adafruit_SSD1306 OLED(128, 64, &Wire, -1);
int ledState = LOW;
unsigned long previousMillis = 0;
const long interval = 1000;
/***************主程序**********************************/
void setup()
{
  Serial.begin(115200);
  initOled(&OLED);
  oledShow(&OLED, 2, 0, 0, "Begin");
  OLED.display();

  delay(500);
  oledShow(&OLED, 1, 0, 24, "Waiting online service ...");
  OLED.display();
  initConnectWifi();

  syncNetWorkTime();
  printLocalTime();

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    ledState = ~ledState;
    digitalWrite(LED_BUILTIN, ledState);

    OLED.clearDisplay();
    printLocalTime();
    oledShowDateAndTime(&OLED, 2, 0, 15);
    oledShow(&OLED, 1, 0, 56, WiFi.localIP().toString());
    OLED.display();
  }
}
