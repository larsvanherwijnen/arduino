#include "PrintTaskJob.h"

const char* PrintTaskJob::name() {
    return "Task Printer";
}

void PrintTaskJob::setup() {
    Serial.println("🖨 PrintTaskJob ready");
}

void PrintTaskJob::loop() {
    // idle
}

void PrintTaskJob::onMqttMessage(const String& topic, const String& payload) {
    Serial.println("🖨 Task received:");
    Serial.println(payload);
}
