#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <WiFiS3.h>
#include "EEPROMHelper.h"

// Expandable Job enum
enum JobType {
    JOB_NONE = 0,
    JOB_PRINT_TASK,
    JOB_PRINT_FEELINGS,
    JOB_CONTROL_LEDS
};

JobType getJob();
void setJob(JobType job);
const char* jobTypeToString(JobType job);

void handleConfigClient(WiFiClient &client);
String getRoomID();
void setRoomID(const String &roomID);

#endif
