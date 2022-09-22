#include <ESP8266WiFi.h>
const char *wifissid = "slpg5";
const char *wifipass = "98@5";
void setup() 
 {
   // put your setup code here, to run once:
   Serial.begin(115200);
 }
void loop() 
 {
   // put your main code here, to run repeatedly:
    delay(1000);
    reconnectWiFi();    
 }
 void reconnectWiFi()
 {
   WiFi.mode(WIFI_STA);
   delay(200);
   WiFi.begin(wifissid,wifipass);
   while(WiFi.status()!= WL_CONNECTED)
   {
     Serial.print(".");
     delay(500);
   }
 Serial.println("Connected to: \t");
 Serial.println(WiFi.localIP());
 }





 
