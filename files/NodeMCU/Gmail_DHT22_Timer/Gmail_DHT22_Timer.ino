//Ref:http://www.instructables.com/id/ESP8266-GMail-Sender/step2/Edit-sketch/#intro
//程式說明:由Gmail每10分鐘發送一封溫濕度mail至指定信箱
#include <ESP8266WiFi.h>
#include "Gsender.h"
#include <Timer.h>
#include "DHT.h"
#define DHTPIN 2   //gpio2
#define DHTTYPE DHT22  

#pragma region Globals
const char* ssid = "*********";                           // WIFI network name
const char* password = "*********";                       // WIFI network password
uint8_t connection_state = 0;                    // Connected to WIFI or not
uint16_t reconnect_interval = 10000;             // If not connected wait time to try again
#pragma endregion Globals
DHT dht(DHTPIN, DHTTYPE);
Timer t1;

uint8_t WiFiConnect(const char* nSSID = nullptr, const char* nPassword = nullptr)
{
    static uint16_t attempt = 0;
    Serial.print("Connecting to ");
    if(nSSID) {
        WiFi.begin(nSSID, nPassword);  
        Serial.println(nSSID);
    } else {
        WiFi.begin(ssid, password);
        Serial.println(ssid);
    }

    uint8_t i = 0;
    while(WiFi.status()!= WL_CONNECTED && i++ < 50)
    {
        delay(200);
        Serial.print(".");
    }
    ++attempt;
    Serial.println("");
    if(i == 51) {
        Serial.print("Connection: TIMEOUT on attempt: ");
        Serial.println(attempt);
        if(attempt % 2 == 0)
            Serial.println("Check if access point available or SSID and Password\r\n");
        return false;
    }
    Serial.println("Connection: ESTABLISHED");
    Serial.print("Got IP address: ");
    Serial.println(WiFi.localIP());
    return true;
}

void Awaits()
{
    uint32_t ts = millis();
    while(!connection_state)
    {
        delay(50);
        if(millis() > (ts + reconnect_interval) && !connection_state){
            connection_state = WiFiConnect();
            ts = millis();
        }
    }
}

void test_send(){              //開機時發送一封測試信件
    float h = dht.readHumidity();  
    float t = dht.readTemperature();
    Gsender *gsender = Gsender::Instance();    // Getting pointer to class instance
    String subject = "測試標題";
    String receive_email = "接收信箱";
    String content = "測試內容";
    if(gsender->Subject(subject)->Send(receive_email, content)) {
        Serial.println("Message send.");
        //可改成LED閃爍告知信件寄發完成
    } else {
        Serial.print("Error sending message: ");
        Serial.println(gsender->getError());
        //可改成LED閃爍告知信件寄發失敗
    }  
}

void sending(){
    float h = dht.readHumidity();  
    float t = dht.readTemperature();
    Gsender *gsender = Gsender::Instance();    // Getting pointer to class instance
    String subject = "溫溼度報告";
    String receive_email = "接收信箱";
    String content = "";
    content += "目前環境資料: ";
    content += "  温度";
    content += String(t);
    content += "  濕度";
    content += String(h);
    
    if(gsender->Subject(subject)->Send(receive_email, content)) {
        Serial.println("Message send.");
        //可改成LED閃爍告知完成信件寄發
    } else {
        Serial.print("Error sending message: ");
        Serial.println(gsender->getError());
        //可改成LED閃爍告知信件寄發失敗
    }  
}

void setup()
{
    Serial.begin(115200);
    Serial.println("DHTxx test!");

    dht.begin();
    
    connection_state = WiFiConnect();
    if(!connection_state)  // if not connected to WIFI
        Awaits();          // constantly trying to connect
        
    test_send();           //寄發開機測試信件
    t1.every(600000 ,sending);  //600000ms = 10min

}

void loop(){

   t1.update();
   
   float h = dht.readHumidity();  
   float t = dht.readTemperature();
   if (isnan(h) || isnan(t) ) {
    //監聽並警告未接收溫溼度資料
    return;
   }

}
