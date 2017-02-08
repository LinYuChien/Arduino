#include <SoftwareSerial.h>

SoftwareSerial ESP(8,7); //Rx Tx

void setup(){
  Serial.begin(9600);
  ESP.begin(9600);
  Serial.println("Serial Ready");
}

void loop(){
  if(Serial.available()){
    ESP.print(Serial.read());
  }
  
  if (ESP.available())
  {
    Serial.println(ESP.read());
  }

}
