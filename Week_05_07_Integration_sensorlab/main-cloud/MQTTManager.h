#ifndef MQTT_MANAGER_H
#define MQTT_MANAGER_H

#include <ArduinoMqttClient.h>
#include "JobBase.h"

void mqttSetup(JobBase* job);
void mqttLoop();

#endif
