#include <SoftwareSerial.h>   // 引用程式庫

SoftwareSerial BT(8, 9); // RX TX
String comdata = " ";


void setup() {
  BT.begin(115200);
  Serial.begin(9600);
  Serial.println("BT is ready!");
}

void loop() {
  if (BT.available()) {
    //delay(100);
    char BT_Buffer = BT.read();
    if(BT_Buffer != '\n'){
      comdata = comdata + BT_Buffer;
    }
    else{
      Serial.println(comdata);
      comdata = "";  
    }
  }
}

