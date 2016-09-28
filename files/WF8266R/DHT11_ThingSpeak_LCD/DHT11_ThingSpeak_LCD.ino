#include <SoftwareSerial.h>
#include "DHT.h"
#include <Timer.h>
//for LCD
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2 
#define DHTTYPE DHT11
SoftwareSerial mySerial(7, 8); // RX, TX
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
Timer upload;   //使用Timer函式庫之every(毫秒,呼叫函式) ，每6秒上傳一次溫濕度，這樣做可空出loop()
Timer instant_data;

void uploadToThingSpeak(){
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
    sendValueToThingSpeak(h,t);
}

void LCD_print_data(){
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  lcd.setCursor(0,0); 
  lcd.print("It's Working!!      ");
  delay(50);
  
  lcd.setCursor(0,1);
  lcd.print("Instant data      ");
  delay(50);  
  
  lcd.setCursor(0,2);
  lcd.print("Humidity:");
  lcd.print(h);
  lcd.print("%     ");
  delay(50);
  
  lcd.setCursor(0,3);
  lcd.print("Temperature:");
  lcd.print(t);
  lcd.print("*C ");
  delay(5500);
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
  /*--------------LCD-------------*/
  lcd.begin(20,4);         // initialize the lcd for 20 chars 4 lines and turn on backlight

  for(int i = 0; i< 2; i++) //背光閃爍三次
  {
    lcd.backlight();
    delay(150);
    lcd.noBacklight();
    delay(150);
  }
  lcd.backlight();
  /*------------------------------*/
  upload.every(6000, uploadToThingSpeak); // 每經過6000毫秒，就會呼叫uploadToThingSpeak
  instant_data.every(25000, LCD_print_data);
}

void loop() {
  upload.update();
  instant_data.update();
  
  lcd.setCursor(0,0); 
  lcd.print("IoT Project By Y.C.");
  delay(100);
  
  lcd.setCursor(0,1);
  lcd.print("  Hygrothermograph  ");
  delay(100);  
  
  lcd.setCursor(0,2);
  lcd.print("Link to Public Data:");
  delay(100);
  
  lcd.setCursor(0,3);
  lcd.print("   ppt.cc/bnPdu     ");
  delay(100);
}


