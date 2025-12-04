#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "你的wifi名";
const char* password = "你的wifi密码";

const char* mqtt_server = "你的电脑IP";

WiFiClient espClient;
PubSubClient client(espClient);

int led = 2;
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

  setupWifi();

  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  ledState = !ledState;
  digitalWrite(led, ledState);

  client.publish("esp32/data", ledState ? "1" : "0");

  delay(1000);
}