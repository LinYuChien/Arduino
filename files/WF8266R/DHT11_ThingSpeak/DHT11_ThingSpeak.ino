#include <SoftwareSerial.h>
#include "DHT.h"
#include <Timer.h>
#define DHTPIN 2 
#define DHTTYPE DHT11
SoftwareSerial mySerial(7, 8); // RX, TX
DHT dht(DHTPIN, DHTTYPE);
Timer upload;   //使用Timer函式庫之every(毫秒,呼叫函式) ，每6秒上傳一次溫濕度，這樣做可空出loop()

void uploadToThingSpeak(){
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
    sendValueToThingSpeak(h,t);
}

void sendValueToThingSpeak(float Hum,float Tem)
{
  mySerial.print("IoT+{1:" + String(Hum) + "},{2:" + String(Tem) + "}");
  Serial.print("Sent Humidity:");
  Serial.print(Hum);
  Serial.println("% to thingspeak.com");
  Serial.print("Sent Temperature:");
  Serial.print(Tem);
  Serial.println("*C to thingspeak.com");
  Serial.println("----------------------");
}

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  dht.begin();
  upload.every(6000, uploadToThingSpeak); // 每經過6000毫秒，就會呼叫uploadToThingSpeak
}

void loop() {
  upload.update();
}


