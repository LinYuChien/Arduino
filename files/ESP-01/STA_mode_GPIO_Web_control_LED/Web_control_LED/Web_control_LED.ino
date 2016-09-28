#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

MDNSResponder mdns;

// Replace with your network credentials
const char* ssid = "*******";
const char* password = "*******";

ESP8266WebServer server(80);

String webPage = "";

int gpio0_pin = 0;
int gpio2_pin = 2;

void setup(void){
  webPage += "<!DOCTYPE html><html><head><meta charset=\"utf-8\"><title>STA模式網頁控制</title>";
  webPage += "<link rel=\"stylesheet\" type=\"text/css\" href=\"https://goo.gl/6gNKaN\">";
  webPage += "</head><body><br><div class=\"ui buttons\">";
  webPage += "<a href=\"L1_OFF\"><button class=\"ui button\">關</button></a>";
  webPage += "<div class=\"or\" data-text=\"or\"></div>";
  webPage += "<a href=\"L1_ON\"><button class=\"ui positive button\">開</button></a>";
  webPage += "</div>";
  webPage += "<br><br><div class=\"ui buttons\"><a href=\"L2_OFF\"><button class=\"ui button\">關</button></a>";
  webPage += "<div class=\"or\" data-text=\"or\"></div>";
  webPage += "<a href=\"L2_ON\"><button class=\"ui positive button\">開</button></a>";
  webPage += "</div></body></html>";
  
  
  // preparing GPIOs
  pinMode(gpio0_pin, OUTPUT);
  digitalWrite(gpio0_pin, LOW);
  pinMode(gpio2_pin, OUTPUT);
  digitalWrite(gpio2_pin, LOW);
  
  delay(1000);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }
  
  server.on("/", [](){
    server.send(200, "text/html", webPage);
  });
  server.on("/L1_ON", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(gpio0_pin, HIGH);
    delay(1000);
  });
  server.on("/L1_OFF", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(gpio0_pin, LOW);
    delay(1000); 
  });
  server.on("/L2_ON", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(gpio2_pin, HIGH);
    delay(1000);
  });
  server.on("/L2_OFF", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(gpio2_pin, LOW);
    delay(1000); 
  });
  server.begin();
  Serial.println("HTTP server started");
}
 
void loop(void){
  server.handleClient();
} 
