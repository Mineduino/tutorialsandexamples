/*
 * Tested with Iduino SE019
 * 
 * @author Adam Raźniewski
 * License MIT 
 * 
 */

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define TOPIC "MD/clap/raw"
#define DIGITALPIN 2


const char* ssid = "YourWifi";
const char* password = "YourWifiPassword";
const char* mqtt_server = "192.168.1.100";

bool shouldReset = false;
unsigned long lastSended = 0;


WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi();
void reactToInterrupt();

void setup() {
  Serial.begin(9600);
  while (!Serial);
  pinMode(DIGITALPIN, INPUT);
  setup_wifi();

  attachInterrupt(digitalPinToInterrupt(2), reactToInterrupt, CHANGE);
  
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

ICACHE_RAM_ATTR void reactToInterrupt() {
  if(millis() - lastSended > 100) {
    lastSended = millis();
    shouldReset = true;
    client.publish(TOPIC, new byte[1]{15}, 1);   
  }
  
}

void loop() {
  if((lastSended - millis() > 200) && shouldReset) {
    shouldReset = false;      
    client.publish(TOPIC, new byte[1]{0}, 1);  
  }
  
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
 
  delay(100);
}
