#pragma once
#include "JobBase.h"

class PrintFeelingsJob : public JobBase {
public:
    const char* name() override;

    void setup() override;
    void loop() override;
    void onMqttMessage(const String& topic, const String& payload) override;
};
