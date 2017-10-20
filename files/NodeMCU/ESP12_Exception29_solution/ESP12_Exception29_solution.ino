#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

void setup() {
    WiFi.softAPdisconnect(true);
    WiFi.disconnect(true);
    ESP.eraseConfig();
    ESP.reset();
}
void loop() {}
