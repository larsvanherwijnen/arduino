#ifndef PRINT_TASK_JOB_H
#define PRINT_TASK_JOB_H

#include "JobBase.h"

class PrintTaskJob : public JobBase {
public:
    const char* name() override;

    void setup() override;
    void loop() override;
    void onMqttMessage(const String& topic, const String& payload) override;
};

#endif
