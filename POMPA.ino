#include <ESP8266WiFi.h>
#include <espnow.h>
#define POMP_PIN 4
#define sensorPower 7
#define sensorPin A0

int led = 8;

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

struct_message myData;

void OnDataRecv(uint8_t * mac_addr, uint8_t *incomingData, uint8_t len) {
  char macStr[18];
  memcpy(&myData, incomingData, sizeof(myData));
}
 
void setup() {
  pinMode(sensorPower, OUTPUT);
  digitalWrite(sensorPower, LOW);
 
  pinMode(POMP_PIN, OUTPUT);

  // Initialize Serial Monitor
  Serial.begin(115200);
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
}

void loop(){
  
  digitalWrite(sensorPower, HIGH);  // Включить датчик
  delay(10);                        // Ждать 10 миллисекунд
  int val = analogRead(sensorPin);  // Прочитать аналоговое значение от датчика
  digitalWrite(sensorPower, LOW);   // Выключить датчик

 if(  val < 500){
   digitalWrite(led, HIGH);
   delay(1000);
   digitalWrite(led, LOW);
   delay(1000);
  }
  else{
   digitalWrite(led, LOW);
   delay(1000);
  }
  int board2pochva =  myData.pochva;
  if(  board2pochva < 500){
   digitalWrite(POMP_PIN, HIGH);
   delay(5000);
  }
  else{
   digitalWrite(POMP_PIN, LOW);
  delay(2000);
  }
}
