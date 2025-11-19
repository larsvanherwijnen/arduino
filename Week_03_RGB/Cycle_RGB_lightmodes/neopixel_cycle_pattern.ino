#include <Adafruit_NeoPixel.h>

#define LED_PIN     6
#define LED_COUNT   8
#define BUTTON_PIN  2

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// Color helpers (use strip.Color(...) at runtime)
#define RED    strip.Color(255, 0, 0)
#define GREEN  strip.Color(0, 255, 0)
#define BLUE   strip.Color(0, 0, 255)

enum {
  MODE_SOLID_RED = 0,
  MODE_SOLID_GREEN,
  MODE_SOLID_BLUE,
  MODE_RAINBOW,
  MODE_THEATER,
  MODE_FIRE,
  MODE_SPARKLE,
  MODE_OFF,
  MODE_COUNT
};

int mode = MODE_SOLID_RED;

// ---- Button debounce / edge detect ----
int lastReading = HIGH, stableState = HIGH;
unsigned long lastDebounce = 0;
const unsigned long debounceDelay = 35;

// ---- Animation state ----
unsigned long nowMs = 0;

// Rainbow
unsigned long rainbowTimer = 0;
uint16_t rainbowPos = 0;
const unsigned long rainbowInterval = 35;

// Theater chase
unsigned long theaterTimer = 0;
uint8_t theaterPhase = 0;
const unsigned long theaterInterval = 90;

// Fire
unsigned long fireTimer = 0;
const unsigned long fireInterval = 50;

// Sparkle
unsigned long sparkleTimer = 0;
const unsigned long sparkleInterval = 50;

uint32_t wheel(byte pos) {
  pos = 255 - pos;
  if (pos < 85) return strip.Color(255 - pos * 3, 0, pos * 3);
  if (pos < 170) { pos -= 85; return strip.Color(0, pos * 3, 255 - pos * 3); }
  pos -= 170; return strip.Color(pos * 3, 255 - pos * 3, 0);
}

// ---------- Patterns ----------
void solidColor(uint32_t c) {
  static uint32_t last = 0xFFFFFFFF;
  if (c != last) {
    strip.fill(c);
    strip.show();
    last = c;
  }
}

void modeRainbowCycle() {
  if (nowMs - rainbowTimer >= rainbowInterval) {
    for (uint16_t i = 0; i < LED_COUNT; i++) {
      strip.setPixelColor(i, wheel(((i * 256 / LED_COUNT) + rainbowPos) & 255));
    }
    strip.show();
    rainbowPos = (rainbowPos + 1) & 255;
    rainbowTimer = nowMs;
  }
}

void modeTheaterChase() {
  if (nowMs - theaterTimer >= theaterInterval) {
    strip.clear();
    for (int i = theaterPhase; i < LED_COUNT; i += 3) {
      strip.setPixelColor(i, strip.Color(255, 180, 60)); // warm dots
    }
    strip.show();
    theaterPhase = (theaterPhase + 1) % 3;
    theaterTimer = nowMs;
  }
}

void modeFireFlicker() {
  if (nowMs - fireTimer >= fireInterval) {
    for (int i = 0; i < LED_COUNT; i++) {
      uint8_t r = 160 + random(96);     // 160..255
      uint8_t g = random(120);          // 0..119
      uint8_t b = 0;
      // cool the green a bit with position for depth
      g = (uint8_t)(g * (0.4 + 0.6 * (float)i / (LED_COUNT - 1)));
      strip.setPixelColor(i, strip.Color(r, g, b));
    }
    strip.show();
    fireTimer = nowMs;
  }
}

void modeSparkle() {
  if (nowMs - sparkleTimer >= sparkleInterval) {
    // gentle dim of all pixels
    for (int i = 0; i < LED_COUNT; i++) {
      uint32_t c = strip.getPixelColor(i);
      uint8_t r = (uint8_t)( (c >> 16) & 0xFF );
      uint8_t g = (uint8_t)( (c >> 8)  & 0xFF );
      uint8_t b = (uint8_t)(  c        & 0xFF );
      r = (r * 200) / 255;
      g = (g * 200) / 255;
      b = (b * 200) / 255;
      strip.setPixelColor(i, strip.Color(r, g, b));
    }
    // add a random white sparkle
    int idx = random(LED_COUNT);
    strip.setPixelColor(idx, strip.Color(255, 255, 255));
    strip.show();
    sparkleTimer = nowMs;
  }
}

void modeOff() {
  static bool cleared = false;
  if (!cleared) {
    strip.clear();
    strip.show();
    cleared = true;
  }
}

// ---------- Button & mode handling ----------
void handleButton() {
  int reading = digitalRead(BUTTON_PIN);
  if (reading != lastReading) {
    lastDebounce = nowMs;
  }
  if ((nowMs - lastDebounce) > debounceDelay) {
    if (reading != stableState) {
      stableState = reading;
      if (stableState == LOW) {
        // advance mode on press
        mode = (mode + 1) % MODE_COUNT;
        // reset one-shot flags/state for certain modes
        // ensure 'off' clears once, and solid forces refresh
        // (clear cached state by tweaking)
        // simplest: just clear so the next mode paints fresh
        strip.clear();
        strip.show();
      }
    }
  }
  lastReading = reading;
}

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  strip.begin();
  strip.show();
  randomSeed(analogRead(A0)); // if available; else millis() based
  Serial.println("Press the button to cycle modes");
}

void loop() {
  nowMs = millis();
  handleButton();

  switch (mode) {
    case MODE_SOLID_RED:    solidColor(RED);   break;
    case MODE_SOLID_GREEN:  solidColor(GREEN); break;
    case MODE_SOLID_BLUE:   solidColor(BLUE);  break;
    case MODE_RAINBOW:      modeRainbowCycle(); break;
    case MODE_THEATER:      modeTheaterChase(); break;
    case MODE_FIRE:         modeFireFlicker();  break;
    case MODE_SPARKLE:      modeSparkle();      break;
    case MODE_OFF:          modeOff();          break;
  }
}
