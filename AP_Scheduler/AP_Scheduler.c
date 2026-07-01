//------------------------------------------------------------------------------
// File    : AP_Scheduler.c
// Purpose : MiniPilot task scheduler
// Project : MiniPilot
//------------------------------------------------------------------------------

#include "AP_Scheduler.h"

#include "../AP_HAL/AP_HAL.h"

#define MAX_TASKS 20

static AP_Task_t tasks[MAX_TASKS];

static uint8_t task_count = 0;

// Initialize scheduler
void AP_Scheduler_Init(void)
{
    task_count = 0;
}

// Register task
int AP_Scheduler_Add_Task(TaskFunction_t function,
                          uint32_t period_ms)
{
    if(task_count >= MAX_TASKS)
    {
        return -1;
    }

    tasks[task_count].function = function;

    tasks[task_count].period_ms = period_ms;

    tasks[task_count].last_run_ms = 0;

    task_count++;

    return 0;
}

// Execute scheduler
void AP_Scheduler_Run(void)
{
    uint32_t now = hal_millis();

    for(uint8_t i=0;i<task_count;i++)
    {
        if((now - tasks[i].last_run_ms) >=
            tasks[i].period_ms)
        {
            tasks[i].last_run_ms = now;

            tasks[i].function();
        }
    }
}
