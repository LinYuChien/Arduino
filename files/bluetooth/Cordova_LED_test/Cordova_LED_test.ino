#include <SoftwareSerial.h>   // 引用程式庫

// 定義連接藍牙模組的序列埠
SoftwareSerial BT(8, 9); // (Rx, Tx)
char val;  // 儲存接收資料的變數
const byte LED_PIN = 13;

void setup() {
  Serial.begin(9600);   // 與電腦序列埠連線
  Serial.println("BT is ready!");
  pinMode(LED_PIN, OUTPUT);
  // 設定藍牙模組的連線速率
  BT.begin(9600);
}

void loop() {
  // 若收到藍牙模組的資料，則送到「序列埠監控視窗」
  if (BT.available()) {
    val = BT.read();
    Serial.println(val);
    
    if (val == '1') {
      digitalWrite(LED_PIN, HIGH);
    } else if (val == '0') {
      digitalWrite(LED_PIN, LOW);
    }
  }
}
