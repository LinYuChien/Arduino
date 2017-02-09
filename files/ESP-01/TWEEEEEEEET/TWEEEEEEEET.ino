/*
 * Sending Tweets Automatically Every Minutes by ThingSpeak 
 * 每分鐘由Twitter自動發溫溼度資料
 * Get your API Key https://thingspeak.com/apps/thingtweets
 * 使用:UNO、ESP01、DHT22
 * URL編碼:http://www.ifreesite.com/urldecoderencoder.htm
 * dht22 wiring arduino http://i.imgur.com/LdHLuX1.png
 */

#include <SoftwareSerial.h>
#include "DHT.h"
#define DEBUG true

SoftwareSerial esp8266(7,8); //(RX,TX)
DHT dht(4, DHT22);

float h,t;
//指定AP
String ssid="SSID";
String pwd="pwd";                          /*XXXXX*/
String ThingTweet_API="API";               /*XXXXX*/


void setup() {
  Serial.begin(9600);
  esp8266.begin(9600);
  dht.begin();
  
  sendData("AT+RST\r\n",2000,DEBUG); // reset ESP8266
  while (!connectWifi(ssid, pwd)) {
    Serial.println("Connecting WiFi ... failed");
    delay(2000);
  }
  sendData("AT+GMR\r\n",1000,DEBUG);
  delay(3000); //wait for wifi connection to get local ip
  sendData("AT+CIFSR\r\n",1000,DEBUG); //get ip address
}

void loop() {
  //getting DHT22 data
  float h=dht.readHumidity();     
  float t=dht.readTemperature(); 
  //Twitter by ThingSpeak 
  Serial.println(F("Connecting Thingspeak ..."));
  sendData("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n",1000,DEBUG);
  String data="GET /apps/thingtweet/1/statuses/update?api_key=" + ThingTweet_API +"&status=";
  data += "%E3%80%90YC%20IoT%E3%80%91%0A%E6%BF%95%E5%BA%A6%3A";
  data += (String)h+"%25";
  data += "%0A%E6%BA%AB%E5%BA%A6%3A" + (String)t + "%C2%B0C";
  data += "\r\n";
  sendData("AT+CIPSEND=" + (String)data.length() + "\r\n",1000,DEBUG); 
  String res=sendData(data,3000,DEBUG);  
  res.replace("\r\n",""); //remove all line terminator   
  if (res.indexOf("Unlink") == -1) { //if no auto unlink
    sendData("AT+CIPCLOSE\r\n",2000,DEBUG); //close session
  }

  delay(60000);
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

boolean connectWifi(String ssid, String pwd) {
  String res=sendData("AT+CWJAP=\"" + ssid + "\",\"" + pwd + "\"\r\n",8000,DEBUG); 
  res.replace("\r\n",""); //remove all line terminator
  if (res.indexOf("OK") != -1) {return true;}
  else {return false;}  
}
