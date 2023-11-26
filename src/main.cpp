#include "util.h"

Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup()
{
  Serial.begin(115200);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println(F("SSD1306 allocation failed"));
  }
  delay(2000);
  display.clearDisplay();
  display.setTextColor(WHITE);

  initConnectWifi();
  httpClientRequest("http://api.pinduoduo.com/api/server/_stm");
  httpClientRequest("http://api.m.taobao.com/rest/api3.do?api=mtop.common.getTimestamp");
  httpClientRequest("http://vv6.video.qq.com/checktime");
}

void loop()
{

  // // 3秒刷新显示内容
  delay(3000);
  // 清空显示
  display.clearDisplay();
  // 使更改的显示生效
  display.display();
  display.setTextSize(1); // 设置字体大小（1~8）
  display.setCursor(0, 0);       // 设置坐标
  display.print("content");        // 显示内容
  display.display();
  // display.print("2022-03-18 21:66:18");
}
