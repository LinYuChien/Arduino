#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "ssid";
const char* password = "pwd";

String msgStr;
int temp;


ESP8266WebServer server(80);


void setup(void){
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print(F("Connected to "));
  Serial.println(ssid);
  Serial.print(F("IP address: "));
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
  });

  server.on("/temp", [](){
    String a="";
    a+="<!DOCTYPE html><html><head><title>Page Title</title><meta http-equiv=\"refresh\" content=\"3\" /></head><body>";
    a+="<h1>"+msgStr+ "</h1>";
    a+="</body></html>";
    server.send(200, "text/html", a);
    //msgStr="";
  });

  server.on("/temp.json", [](){
    String a="";
    a+="{\"temp\":" + (String)(19 + random(10)) + ",\"humid\":" + (String)20 + "}";
    server.send(200, "application/json", a);
    a="";
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println(F("HTTP server started"));
}

void loop(void){
  server.handleClient();
  //msgStr ="{\"temp\":" + (String)(19 + random(10)) + ",\"humid\":" + (String)20 + "}";
  while(Serial.available()){
    char c = Serial.read();
    msgStr += c;
    delay(2);  
  }
//  if (msgStr.length() >0) {
//    Serial.println(msgStr);  //so you can see the captured String 
//    msgStr="";
//  } 

}

void handleRoot() {
  server.send(200, "text/plain", "hello from esp8266!");
}

void handleNotFound(){
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

