Steps

1.移除HC-05模組，燒入以下程式，並打開序列視窗
```ino
/*
最新設定:
AT+UART=115200,0,0  (但是BTSerial.begin(38400); 還是要用38400才能回應AT  怪怪der)
AT+ROLE=0
AT+NAME=CordovaSlave
*/

#include <SoftwareSerial.h>

SoftwareSerial BTSerial(7,8); // RX | TX

void setup()
{
  Serial.begin(9600);
  Serial.println("Please choose Both NL & CR");
  Serial.println("Enter AT commands:");
  BTSerial.begin(38400);  // HC-05 default speed in AT command more
}

void loop()
{

  // Keep reading from HC-05 and send to Arduino Serial Monitor
  if (BTSerial.available())
    Serial.write(BTSerial.read());

  // Keep reading from Arduino Serial Monitor and send to HC-05
  if (Serial.available())
    BTSerial.write(Serial.read());
}
```

2.在按著HC-05上的Reset按鈕的狀態下供5V電，進入AT模式(燈號慢速閃爍每2秒一次)


3.常用指令
 * AT+NAME=輸入名稱      //指定BT名稱
 * AT+ADDR?            //回傳位址
 * AT+UART=115200,0,0  //設定BAUD
 * AT+CMODE=0          //指定連接綁定的位址
 * AT+ROLE=0           //Indicating this device is the slave.
