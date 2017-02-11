/*
 * Ref:http://swf.com.tw/?p=946
 * 採用Paul Stoffregen撰寫的Captivative Sensor程式庫
 * 電阻:1MΩ
 * http://i.imgur.com/Q84DsCA.jpg
 */



#include <CapacitiveSensor.h>

#define threshold 200   // 感測電容量的臨界值
#define LED  13         // LED1的腳位


// 設定電容觸控的訊號輸入和輸出腳位 Pin4到5 一定要先R再C
CapacitiveSensor   cs_4_5 = CapacitiveSensor(4,5);


void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
 
}

void loop() {
    long total1 =  cs_4_5.capacitiveSensor(30);

    Serial.println(total1);
    // 若第一個觸控點的電容量大於臨界值，則點亮LED。
    if (total1 > threshold) {
      digitalWrite(LED, HIGH);
    } else {
      digitalWrite(LED, LOW);
    }

}
