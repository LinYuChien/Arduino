#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
/*
記得到Database>規則更新為可讀
ESP8266 Firebase API Refrence : http://firebase-arduino.readthedocs.io/en/latest/
*/
const char* firebaseURL PROGMEM = "***.firebaseio.com";
const char* authCode PROGMEM = "***";
const char* ssid PROGMEM = "***";
const char* pwd PROGMEM  = "***";

String chipId = "ESP12E";

class System{
  private:
    int* leds;
    void turnOFF(){ 
        digitalWrite(leds[1], LOW);
        digitalWrite(leds[0], LOW);
    }
    bool getled01();
    bool getled02();
  public:
    System(){
      Serial.begin(9600);
      leds = new int[2];
      leds[0] = D6;
      leds[1] = D7;   
      Serial.println("System OK!");
    }
    void setupWiFi(); //WiFi設置
    void setMode();   //pin mode設置
    void LEDtest();   //燈號測試
    void setupFirebase(); //firebase設置
    void reactLEDs();  //依照get值反應燈號
};



System myS1;

/********************************/
void setup() {
  myS1.setMode();
  myS1.LEDtest();
  myS1.setupWiFi();
  myS1.setupFirebase();
}

/********************************/
void loop() {
  myS1.reactLEDs();
}


void System::setMode(void){
  for(int i = 0; i < 2; i++){
    pinMode(leds[i], OUTPUT);
  }  
}

void System::LEDtest(void){
  for(int i = 0; i < 4; i++){
    digitalWrite(leds[0], HIGH);
    digitalWrite(leds[1], LOW);
    delay(80);
    digitalWrite(leds[1], HIGH);
    digitalWrite(leds[0], LOW);
    delay(80);
  }
  turnOFF();
}

void System::setupWiFi(void){
  WiFi.begin(ssid, pwd);
  Serial.println("WiFi connecting...");
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(200);  
  }
  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.println("SSID : "+(String)ssid);
  Serial.print("IP address : ");
  Serial.println(WiFi.localIP());
}

void System::setupFirebase(void){
  Firebase.begin(firebaseURL, authCode);
  Serial.println("Firebase setup!");
}

bool System::getled01(void){
  String path = chipId + "/status";
  FirebaseObject F_Obj = Firebase.get(path);
  bool St1 = F_Obj.getBool("led01");
//  if(F_Obj.failed()){
//    Serial.print("setting /number failed:");
//    Serial.println(Firebase.error());  
//    //return;
//  }
  Serial.print("Led 1 : ");
  Serial.println(St1);
  return St1;
}

bool System::getled02(void){
  String path = chipId + "/status";
  FirebaseObject F_Obj = Firebase.get(path);
  bool St2 = F_Obj.getBool("led02");
//  if(F_Obj.failed()){
//    Serial.print("setting /number failed:");
//    Serial.println(Firebase.error());  
//    return;
//  }
  Serial.print("Led 2 : ");
  Serial.println(St2);
  return St2;
}

void System::reactLEDs(void){
  digitalWrite(leds[0], getled01());
  digitalWrite(leds[1], getled02());
}
