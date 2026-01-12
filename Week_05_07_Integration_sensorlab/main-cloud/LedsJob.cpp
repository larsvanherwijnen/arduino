#include "LedsJob.h"
#include <ArduinoJson.h>

LedsJob::LedsJob(uint8_t pin, uint8_t count)
  : pixels(count, pin, NEO_GRB + NEO_KHZ800) {}

void LedsJob::setup() {
  pixels.begin();
  pixels.clear();
  pixels.show();
}

void LedsJob::onMqttMessage(
  const String& topic,
  const String& payload
) {
  DynamicJsonDocument doc(256);
  if (deserializeJson(doc, payload)) return;

  uint8_t r = doc["color"]["r"] | 0;
  uint8_t g = doc["color"]["g"] | 0;
  uint8_t b = doc["color"]["b"] | 0;

  setColor(r, g, b);
}

void LedsJob::setColor(uint8_t r, uint8_t g, uint8_t b) {
  for (int i = 0; i < pixels.numPixels(); i++) {
    pixels.setPixelColor(i, pixels.Color(r, g, b));
  }
  pixels.show();
}
