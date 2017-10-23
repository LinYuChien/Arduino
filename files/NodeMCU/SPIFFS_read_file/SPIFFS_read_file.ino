/*
ref: http://esp8266.github.io/Arduino/versions/2.0.0/doc/filesystem.html
     https://swf.com.tw/?p=905
     ESP8266的SPIFFS檔案系統讀取檔案
*/
#include <FS.h>

void setup() {
  Serial.begin(115200);
  SPIFFS.begin();
}

void loop() {
  File myFile = SPIFFS.open("/data.txt", "r"); //唯讀模式取得data.txt內容
  if(!myFile) {
    Serial.println("檔案讀取失敗");
  }
  else {
    while(myFile.available()) { //讀到檔案結束
      String str1 = myFile.readStringUntil('\n'); //回傳檔案內容(字串)，直到換行字元為止
      Serial.println(str1);
    }
  }
  delay(1000);
}
