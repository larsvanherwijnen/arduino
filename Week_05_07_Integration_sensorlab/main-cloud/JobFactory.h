#ifndef JOB_FACTORY_H
#define JOB_FACTORY_H

#include "JobBase.h"
#include "ConfigManager.h"

JobBase* createJob(JobType type);

#endif
