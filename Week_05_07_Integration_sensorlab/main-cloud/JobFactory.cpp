#include "JobFactory.h"
#include "LedsJob.h"
#include "PrintTaskJob.h"
#include "PrintFeelingsJob.h"

JobBase* createJob(JobType type) {

  switch (type) {

    case JOB_CONTROL_LEDS:
      return new LedsJob(6, 8);

    case JOB_PRINT_TASK:
      return new PrintTaskJob();

    case JOB_PRINT_FEELINGS:
      return new PrintFeelingsJob();

    default:
      return nullptr;
  }
}
