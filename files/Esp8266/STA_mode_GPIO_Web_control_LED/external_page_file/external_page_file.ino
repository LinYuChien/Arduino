// STA模式網頁伺服器控制LED
// 將網頁另外寫在index.h裡

#include <ESP8266WiFi.h>      // 提供Wi-Fi功能的程式庫
#include <ESP8266WebServer.h>  // 提供網站伺服器功能的程式庫
#include <ESP8266mDNS.h>
#include "index.h"

const byte LED_PIN = 2;
const byte PWM_PIN = 0;

const char ssid[] = "SSID";
const char pass[] = "password";

ESP8266WebServer server(80);   // 宣告網站伺服器物件與埠號

// 定義處理首頁請求的自訂函式
void rootRouter() {
  server.send (200, "text/html", PAGE_INDEX );
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);  
  WiFi.begin(ssid, pass);
  

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);   // 等待WiFi連線
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected, IP: ");
  Serial.println(WiFi.localIP());  // 顯示ESP8266裝置的IP位址
  
  if (!MDNS.begin("jarvis")) {
    Serial.println("Error setting up MDNS responder!");
    while(1) { 
      delay(1000);
    }
  }
  Serial.println("mDNS responder started");

  server.on ( "/", rootRouter);
  server.on ( "/index.html", rootRouter);
  server.on ("/sw", []() {
     String state = server.arg("led");
     if (state == "ON") {
         digitalWrite(LED_PIN, HIGH);
     } else if (state == "OFF") {
         digitalWrite(LED_PIN, LOW);
     }
     
     Serial.print("LED_PIN: ");
     Serial.println(state);
  });
  
  server.on ("/pwm", []() {
     String pwm = server.arg("led");
     int val = pwm.toInt();
     analogWrite(PWM_PIN, val);
     Serial.print("PWM: ");
     Serial.println(val);
  });
  
  server.onNotFound([](){   // 處理「找不到指定路徑」的事件
  server.send(404, "text/plain", "File NOT found!");
  });
  
  server.begin();
  Serial.println("HTTP server started.");
  
  MDNS.setInstanceName("Cubie's ESP8266");
  MDNS.addService("http", "tcp", 80);
}

void loop() {
    server.handleClient();  // 處理用戶連線
}
