/*
 * sketch for sender(master BT)
 * AT+NAME=five1
 * AT+ADDR?   (unnecessary)
 * AT+UART=115200,0,0
 * AT+CMODE=0        指定連接綁定的位址
 * AT+ROLE=1         Indicating this device is the master.
 * AT+BIND=98d3,31,fc2103    the parameter is slave's addr
 */

/*
 * sketch for reciver(slave BT)
 * AT+NAME=five2
 * AT+ADDR?   98d3:31:fc2103
 * AT+UART=115200,0,0
 * AT+CMODE=0        指定連接綁定的位址
 * AT+ROLE=0         Indicating this device is the slave.
 */


#include <SoftwareSerial.h>
SoftwareSerial BT(11, 10);   // RX & TX
 
void setup()
{
  BT.begin(38400);
  Serial.begin(9600);
  Serial.println("Enter commands:");
}
 
void loop()
{
  if (BT.available())
  {
    char data = BT.read();
    Serial.print(data);
  }
  if (Serial.available())
    BT.write(Serial.read());
}

