// 使用Webduino程式庫建立微網站
// 詳細的程式說明，請參閱第十六章，16-2頁。
//bug:Serail print的IP錯誤  但是可以連線
//錯誤已解決
#include "SPI.h"
#include "Ethernet.h"
#include "WebServer.h"

static byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xFD };
//IPAddress ip(192, 168, 0,102);
//IPAddress subnet(255, 255, 255, 0);
//IPAddress gateway(192, 168, 1, 1);

WebServer webserver("", 80);

P(homePage) = 
    "<!doctype html>"
    "<html><head><meta charset=\"UTF-8\" />"
    "<title>Arduino XDD</title>"
    "</head><body>"
    "This is index test"
    "</body></html>";

void defaultCmd(WebServer &server, WebServer::ConnectionType type, char *, bool)
{
  server.httpSuccess();
  
  if (type != WebServer::HEAD) 
  {
    server.printP(homePage);
  }
}

void setup() {  
  Serial.begin(9600);
  Ethernet.begin(mac);               //初始化動態IP乙太網路連線
  IPAddress ip = Ethernet.localIP(); //取得分配到的IP位址  跟上一行次序不可顛倒，否則無法print出正確IP
  webserver.setDefaultCommand(&defaultCmd);   // 處理「首頁」請求
  webserver.begin();
  Serial.println(F( "\nStarting Ethernet..."));
  Serial.print("My IP address:");
  Serial.print(ip);
  
}

void loop() {
  webserver.processConnection();
}
