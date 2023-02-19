#include <AccelStepper.h>
#include <MultiStepper.h>
#include <ESP8266WiFi.h>
#include <espnow.h>
#define pinStep 2
#define pinDir 3
int a = 0;
int dovl;
#define steps_rotate_360 200
int fsrAnalogPin = 0;
int fsrReading;
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
   pinMode(pinStep, OUTPUT);
  pinMode(pinDir, OUTPUT);
//устанавливаем начальный режим
  digitalWrite(pinStep, HIGH);
  digitalWrite(pinDir, LOW);

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
fsrReading = analogRead(fsrAnalogPin);
dovl = map(fsrReading, 0, 1023, 0, 255);
if( dovl > 100 and a == 3){
digitalWrite(pinDir, LOW);

  for(int i = 0; i < steps_rotate_360; i++)
  {
  digitalWrite(pinStep, HIGH);   
  delay(500) ;
   }   
  a == a-1;
}
else if( dovl > 100 and a == 4){
digitalWrite(pinDir, LOW);

  for(int i = 0; i < steps_rotate_360; i++)
  {
  digitalWrite(pinStep, HIGH);   
  delay(100) ;
   }   
  a == a-2;
} 
  else if(  myData.temper < 23 and myData.temper < 25 and a==1){  //60
   digitalWrite(pinDir, HIGH);

  for(int i = 0; i < steps_rotate_360; i++)
  {
  digitalWrite(pinStep, HIGH);   
  delay(500) ;
   }   
  a == a+1;
  }  
  else if(  myData.temper < 25 and myData.temper < 27 and a==2){ // 45 
   digitalWrite(pinDir, HIGH);

  for(int i = 0; i < steps_rotate_360; i++)
  {
  digitalWrite(pinStep, HIGH);   
  delay(500) ;
   }   
  a == a+1;
  }
 else if(  myData.temper < 27 and myData.temper < 30 and a==3){   //90
   digitalWrite(pinDir, HIGH);

  for(int i = 0; i < steps_rotate_360; i++)
  {
  digitalWrite(pinStep, HIGH);   
  delay(500) ;
   }   
  a == a+1;
  }  
 else if(  myData.temper < 30 and myData.temper < 33 and a==4){ //110
   digitalWrite(pinDir, HIGH);

  for(int i = 0; i < steps_rotate_360; i++)
  {
  digitalWrite(pinStep, HIGH);   
  delay(500) ;
   }   
  a == a+1;
  }
    else if(  myData.temper < 27 and myData.temper < 30 and a==4){
   digitalWrite(pinDir, LOW);

  for(int i = 0; i < steps_rotate_360; i++)
  {
  digitalWrite(pinStep, HIGH);   
  delay(500) ;
   }   
  a == a-1;
  }
  else if(  myData.temper < 25 and myData.temper < 27 and a==3){
   digitalWrite(pinDir, LOW);

  for(int i = 0; i < steps_rotate_360; i++)
  {
  digitalWrite(pinStep, HIGH);   
  delay(500) ;
   }   
  a == a-1;
  }
  else if(  myData.temper < 23 and myData.temper < 25 and a==2){
   digitalWrite(pinDir, LOW);

  for(int i = 0; i < steps_rotate_360; i++)
  {
  digitalWrite(pinStep, HIGH);   
  delay(500) ;
   }   
  a == a-1;
  }
  else if(  myData.temper < 23 and myData.temper < 25 and a==2){
   digitalWrite(pinDir, LOW);

  for(int i = 0; i < steps_rotate_360; i++)
  {
  digitalWrite(pinStep, HIGH);   
  delay(500) ;
   }   
  a == a-1;
  }
   else if( myData.temper < 23 and a==1){
   digitalWrite(pinDir, LOW);

  for(int i = 0; i < steps_rotate_360; i++)
  {
  digitalWrite(pinStep, HIGH);   
  delay(500) ;
   }   
  a == a-1;
  }
else {
 digitalWrite(pinStep, LOW);  
 delay(1000) ;
 } 
}

