#include <Timer.h>

// 用四個計時器控制四個LED 
Timer t2;
Timer t3;
Timer t4;
Timer t5;

int TM1 = 500;
int TM2 = 1000;

void setup() {
  pinMode(2, OUTPUT); // 腳位設定為輸出模式
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  
  t2.oscillate(2, TM1, HIGH); // 以oscillate設定每幾毫秒切換一次狀態
  t3.oscillate(3, TM2, HIGH); // 第一個參數：哪個腳位
  t4.oscillate(4, TM1, HIGH); // 第二個參數：幾毫秒
  t5.oscillate(5, TM2, HIGH); // 第三個參數：初始狀態
}

void loop() {
  // 在loop裡，呼叫每個計時器的update，它才能運作更新狀態 
  t2.update();
  t3.update();
  t4.update();
  t5.update();
}
