#include "PrintFeelingsJob.h"

const char* PrintFeelingsJob::name() {
    return "Feelings Printer";
}

void PrintFeelingsJob::setup() {
    Serial.println("🖨 Feelings printer ready");
}

void PrintFeelingsJob::loop() {
    // nothing to do yet
}

void PrintFeelingsJob::onMqttMessage(
    const String& topic,
    const String& payload
) {
    Serial.print("💭 Feeling: ");
    Serial.println(payload);
}
