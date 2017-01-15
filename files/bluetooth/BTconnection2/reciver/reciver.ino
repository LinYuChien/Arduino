/*
 * sketch for reciver(slave BT)
 * AT+NAME=five2
 * AT+ADDR?   98d3:31:fc2103
 * AT+UART=115200,0,0
 * AT+CMODE=0        指定連接綁定的位址
 * AT+ROLE=0         Indicating this device is the slave.
 */

#include <SoftwareSerial.h>   // 引用程式庫
//222
// 定義連接藍牙模組的序列埠
SoftwareSerial BT(8, 9); // RX TX
char val;  // 儲存接收資料的變數
const byte LED_PIN = 13;  // 定義LED腳位

void setup() {
  // 設定HC-05藍牙模組，AT命令模式的連線速率。
  BT.begin(115200);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // 若收到藍牙模組的資料，則送到「序列埠監控視窗」
  if (BT.available()) {
    val = BT.read();
    if (val == '1') {
      digitalWrite(LED_PIN, HIGH);
      // 回應命令發送端，告知「已開燈」
      BT.println("LED ON from reciver");
    } else if (val == '0') {
      digitalWrite(LED_PIN, LOW);
      // 回應命令發送端，告知「已關燈」
      BT.println("LED OFF frome reciver");
    }
  }
}
