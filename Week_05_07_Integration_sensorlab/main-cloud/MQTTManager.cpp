#include "MqttManager.h"
#include <WiFiS3.h>

static WiFiClient wifi;
static MqttClient mqtt(wifi);
static JobBase* activeJob = nullptr;

const char* BROKER = "192.168.178.20";
const int   PORT   = 1883;
const char* TOPIC  = "jobs/data";

void mqttSetup(JobBase* job) {
    activeJob = job;

    mqtt.connect(BROKER, PORT);
    mqtt.subscribe(TOPIC);
}

void mqttLoop() {
    if (!mqtt.connected()) return;

    int size = mqtt.parseMessage();
    if (!size) return;

    String payload;
    while (mqtt.available()) {
        payload += (char)mqtt.read();
    }

    if (activeJob) {
        activeJob->onMqttMessage(mqtt.messageTopic(), payload);
    }
}
