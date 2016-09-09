//網頁顯示DHT11溫溼度資料

#include "SPI.h"
#include "Ethernet.h"
#include "WebServer.h"
#include "Streaming.h"   // 引用處理字串的程式庫（參閱下文說明）
#include "dht11.h"

dht11 DHT11;            // 宣告 DHT11 程式物件
const byte dataPin = 2; // 宣告 DHT11 模組的資料輸入腳位

static byte mac[] = { 0xF0, 0x7B, 0xCB, 0x4B, 0x7C, 0x9F };
//IPAddress ip(192, 168, 1, 100);
//IPAddress subnet(255, 255, 255, 0);
//IPAddress gateway(192, 168, 1, 1);

WebServer webserver("", 80);

P(htmlHead) =
 "<!doctype html><html>"
 "<head><meta charset=\"utf-8\">"
 "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" /></head>"
 "<link rel=\"stylesheet\" href=\"https://goo.gl/AUevhM\">"
 "<style>body {background-image:url(\"http://i.imgur.com/n0oAAht.jpg\");background-size:cover;}.segment{background:rgba(234,235,236,0.31);text-align:center;}</style>"
 "<title>Arduino 溫濕度計</title>"
 "</head><body><br><br><br>" ;
 
P(htmlFoot) = "</body></html>";

void defaultCmd(WebServer &server, WebServer::ConnectionType type, char *, bool)
{
  int chk = DHT11.read(dataPin);

  server.httpSuccess();

  if (type != WebServer::HEAD){
    server.printP(htmlHead);

    if (chk == 0) {
      server << "<div class=\"ui two column centered grid\"><div class=\"column\"><div class=\"segment\">";
      server << "<h1>溫濕度計</h1>";
      server << "</div></div><div class=\"four column centered row\"><div class=\"segment\"><div class=\"column\">";
      server << "<p>溫度：" << DHT11.temperature << "&deg;C</p>";
      server << "</div><div class=\"column\">";
      server << "<p>濕度：" << DHT11.humidity << "%</p>";
      server << "</div></div></div></div>";
    } else {
      server << "<h1>無法讀取溫濕度值</h1>";
    }
    server.printP(htmlFoot);
  }
}

void setup() {  
  Serial.begin(9600);
  Ethernet.begin(mac  );
  IPAddress ip = Ethernet.localIP(); 
  webserver.setDefaultCommand(&defaultCmd);   // 處理「首頁」請求
  webserver.begin();
  Serial.println(F( "\nStarting Ethernet..."));
  Serial.print("My IP address:");
  Serial.print(ip);
}

void loop() {
  webserver.processConnection();
}
