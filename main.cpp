#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "raj";
const char* password = "fansina123";

ESP8266WebServer server(80);
const int ledPin = 2; // Use GPIO pin, D1 is usually GPIO5

void handleOn() {
  digitalWrite(ledPin, HIGH);
  server.send(200, "text/plain", "LED is ON");
  Serial.println("led_on");
}

void handleOff() {
  digitalWrite(ledPin, LOW);
  Serial.println("led_off");
  server.send(200, "text/plain", "LED is OFF");
}

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/on", handleOn);
  server.on("/off", handleOff);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
