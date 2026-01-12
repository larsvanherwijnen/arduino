#pragma once
#include "JobBase.h"
#include <Adafruit_NeoPixel.h>

class LedsJob : public JobBase {
public:
  LedsJob(uint8_t pin, uint8_t count);

  const char* name() override {
    return "LEDs";
  }

  void setup() override;
  void loop() override {}

  void onMqttMessage(
    const String& topic,
    const String& payload
  ) override;

private:
  Adafruit_NeoPixel pixels;

  void setColor(uint8_t r, uint8_t g, uint8_t b);
};
