#include <ESP8266WiFi.h>

void setup(){
  Serial.begin(115200);
  Serial.println(WiFi.macAddress());    // Определяем MAC адрес платы
}
 
void loop(){
  Serial.print("MAC адрес платы:  ");
  Serial.println(WiFi.macAddress());
  delay(5000);
}

//трекер 2C:F4:32:3C:DA:51
//светодиод
//ветер
//главная CC:50:E3:70:50:F3
