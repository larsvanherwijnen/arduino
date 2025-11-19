#include <Adafruit_NeoPixel.h>

#define LED_PIN    6      // Data pin connected to DIN
#define LED_COUNT  8      // Number of LEDs

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // Simple color cycle
  strip.fill(strip.Color(255, 0, 0)); // Red
  strip.show();
  delay(500);

  strip.fill(strip.Color(0, 255, 0)); // Green
  strip.show();
  delay(500);

  strip.fill(strip.Color(0, 0, 255)); // Blue
  strip.show();
  delay(500);
}