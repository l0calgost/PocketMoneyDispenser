#include <Arduino.h>
#include <Servo.h>
#include <ESPAsyncWebServer.h>
#include <config.h>

const char* ssid     = WLAN_SSID;
const char* password = WLAN_PASSWORD;

Servo servo;

AsyncWebServer server(80);

const char* htmlTemplate = R"(
<!DOCTYPE html>
<html>
<head>
  <title>Servo Steuerung</title>
  <style>
    body { 
      font-family: Arial, sans-serif;
      display: flex;
      justify-content: center;
      align-items: center;
      height: 100vh;
      margin: 0;
    }
    .button {
      display: inline-block;
      padding: 30px 50px;
      font-size: 25px;
      text-align: center;
      text-decoration: none;
      background-color: #4CAF50;
      color: #fff;
      border: none;
      border-radius: 4px;
      cursor: pointer;
    }
    .button:hover {
      background-color: #45a049;
    }
  </style>
</head>
<body>
  <button class='button' onclick='rotateServo()'>Ka-Ching!</button>
  <script>
    function rotateServo() {
      var xhr = new XMLHttpRequest();
      xhr.open('GET', '/rotate', true);
      xhr.send();
    }
  </script>
</body>
</html>
)";

// put function declarations here:
void eject();
void connectWifi();
void handleRoot();

void setup() {
  Serial.begin(115200);

  connectWifi();

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", htmlTemplate);
  });

  server.on("/rotate", HTTP_GET, [](AsyncWebServerRequest *request){
    eject();
    request->send(200, "text/plain", "Servo wurde um 30° gedreht");
  });
  
  servo.attach(2);
  servo.write(180);

  server.begin();
}

void loop() {
  // nothing to do
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
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}