#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup() {
  Serial.begin(115200); //打开串口通讯，设置传输速率为115200字节每秒
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  delay(2000);
  display.clearDisplay();
  display.setTextColor(WHITE);
}

int flag = 1;

void loop() {

  // 3秒刷新显示内容
  delay(3000);
  // 清空显示
  display.clearDisplay();
  // 使更改的显示生效
  display.display();

  // 判断应该显示的内容
  flag = flag % 4;
  if (flag == 1) {
    // 这段时间可以显示时间
    display.setTextSize(1);  // 设置字体大小（1~8）
    display.setCursor(0, 0); // 设置坐标
    display.print("Time:"); // 显示内容
    display.setTextSize(2);
    display.setCursor(0, 15);
    display.print("2022-03-18 21:66:18");
  } if (flag == 2) {
    // 这段时间可以显示天气
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("Weather: ");
    display.setTextSize(2);
    display.setCursor(0, 15);
    display.print("Sunny ");
    display.print(28.6);
    display.setTextSize(1);
    display.cp437(true);
    display.write(167);
    display.setTextSize(2);
    display.print("C");
  } if (flag == 3) {
    // 这段时间可以显示温度
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("Temperature: ");
    display.setTextSize(2);
    display.setCursor(0, 15);
    display.print(28.6);
    display.print(" ");
    display.setTextSize(1);
    display.cp437(true);
    display.write(167);
    display.setTextSize(2);
    display.print("C");
  } else  if (flag == 0) {
    Serial.println("show humidity 4 \n");
    // 这段时间可以显示湿度
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("Humidity: ");
    display.setTextSize(2);
    display.setCursor(0, 15);
    display.print(46);
    display.print(" %");
  }
  flag++;

  display.display();
}
