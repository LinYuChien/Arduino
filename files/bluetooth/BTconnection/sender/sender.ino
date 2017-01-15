/*
 * sketch for sender(master BT)
 * AT+NAME=five1
 * AT+ADDR?   (unnecessary)
 * AT+UART=115200,0,0
 * AT+CMODE=0        指定連接綁定的位址
 * AT+ROLE=1         Indicating this device is the master.
 * AT+BIND=98d3,31,fc2103    the parameter is slave's addr
 */

#include <SoftwareSerial.h>   // 引用程式庫
 
// 定義連接藍牙模組的序列埠
SoftwareSerial BT(11, 10); // RX,TX
char val;  // 儲存接收資料的變數
 
void setup() {
  Serial.begin(9600);   // 與電腦序列埠連線
  Serial.println("BT is ready!");
 
  // 藍牙透傳模式的預設連線速率,should be match the parameter of AT+UART commend
  BT.begin(115200);
}
 
void loop() {
  // 若收到「序列埠監控視窗」的資料，則送到藍牙模組
  if (Serial.available()) {
    val = Serial.read();
    BT.print(val);
  }
 
  // 若收到藍牙模組的資料，則送到「序列埠監控視窗」
  if (BT.available()) {
    val = BT.read();
    Serial.print(val);
  }
}

