#include <SoftwareSerial.h>
#define DEBUG true

SoftwareSerial esp8266(7,8); //(RX,TX)
String ThingTweet_API="API";
int i=0; //counter

void setup() {
  Serial.begin(9600);
  esp8266.begin(9600);
  sendData("AT+RST\r\n",2000,DEBUG); // reset ESP8266
  sendData("AT+GMR\r\n",1000,DEBUG);
  delay(3000); //wait for wifi connection to get local ip
  sendData("AT+CIFSR\r\n",1000,DEBUG); //get ip address
}

void loop() {
  Serial.println("Connecting Thingspeak ...");
  sendData("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n",1000,DEBUG);
  String data="GET /apps/thingtweet/1/statuses/update?api_key=" + ThingTweet_API + 
              "&status=Hello! " + i + " times.\r\n";
  sendData("AT+CIPSEND=" + (String)data.length() + "\r\n",1000,DEBUG); 
  String res=sendData(data,3000,DEBUG);  
  res.replace("\r\n",""); //remove all line terminator   
  if (res.indexOf("Unlink") == -1) { //if no auto unlink
    sendData("AT+CIPCLOSE\r\n",2000,DEBUG); //close session
  }
  delay(60000);
  i++;
  }

String sendData(String command, const int timeout, boolean debug) {
  String res="";
  esp8266.print(command);
  long int time=millis();
  while ((time + timeout) > millis()) {
    while(esp8266.available()) {res.concat((char)esp8266.read());}
  }
  if (debug) {
    Serial.print(res);
  }
  return res;
}
