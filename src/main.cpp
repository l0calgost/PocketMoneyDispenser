#include <Arduino.h>
#include <Servo.h>
#include <ESP8266WiFi.h>
#include <config.h>

const char* ssid     = WLAN_SSID;
const char* password = WLAN_PASSWORD;

Servo servo;

WiFiServer server(80);

// put function declarations here:
void eject();
void connectWifi();

void setup() {
  Serial.begin(115200);

  connectWifi();
  server.begin();

  servo.attach(2);
  servo.write(180);
}

void loop() {
  delay(3000);
  eject();
}


void  eject() {
  Serial.println("ejecting...");
  servo.write(50);
  delay(300);
  servo.write(180);
}

void connectWifi()
{
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}