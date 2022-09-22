#include <ESP8266WiFi.h>
#include <MQTT.h>
#include "DHT.h"

WiFiClient net;
MQTTClient client;
#define DHTTYPE DHT11   // DHT 11

const int DHTPin = 2;   //D1

// Initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE);
String ssid="OnePlus_Hotspot";
String pass="12345678";
unsigned long lastMillis = 0;

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!client.connect("nodemcu_client")) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nconnected!");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  dht.begin();
  client.begin("192.168.0.104", net); //hostname -I
  client.onMessage(messageReceived);
  connect();
  if (client.connected()) {
    client.subscribe("nodemcu/dht");
  }
}

void loop() {
  client.loop();
  delay(1000);  // <- fixes some issues with WiFi stability
  if (!client.connected()) {
    connect();
  }

  // publish a message roughly every 5 second.
  if (millis() - lastMillis > 5000) {
    lastMillis = millis();
    float h = dht.readHumidity();
    float temp = dht.readTemperature();
    if (isnan(h) || isnan(temp)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
    Serial.println(temp);
    client.publish("nodemcu/dht",String(temp));
  }
}
