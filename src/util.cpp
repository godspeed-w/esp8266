#include "util.h"

/*!
    @brief  通发送HTTP请求并且将服务器响应通过串口输出
*/
String httpClientRequest(String URL)
{
    String response = "";
    // 重点1 创建 HTTPClient 对象
    HTTPClient httpClient;
    WiFiClient wifiClient;
    // 重点2 通过begin函数配置请求地址。此处也可以不使用端口号和PATH而单纯的
    httpClient.begin(wifiClient, URL);
    httpClient.setTimeout(3000);
    // 重点3 通过GET函数启动连接并发送HTTP请求
    int httpCode = httpClient.GET();
    Serial.printf("Send GET request to URL:%s\n", URL.c_str());
    // 重点4. 如果服务器响应HTTP_CODE_OK(200)则从服务器获取响应体信息并通过串口输出
    // 如果服务器不响应HTTP_CODE_OK(200)则将服务器响应状态码通过串口输出
    if (httpCode == HTTP_CODE_OK)
    {
        // 使用getString函数获取服务器响应体内容
        response = httpClient.getString();
        Serial.println("Server Response Payload: ");
        Serial.println(response);
    }
    else
    {
        response = (String)httpCode;
        Serial.printf("Server Respose Code: %d\n", httpCode);
    }
    // 重点5. 关闭ESP8266与服务器连接
    httpClient.end();
    return response;
}

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
    @brief 初始化Oled
*/
void initOled(Adafruit_SSD1306 dispaly)
{
    if (!dispaly.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println(F("SSD1306 allocation failed"));
    }
    delay(2000);
    dispaly.clearDisplay();
    dispaly.setTextColor(WHITE);
}

/*!
    @brief oled显示,字体大小（1~8), 坐标x，坐标y，显示内容
*/
void oledShow(Adafruit_SSD1306 dispaly, int TextSize, int x, int y, String content)
{
    dispaly.setTextSize(TextSize); // 设置字体大小（1~8）
    dispaly.setCursor(x, y);       // 设置坐标
    dispaly.print(content);        // 显示内容
}