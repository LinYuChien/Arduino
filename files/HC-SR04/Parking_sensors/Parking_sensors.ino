/*倒車雷達實作 超音波感測超過40cm時550ms為間隔嗶聲，小於40cm時嗶聲會越來越急促*/
//電路實體http://i.imgur.com/tIvOdns.jpg
#include <Ultrasonic.h>

#define TRIGGER_PIN  12
#define ECHO_PIN     13

Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);
const int led = 5;
void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  Serial.print("Welcome to Serial Monitor");
}

void loop()
{
  float cmMsec, inMsec;
  long microsec = ultrasonic.timing();

  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM); // 計算距離&#65292;單位: 公分
//  inMsec = ultrasonic.convert(microsec, Ultrasonic::IN); // 計算距離&#65292;單位: 英吋
//  Serial.print("MS: ");
//  Serial.print(microsec);
  Serial.print("CM: ");
  Serial.print(cmMsec);
//  Serial.print(", IN: ");
//  Serial.println(inMsec);
  delay(200);
  if(cmMsec > 40){
    digitalWrite(led, HIGH);
    delay(550);
    digitalWrite(led, LOW);
    delay(550);
  }
  else{
    int num = 40/cmMsec;
    digitalWrite(led, HIGH);
    delay(550/num);
    digitalWrite(led, LOW);
    delay(550/num);
  }
}

