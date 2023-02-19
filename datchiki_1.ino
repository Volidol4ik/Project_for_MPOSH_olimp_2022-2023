#include <ESP8266WiFi.h>
#include <Adafruit_Sensor.h>
#include <espnow.h>
#include "DHT.h"

#define sensorPin A0
#define DHTPIN 5
DHT dht(DHTPIN, DHT11);
                                                      
int p;
uint8_t broadcastAddress[] = {0x48, 0x3F, 0xDA, 0x54, 0xF5, 0x31};        // МАС адрес получателя

#define BOARD_ID 1                                                        // Устанавливаем ID платы как 1

// структуры для отправки данных
typedef struct struct_message {
    int id;
    int x;
    int y;
    int z;
    int x2;
    int y2;
    int z2;
    int pochva;
    int temper;
    int vozduh;
} struct_message;

struct_message myData;                                                    // Создайте сообщение с именем myData для хранения отправляемых переменных

unsigned long lastTime = 0;                                               // Переменная для хранения времени
unsigned long timerDelay = 10000;                                         // Задержка в 10 сек между отправками пакетов данных

// Callback-функция при отправке сообщения
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("\r\nСтатус Отправки Последнего Пакета: ");
  if (sendStatus == 0){ Serial.println("Сообщение доставлено"); }
  else{ Serial.println("Сообщение НЕ доставлено"); }
}

void setup() {  
  dht.begin();
 Serial.begin(115200);                                                   // Запускаем монитор порта на скорости 115200 бод
  WiFi.mode(WIFI_STA);                                                    // Режим работы Клиент
  WiFi.disconnect();
  
  // Инициализируем ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Ошибка инициализации ESP-NOW");
    return;
  } 
  
  // Роль платы в ESP-NOW
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);  
  esp_now_register_send_cb(OnDataSent);                                   // Получаем сообщение об отправке
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);     // Регистрируем пиры
}

void loop() {
  float h = dht.readHumidity();     // get humidity
  float t = dht.readTemperature();  // get temperature
  
  if ((millis() - lastTime) > timerDelay) {                               // Если прошло больше 10 секунд
  p = analogRead(sensorPin);                                           // Считываем освещённость
    myData.id = BOARD_ID;
    myData.x = p;
    myData.y = h; 
    myData.z = t;                                                  
    esp_now_send(0, (uint8_t *) &myData, sizeof(myData));                 // Отправляем сообщение
    lastTime = millis();
  }
}
