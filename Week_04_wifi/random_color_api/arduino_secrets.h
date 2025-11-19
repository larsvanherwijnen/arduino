#include <WiFiS3.h>
#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>
#include "arduino_secrets.h"     

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

const char* server = "random-color.larsvanherwijnen.nl";
const int   port   = 80;
const char* path   = "/api/random";

#define NEOPIXEL_PIN 6
#define NUM_PIXELS   8

Adafruit_NeoPixel pixels(NUM_PIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

void connectToWiFi() {
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("  ...still trying");
  }

  Serial.println("Connected to WiFi.");
}

String fetchRandomColorJson() {
  WiFiClient client;
  String response = "";

  Serial.println("\nConnecting to random-color API...");

  if (!client.connect(server, port)) {
    Serial.println("❌ Connection failed");
    return "";
  }

  client.print("GET ");
  client.print(path);
  client.println(" HTTP/1.1");
  client.print("Host: ");
  client.println(server);
  client.println("Connection: close");
  client.println();

  unsigned long timeout = millis();
  while (client.connected() || client.available()) {
    if (client.available()) {
      response += (char)client.read();
      timeout = millis();
    } else {
      if (millis() - timeout > 5000) {
        Serial.println("❌ Timeout while reading");
        break;
      }
      delay(10);
    }
  }
  client.stop();

  return response;
}


String extractJsonBody(const String& httpResponse) {
  int start = httpResponse.indexOf('{');
  int end   = httpResponse.lastIndexOf('}');
  if (start < 0 || end < 0) return "";
  return httpResponse.substring(start, end + 1);
}

bool parseRgbString(const char* rgbStr, uint8_t &r, uint8_t &g, uint8_t &b) {
  if (!rgbStr) return false;

  String s(rgbStr);
  int open = s.indexOf('(');
  int close = s.indexOf(')');
  if (open < 0 || close < 0) return false;

  String inside = s.substring(open + 1, close);

  int c1 = inside.indexOf(',');
  int c2 = inside.indexOf(',', c1 + 1);
  if (c1 < 0 || c2 < 0) return false;

  r = inside.substring(0, c1).toInt();
  g = inside.substring(c1 + 1, c2).toInt();
  b = inside.substring(c2 + 1).toInt();

  return true;
}

bool parseRandomColor(const String& jsonStr, uint8_t &r, uint8_t &g, uint8_t &b, String &hexOut) {
  DynamicJsonDocument doc(256);

  DeserializationError err = deserializeJson(doc, jsonStr);
  if (err) {
    Serial.print("❌ JSON parse error: ");
    Serial.println(err.c_str());
    return false;
  }

  const char* hex = doc["hex"];
  const char* rgb = doc["rgb"];

  if (!hex || !rgb) return false;

  hexOut = hex;

  return parseRgbString(rgb, r, g, b);
}

void setStripColor(uint8_t r, uint8_t g, uint8_t b) {
  for (int i = 0; i < NUM_PIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(r, g, b));
  }
  pixels.show();
}

void setup() {
  Serial.begin(9600);

  pixels.begin();
  pixels.setBrightness(60);
  pixels.show();

  connectToWiFi();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    connectToWiFi();
    return;
  }

  String response = fetchRandomColorJson();
  if (response.length() == 0) {
    delay(3000);
    return;
  }

  String json = extractJsonBody(response);
  Serial.println("JSON: " + json);

  uint8_t r, g, b;
  String hex;

  if (parseRandomColor(json, r, g, b, hex)) {
    Serial.print("✔ Color = ");
    Serial.print(hex);
    Serial.print(" → RGB(");
    Serial.print(r); Serial.print(", ");
    Serial.print(g); Serial.print(", ");
    Serial.print(b); Serial.println(")");

    setStripColor(r, g, b);
  } else {
    Serial.println("❌ Failed to parse color");
  }

  delay(3000);
}
