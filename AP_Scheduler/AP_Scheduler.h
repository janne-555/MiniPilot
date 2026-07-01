//------------------------------------------------------------------------------
// File    : AP_Scheduler.h
// Purpose : MiniPilot task scheduler
// Project : MiniPilot
//------------------------------------------------------------------------------

#ifndef AP_SCHEDULER_H
#define AP_SCHEDULER_H

#include <stdint.h>

// Task callback
typedef void (*TaskFunction_t)(void);

// Scheduler task
typedef struct
{
    TaskFunction_t function;

    uint32_t period_ms;

    uint32_t last_run_ms;

} AP_Task_t;

// Initialize scheduler
void AP_Scheduler_Init(void);

// Register new task
int AP_Scheduler_Add_Task(TaskFunction_t function,
                          uint32_t period_ms);

// Execute scheduler
void AP_Scheduler_Run(void);

#endif
