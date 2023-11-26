/*
  Arduino 解析json
*/
#include <Arduino.h>
#include <ArduinoJson.h>

void setup()
{
  Serial.begin(115200);
  DynamicJsonDocument doc(1024);
  for (uint8_t t = 4; t > 0; t--)
  {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(500);
  }
  // 这里暂时用String类型的变量来代替串口获取的Json数据
  String input = "{\"id\":\"l or r\",\"speed\":10.50, \"kp\":5.1, \"ki\":0.1, \"kd\":0.02, \"forward\":1}";
  deserializeJson(doc, input);
  JsonObject obj = doc.as<JsonObject>();
  // 到这里可以用 obj[键名] 提取数据
  Serial.println((String)obj["id"]);
  Serial.println((String)obj["speed"]);

  // 可以将他们存入变量
  String id = obj["id"];
  float speed = obj["speed"];
  float kp = obj["kp"];
  float ki = obj["ki"];
  float kd = obj["kd"];
  bool forward = obj["forward"];
  Serial.printf("kp:%f, ki:%f, kd:%f, forward:%d",kp,ki,kd,forward);

  // 注意：Json的值可以为列表哦，到这里就是一维数组。这里没用到。
  // 如果是 { "PID":[5.1, 0.1, 0.02] }
  // 则可以 kp = obj["PID"][0], ki = obj["PID"][1], kd = obj["PID"][2]
}

void loop()
{
  // not used in this example
}