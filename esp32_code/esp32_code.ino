#include <WiFi.h>
#include <PubSubClient.h>
#define led 15
const char* ssid = "清寒不喜争抢";
const char* password = "sg8917301";

const char* mqtt_server = "172.17.180.60";

WiFiClient espClient;
PubSubClient client(espClient);

// int led = 15;
bool ledState = false;

void setupWifi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("ESP32Client")) {
      client.subscribe("esp32/led_control");
    } else {
      delay(2000);
    }
  }
}

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(115200);
  digitalWrite(led,HIGH);
  setupWifi();

  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  // ledState = !ledState;
  // digitalWrite(led, ledState);

  client.publish("esp32/data", "1");

  delay(1000);
}