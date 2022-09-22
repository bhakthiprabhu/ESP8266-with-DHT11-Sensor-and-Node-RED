#include <ESP8266WiFi.h>
#include <DHT.h>
#define dht_apin 2 // Pin sensor is connected to
DHT dht(dht_apin,DHT11);
const char *wifissid = "slpg5";
const char *wifipass = "9848038171@5";
void setup() 
 {
   // put your setup code here, to run once:
   Serial.begin(115200);
   dht.begin();
 }
void loop() 
 {
   // put your main code here, to run repeatedly:
    delay(1000);
    reconnectWiFi();
    Serial.print("Current humidity = ");
    Serial.print(dht.readHumidity());
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(dht.readTemperature()); 
    Serial.println("C  ");
    
    delay(5000);//Wait 5 seconds before accessing sensor again.
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
 Serial.print("Connected to: ");
 Serial.println(WiFi.localIP());
 }
