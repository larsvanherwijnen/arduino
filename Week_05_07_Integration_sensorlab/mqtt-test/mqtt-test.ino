// MQTT -> NeoPixel example
#include <WiFiS3.h>
#include <ArduinoMqttClient.h>
#include <Adafruit_NeoPixel.h>
#include <ArduinoJson.h>
#include "secrets.h"

// ---------- NeoPixel config ----------
#define NEOPIXEL_PIN 6
#define NUM_PIXELS   8

Adafruit_NeoPixel pixels(NUM_PIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

// ---------- MQTT / WiFi ----------
WiFiClient wifi;
MqttClient client(wifi);

const char broker[] = "192.168.178.20";
int port = 1883;
const char subscribe_topic[] = "outgoing/data"; // no trailing space

// ================================================================
// Helpers: parse "rgb(r, g, b)" strings
// ================================================================
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

  r = (uint8_t)inside.substring(0, c1).toInt();
  g = (uint8_t)inside.substring(c1 + 1, c2).toInt();
  b = (uint8_t)inside.substring(c2 + 1).toInt();

  return true;
}

// ================================================================
// Parse JSON and pull out RGB + HEX
// Expecting payload like:
// {"source":"interval","color":{"hex":"#EE9CF8","rgb":"rgb(238, 156, 248)"},"timestamp":"..."}
//
// Extracts r,g,b into parameters and returns hex string (if present).
// ================================================================
bool parseRandomColor(const String& jsonStr, uint8_t &r, uint8_t &g, uint8_t &b, String &hexOut) {
  // small doc size is enough for your payload; increase if needed
  DynamicJsonDocument doc(256);
  DeserializationError err = deserializeJson(doc, jsonStr);
  if (err) {
    Serial.print("❌ JSON parse error: ");
    Serial.println(err.c_str());
    return false;
  }

  // Navigate to color object
  JsonObject color = doc["color"].as<JsonObject>();
  if (color.isNull()) return false;

  const char* hex = color["hex"];
  const char* rgb = color["rgb"];

  if (hex) hexOut = String(hex);
  if (rgb) {
    return parseRgbString(rgb, r, g, b);
  }

  // If no rgb but hex present, parse hex
  if (hex) {
    String h(hex);
    if (h.charAt(0) == '#') h = h.substring(1);
    if (h.length() != 6) return false;
    long val = (long) strtol(h.c_str(), NULL, 16);
    r = (val >> 16) & 0xFF;
    g = (val >> 8) & 0xFF;
    b = val & 0xFF;
    return true;
  }

  return false;
}

// ================================================================
// Set NeoPixel strip color
// ================================================================
void setStripColor(uint8_t r, uint8_t g, uint8_t b) {
  for (int i = 0; i < NUM_PIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(r, g, b));
  }
  pixels.show();
}

// ================================================================
// WiFi & MQTT connect helpers
// ================================================================
void connectWiFi() {
  Serial.print("Attempting to connect to WPA SSID ");
  Serial.println(SSID);

  WiFi.begin(SSID, PASS);
  unsigned long start = millis();
  const unsigned long timeout = 20000; // 20s timeout
  while (WiFi.status() != WL_CONNECTED) {
    if (millis() - start > timeout) {
      Serial.println("\nWiFi connect timeout, retrying...");
      WiFi.begin(SSID, PASS);
      start = millis();
    }
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nConnected to WiFi");
}

bool connectMQTT() {
  Serial.print("Attempting to connect to MQTT broker ");
  Serial.print(broker);
  Serial.print(":");
  Serial.println(port);

  if (!client.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error = ");
    Serial.println(client.connectError());
    return false;
  }

  Serial.println("Connected to MQTT broker!");
  return true;
}

void subscribeTopic() {
  Serial.print("Subscribing to topic: ");
  Serial.println(subscribe_topic);
  bool ok = client.subscribe(subscribe_topic);
  if (!ok) {
    Serial.println("Subscribe failed!");
  } else {
    Serial.println("Subscribe OK, waiting for messages...");
  }
}

// ================================================================
// Setup & Loop
// ================================================================
void setup() {
  Serial.begin(9600);
  // Remove the next line if your board doesn't use native USB Serial
  // while (!Serial) { ; }

  pixels.begin();
  pixels.show(); // initialize all pixels to 'off'

  connectWiFi();

  // If your broker needs auth:
  // client.setUsernamePassword(MQTT_USER, MQTT_PASS);

  if (!connectMQTT()) {
    Serial.println("Initial MQTT connect failed. Will try reconnecting in loop().");
  } else {
    subscribeTopic();
  }
}

void loop() {
  // Ensure WiFi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi lost. Reconnecting...");
    connectWiFi();
  }

  // Ensure MQTT
  if (!client.connected()) {
    Serial.println("MQTT disconnected. Reconnecting...");
    if (connectMQTT()) {
      subscribeTopic();
    } else {
      // Back off a bit before retrying
      delay(2000);
      return;
    }
  }

  // Check for new message
  int messageSize = client.parseMessage();
  if (messageSize) {
    // Read the full payload into a String
    String payload = "";
    while (client.available()) {
      payload += (char)client.read();
    }

    Serial.print("Received (");
    Serial.print(client.messageTopic());
    Serial.print(") : ");
    Serial.println(payload);

    // Parse JSON and set LEDs
    uint8_t r=0, g=0, b=0;
    String hexVal = "";
    if (parseRandomColor(payload, r, g, b, hexVal)) {
      Serial.print("Setting color RGB(");
      Serial.print(r); Serial.print(", ");
      Serial.print(g); Serial.print(", ");
      Serial.print(b); Serial.print(")");
      if (hexVal.length()) {
        Serial.print("  hex=");
        Serial.print(hexVal);
      }
      Serial.println();
      setStripColor(r, g, b);
    } else {
      Serial.println("Failed to parse color from payload");
    }
  }

  delay(10);
}
