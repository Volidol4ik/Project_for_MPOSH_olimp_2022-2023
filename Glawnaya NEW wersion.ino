#include <ESP8266WiFi.h>
#include <espnow.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;
// Structure example to receive data
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  


uint8_t broadcastAddress[] = {0x48, 0x3F, 0xDA, 0x54, 0xF5, 0x31};        // МАС адрес получателя

uint8_t broadcastAddress1[] = {0x48, 0x3F, 0xDA, 0x54, 0xF5, 0x31};        // МАС адрес получателя

uint8_t broadcastAddress2[] = {0x48, 0x3F, 0xDA, 0x54, 0xF5, 0x31};        // МАС адрес получателя

#define BOARD_ID 3  
// Must match the sender structure
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

// Create a struct_message called myData
struct_message myData;

// Callback function that will be executed when data is received
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.println(myData.x);
  Serial.println(myData.y);
  Serial.println(myData.z);
  Serial.println(myData.x2);
  Serial.println(myData.y2);
  Serial.println(myData.z2);
  Serial.println();
}

void setup() {

  // initialize LCD
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight();
  // Initialize Serial Monitor
  Serial.begin(115200);
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
   esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_CONTROLLER, 1, NULL, 0);     // Регистрируем пиры esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);     // Регистрируем пиры 
  esp_now_add_peer(broadcastAddress1, ESP_NOW_ROLE_CONTROLLER, 1, NULL, 0);     // Регистрируем пиры  
   esp_now_add_peer(broadcastAddress1, ESP_NOW_ROLE_CONTROLLER, 1, NULL, 0);

}

void loop() {
    // на помпу
   int board1pch = (myData.x + myData.x2)/2;
   myData.id = BOARD_ID;
   myData.pochva = board1pch;                                                         // Отправляем данные                                                  
   esp_now_send(0, (uint8_t *) &myData, sizeof(myData));                // Отправляем сообщение
   delay(2000);
  //  на увлажнитель
   int board1voz = (myData.y + myData.y2)/2;
   myData.id = BOARD_ID;
   myData.vozduh = board1voz;                                                         // Отправляем данные                                                  
   esp_now_send(0, (uint8_t *) &myData, sizeof(myData));                // Отправляем сообщение
   delay(2000);
  // на мотор  
   int board1temp = (myData.z + myData.z2)/2;
   myData.id = BOARD_ID;
   myData.temper = board1temp;                                                         // Отправляем данные                                                  
   esp_now_send(0, (uint8_t *) &myData, sizeof(myData));                // Отправляем сообщение
   delay(2000); 
   
  
    if( myData.x == 0 or myData.y== 0 or myData.z == 0){
      digitalWrite(8, HIGH);
      delay(1000); 
      digitalWrite(8, LOW);
      delay(1000);
    
}
    else{
      digitalWrite(8, LOW); 
    }
  lcd.print("Temp: ");
  lcd.print(myData.x);
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(myData.y);
  
  Serial.println(myData.x);
  Serial.println(myData.y);
  Serial.println(myData.z);
  delay(1000);
}


