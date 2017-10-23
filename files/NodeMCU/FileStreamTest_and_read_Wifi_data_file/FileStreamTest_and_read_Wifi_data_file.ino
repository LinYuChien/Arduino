/*
 本範例為《超圖解物聯網IoT實作入門》書籍補充內容。
 相關說明請參閱：
 http://swf.com.tw/?p=911
*/
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <FS.h>

//使用靜態位址
IPAddress ip(192, 168, 0, 120);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);

const byte LED_PIN = 2;
const byte PWM_PIN = 0;

//ssid & 密碼  YChomeWifi("myfile.txt");將會到myfile.txt取出SSID與密碼並WiFi.begin();
char* ssid;
char* pass;
const char* host = "ycwemos";

ESP8266WebServer server(80);

// 定義處理首頁請求的自訂函式
String getContentType(String filename){
  if(server.hasArg("download")) return "application/octet-stream";
  else if(filename.endsWith(".htm")) return "text/html";
  else if(filename.endsWith(".html")) return "text/html";
  else if(filename.endsWith(".css")) return "text/css";
  else if(filename.endsWith(".js")) return "application/javascript";
  else if(filename.endsWith(".png")) return "image/png";
  else if(filename.endsWith(".gif")) return "image/gif";
  else if(filename.endsWith(".jpg")) return "image/jpeg";
  else if(filename.endsWith(".mp3")) return "audio/mpeg";
  else if(filename.endsWith(".ico")) return "image/x-icon";
  else if(filename.endsWith(".xml")) return "text/xml";
  else if(filename.endsWith(".pdf")) return "application/x-pdf";
  else if(filename.endsWith(".zip")) return "application/x-zip";
  else if(filename.endsWith(".gz")) return "application/x-gzip";
  return "text/plain";
}

bool handleFileRead(String path){
  Serial.println("handleFileRead: " + path);
  if(path.endsWith("/")) path += "index.htm";
  String contentType = getContentType(path);
  String pathWithGz = path + ".gz";
  if(SPIFFS.exists(pathWithGz) || SPIFFS.exists(path)){
    if(SPIFFS.exists(pathWithGz))
      path += ".gz";
    File file = SPIFFS.open(path, "r");
    size_t sent = server.streamFile(file, contentType);
    file.close();
    return true;
  }
  return false;
}

void setup( ){
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);

  SPIFFS.begin();  // 啟用SPIFFS檔案系統
  WiFi.config(ip, gateway, subnet);
  //WiFi.begin(ssid, pass);
  YChomeWifi("myfile.txt");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  //IPAddress ip = WiFi.localIP();
  Serial.println("mDNS address: " + (String)host + ".local/");
  if (!MDNS.begin(host, ip)) {
    Serial.println("Error setting up MDNS responder!");
    while(1) { 
      delay(1000);
    }
  }
  Serial.println("mDNS responder started");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

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

  // 處理根路徑以及「不存在的」路徑
  server.onNotFound([](){
    if(!handleFileRead(server.uri()))
      server.send(404, "text/plain", "FileNotFound");
  });

  server.begin();
  Serial.println("HTTP server started");

  MDNS.setInstanceName("yc's ESP8266");
  MDNS.addService("http", "tcp", 80);
}
 
void loop( ){
  server.handleClient();
}

void YChomeWifi(String fname){ //傳入SPIFFS上傳的檔案(路徑)
  File f = SPIFFS.open(fname, "r");
  if (!f) {
    Serial.println("file open failed");
  }
  else{
    while(f.available()) {
      String line = f.readStringUntil('\n'); //讀到換行字元為止 (記得txt檔要換行)
      String mySSID = line.substring(0,10);  //取出index 0~9
      String mypwd  = line.substring(10,20); 
      //Serial.println("YC SSID:" + mySSID);
      //Serial.println("YC PWD :" + mypwd);
      mySSID.toCharArray(ssid, mySSID.length());  //(字元陣列buffer, 字串物件長度)
      mypwd.toCharArray(pass, mypwd.length());
      WiFi.begin(ssid, pass);
    }
  }
}



