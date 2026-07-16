#ifndef BSP_SCHEDULER_H
#define BSP_SCHEDULER_H

#include <stdint.h>

typedef void (*TaskFunction)(void);

typedef struct
{
    TaskFunction task;
    uint32_t period_ms;
    uint32_t last_run;
} SchedulerTask;

void BSP_Scheduler_Init(void);

void BSP_Register_Task(TaskFunction task, uint32_t period_ms);

void BSP_Scheduler_Run(void);

#endif
