#include <SoftwareSerial.h>   // 引用程式庫
SoftwareSerial ESP(7, 8); // 接收腳, 傳送腳

void setup() {
  Serial.begin(9600);  // 與電腦序列埠連線，也能改成115200
  ESP.begin(9600);   // 與ESP-01模組連線或採用115200
  Serial.println("Serial is ready!");
  Serial.println("");
  // sendData("AT+RST\r\n",2000,DEBUG); // reset ESP8266
  // sendData("AT+GMR\r\n",1000,DEBUG);
}
 
void loop() {
  // 若收到「序列埠監控視窗」的資料，則送到ESP-01模組。
  if (Serial.available()) {
    ESP.print((char)Serial.read());
  }
 
  // 若收到ESP-01模組的資料，則送到「序列埠監控視窗」。
  if (ESP.available()) {
    Serial.print((char)ESP.read());
  }
}

/*
 * AT+GMR 查詢版本號
 * AT+CWMODE=1 : 修改工作模式為 1:STA  2:AP  3:AP+STA(BOTH)
 * AT+CIOBAUD? : 查詢鮑率 (位元速率)  
 * AT+CIFSR : 查詢 IP 位址
 * AT+CWLAP : 列出附近偵測得到的基地台
 * AT+CWJAP="SSID","PWD" : 連線指定之基地台 (Join AP)
 * AT+CWJAP? : 查詢目前連線到哪一個基地台
 * AT+CIFSR : 查詢 IP 位址
 * 
 * AT+CIPSTART : 建立 TCP/UDP 連線 AT+CIPSTART="TCP","www.google.com",80
 * AT+CIPSTATUS : 查詢目前 IP 連線狀態
 * AT+CIPCLOSE : 關閉 IP 連線
 * 
 * AT+CWSAP? : 查詢 SoftAP 的設定
 * AT+CWSAP="ssid","pwd",ch,ecn : 更改 AP 的設定 (只在 AP/BOTH 模式有效)
 * AT+CWLIF : 查詢有哪些 Client 連線至此 AP (只在 AP/BOTH 模式有效)
 * AT+CIPMUX? : 詢問目前 TCP/UDP 連線模式
 * AT+CIPMUX=1 : 設定 TCP/UDP 連線模式為多重連線 如果要取消 ESP8266 的伺服功能, 恢復單一連線功能, 須將 CIPMUX 設為 0 
 * AT+CIPSERVER=mode[,port] : 設定是否開啟 ESP8266 為伺服器 AT+CIPSERVER=1,8087
 * AT+CIPSTO? : 查詢伺服器逾時計時器設定值 (秒)
 * AT+CIPSTO=timeout : 設定伺服器逾時計時器 (0~7200 秒)
 */
