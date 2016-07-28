#include <ESP8266WiFi.h>      // 提供Wi-Fi功能的程式庫
#include <ESP8266WebServer.h>  // 提供網站伺服器功能的程式庫

const char ssid[] = "peter";
const char pass[] = "076263697";

ESP8266WebServer server(80);   // 宣告網站伺服器物件與埠號

// 定義處理首頁請求的自訂函式
void rootRouter() {
  server.send(200, "text/html", "Hello from <b>ESP8266</b>! </br> <img src=\"http://i.imgur.com/VxgwHex.png\" alt=\"123\">");
}

void setup() {
  Serial.begin(115200);  
  WiFi.begin(ssid, pass);
  /*
   *  若要指定IP位址，請自行在此加入WiFi.config()敘述。
   WiFi.config(IPAddress(192,168,1,50),    // IP位址
               IPAddress(192,168,1,1),     // 閘道（gateway）位址
               IPAddress(255,255,255,0));  // 網路遮罩（netmask）
   */

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);   // 等待WiFi連線
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected, IP: ");
  Serial.println(WiFi.localIP());  // 顯示ESP8266裝置的IP位址

  server.on("/index.html", rootRouter);  // 處理首頁連結請求的事件
  server.on("/", rootRouter);
  
  server.onNotFound([](){   // 處理「找不到指定路徑」的事件
    server.send(404, "text/plain", "File NOT found!");
  });
  
  server.begin();
  Serial.println("HTTP server started.");
}

void loop() {
    server.handleClient();  // 處理用戶連線
}
