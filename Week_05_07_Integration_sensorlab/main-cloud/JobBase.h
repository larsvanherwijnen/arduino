#pragma once
#include <Arduino.h>

class JobBase {
public:
  virtual ~JobBase() {}

  virtual const char* name() = 0;
  virtual void setup() = 0;
  virtual void loop() = 0;

  virtual void onMqttMessage(
    const String& topic,
    const String& payload
  ) = 0;
};
