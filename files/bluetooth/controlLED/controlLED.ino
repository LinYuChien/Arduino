#include <SoftwareSerial.h>
#include <Wire.h>


int LED = 13;
SoftwareSerial I2CBT(10,11);  //定義PIN10及PIN11分別為RX及TX腳位             

void setup() {
  Serial.begin(9600);
  I2CBT.begin(9600);//bluetooth baud rate  
  //(注意！此鮑率每個藍牙晶片不一定相同，請先確認完再填寫進去) 
  
  pinMode(LED, OUTPUT);    
}

///////////////////main///////////////////////////

void loop() {

  byte cmmd[20];
  int insize;
  
  while(1){
/*
read message from bluetooth
*/
    if ((insize=(I2CBT.available()))>0){               //判斷有沒有訊息接收 
       Serial.print("input size = ");                   //顯示接收多少訊息 
       Serial.println(insize);
       for (int i=0; i<insize; i++){
         Serial.print(cmmd[i]=char(I2CBT.read()));      //將接收的訊息顯示出來
         Serial.print("\n"); 
       }
      
    }  
      switch (cmmd[0]) {                 //讀取第一個字
        case 97: //"a"                   //97為"a"的ASCII CODE
          digitalWrite(LED,HIGH);        //點亮LED
          break;  
        case 98://"b"                    //98為"b"的ASCII CODE
          digitalWrite(LED,LOW);
          break;
      } //Switch
   
  } //while

}
