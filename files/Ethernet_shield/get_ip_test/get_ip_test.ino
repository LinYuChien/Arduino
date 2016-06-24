#include <SPI.h>
#include <Ethernet.h>
byte mac[]={ 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xFD };//指定網路卡 MAC 位址 (隨便設)

EthernetClient client;// 建立乙太網物件 EthernetClient
void setup() {//設定初始值
  Serial.begin(9600);//初始化序列埠
  Serial.println(F( "\nStarting Ethernet..."));
  if (Ethernet.begin(mac)==0) {
    Serial.println("Cannot get IP Address!");   
    for(;;);
    }
  Serial.print("IP Address ");
  Serial.println(Ethernet.localIP());
  }
void loop() { }
