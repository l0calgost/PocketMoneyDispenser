#include <Arduino.h>
#include <Servo.h>
#include <ESP8266WebServer.h>
#include <config.h>

const char* ssid     = WLAN_SSID;
const char* password = WLAN_PASSWORD;

Servo servo;

ESP8266WebServer server(80);

// put function declarations here:
void eject();
void connectWifi();
void handleRoot();

void setup() {
  Serial.begin(115200);

  connectWifi();

  servo.attach(2);
  servo.write(180);

  server.begin();
  server.on("/",handleRoot);
  server.on("/eject", eject);
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  String message="<h1>Spend some money!!</h1>";
  message += "<br/><br/>";
  message += "<a href=\"/eject\">Bling Bling</a>";
  server.send(200, "text/html", message);
}

void  eject() {
  Serial.println("ejecting...");
  servo.write(50);
  delay(300);
  servo.write(180);
  handleRoot();
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