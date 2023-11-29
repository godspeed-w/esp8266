#include <U8g2lib.h>

// U8G2_SH1106_128X64_NONAME_1_4W_SW_SPI u8g2 (/*显示方向*/U8G2_R0, /*clock/SCL*/D1, /*data/SDA*/D2, /*cs(GND)*/U8X8_PIN_NONE ,/*DC*/D4 ,/*reset/RST*/D3);
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /*clock=*/D1, /*data=*/D2, /*reset=*/U8X8_PIN_NONE);

int i;
void setup()
{
  u8g2.begin(); // 显示器初始化
  u8g2.enableUTF8Print();
}

void loop()
{
  i++;
  if (i == 100)
    i = 0;
  u8g2.firstPage(); // 此为显示循环
  do
  {
    u8g2.drawFrame(9, 25, 103, 15);          // 画空方框
    u8g2.drawBox(12, 27, i, 11);             // 画实心方形
    u8g2.setFont(u8g2_font_wqy14_t_gb2312a); // 设置中文字体
    u8g2.setCursor(20, 20);
    u8g2.print("系统初始化");
    u8g2.setFont(u8g2_font_ncenB10_tr); // 设置字符串字体
    u8g2.setCursor(54, 54);
    u8g2.print(i);
  } while (u8g2.nextPage());
}
