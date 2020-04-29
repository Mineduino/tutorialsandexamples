/*
 * Tested with DHT-11
 * 
 * @author Adam Raźniewski
 * License MIT 
 * 
 */
#include "DHT.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define TOPIC "MD/tempsign/sign"
#define DHTPIN 2
#define DHTTYPE DHT11


const char* ssid = "YourWifi";
const char* password = "YourPassword";
const char* mqtt_server = "192.168.1.100";

DHT dht(DHTPIN, DHTTYPE);


WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi();

void setup() {
  Serial.begin(9600);
  while (!Serial);
  pinMode(DHTPIN, INPUT_PULLUP);
  setup_wifi();
  dht.begin();

  client.setServer(mqtt_server, 1883);
}

void setup_wifi() {

  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}



void reconnect() {
  while (!client.connected()) {
    Serial.print("MQTT CONNECTING...");
    String clientId = "ESP8266MINED-";
    clientId = clientId + String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("Connected to the broker!");
    } else {
      Serial.println("Problem with connection, will try again in 5 seconds");
      delay(5000);
    }
  }
}


void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  char temp[64];
  sprintf(temp, "[\"&aTemperature\", \"&a%.2f°C\", \"&aHumidity\", \"&a%.2f%\"]", t, h);
  client.publish(TOPIC, temp);
 
  
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
 
  delay(100);
}
