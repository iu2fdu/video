#include <ESPAsyncWebServer.h>
#include "SPIFFS.h"
/**
 * https://github.com/me-no-dev/ESPAsyncWebServer
 * https://github.com/me-no-dev/AsyncTCP
 * 
 */
#include "secrets.h"
#include <WiFi.h>

AsyncWebServer server(80);

void setup() {
  pinMode(5, OUTPUT);
  digitalWrite(5, LOW);
  
  Serial.begin(115200);
  delay(1000);
  Serial.println("SPIFFS web");

  if (!SPIFFS.begin(true)) {
    Serial.println("SPIFFS KO");
    while(1);
  }

  WiFi.begin(MY_WIFI_SSID, MY_WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nconnesso");
  Serial.print("IP: ");Serial.println(WiFi.localIP());   

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *req){
    req->send(SPIFFS, "/index.html", String(), false, processor);  
  });
  server.on("/index.html", HTTP_GET, [](AsyncWebServerRequest *req){
    req->send(SPIFFS, "/index.html", String(), false, processor);  
  });
  server.on("/home.html", HTTP_GET, [](AsyncWebServerRequest *req){
    req->send(SPIFFS, "/home.html", String(), false, processor);  
  });
  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *req){
    digitalWrite(5, HIGH);
    req->send(SPIFFS, "/index.html", String(), false, processor);  
  });
  server.on("/off", HTTP_GET, [](AsyncWebServerRequest *req){
    digitalWrite(5, LOW);
    req->send(SPIFFS, "/index.html", String(), false, processor);  
  });
  server.begin();
}

void loop() {
 
}

String processor (const String& par) {
  // %STATO_LED%
  if (par == "STATO_LED") {
    if (digitalRead(5)) {
      return "ON";  
    } else {
      return "OFF";
    }  
  } 
  return String();  
}
