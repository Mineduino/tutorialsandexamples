/*
 * Tested with ESP8266, HW504 joystick and ADS1115 converter
 * 
 * @author Adam Raźniewski
 * License MIT 
 * 
 */

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_ADS1015.h>

Adafruit_ADS1115 ads(0x48);

#define BUTTON_PIN   2
#define ENTITYTOPIC "MD/fromesp/entity"



const char* ssid = "YourWifiName";
const char* password = "YourWifiPassword";
const char* mqtt_server = "192.168.1.100";

bool shouldReset = false;


WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi();

void setup() {
  Serial.begin(9600);
  while (!Serial);
  setup_wifi();
  ads.begin();
  pinMode(BUTTON_PIN, INPUT);
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
  int16_t z, x;

  int addX = 0;
  int addZ = 0;
  int addY = 0;
  
  addY = digitalRead(BUTTON_PIN); 
  z = ads.readADC_SingleEnded(0);
  x = ads.readADC_SingleEnded(1);
  if(x > 12000) {
    addX = -1;
  } else if(x < 3000){
    addX = 1;
  }
  if(z > 12000) {
    addZ = 1;
  } else if(z < 3000){
    addZ = -1;
  }
  if(addY == 1) {
    addY = 0;
  } else {
    addY = 1;
    shouldReset = true;
  }
  if(addX != 0 || addZ != 0 || addY != 0) {
    char cstr[64];
    sprintf(cstr, "{\"type\": \"move\", \"deltaX\": %d, \"deltaY\": %d, \"deltaZ\": %d}", addX, addY, addZ);
    client.publish(ENTITYTOPIC, cstr);
  } else if(shouldReset && addY == 0) {
    char cstr[64];
    sprintf(cstr, "{\"type\": \"move\", \"deltaX\": %d, \"deltaY\": %d, \"deltaZ\": %d}", addX, addY, addZ);
    client.publish(ENTITYTOPIC, cstr);
    shouldReset = false;    
  }
  
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
 
  delay(200);
}
