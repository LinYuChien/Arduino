#define xPin      A1
#define yPin      A0
#define buttonPin 2

int xPosition   = 0;
int yPosition   = 0;
int buttonState = 0;


#include <SoftwareSerial.h>   // 引用程式庫
 
// 定義連接藍牙模組的序列埠
SoftwareSerial BT(11, 10); // RX,TX
char val;  // 儲存接收資料的變數
 
void setup() {
  Serial.begin(9600);   // 與電腦序列埠連線
  Serial.println("BT is ready!");
  BT.begin(115200);
  
  Init_ReadPin();
}
 
void loop() {

  xPosition = analogRead(xPin);
  yPosition = analogRead(yPin);
  buttonState = digitalRead(buttonPin);

  Serial.print("X: ");
  Serial.print(xPosition);
  Serial.print(" | Y: ");
  Serial.print(yPosition);
  Serial.print(" | Button: ");
  Serial.println(buttonState);

  BT.print("X: ");
  BT.print(xPosition);
  BT.print(" | Y: ");
  BT.print(yPosition);
  BT.print(" | Button: ");
  BT.println(buttonState);

  delay(500); // add some delay between reads

}

void Init_ReadPin(void){
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP); 
}



