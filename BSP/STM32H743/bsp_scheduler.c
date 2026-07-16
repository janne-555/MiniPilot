#include "bsp_scheduler.h"
#include "bsp_timer.h"

#define MAX_TASKS 16

static SchedulerTask tasks[MAX_TASKS];
static uint32_t task_count = 0;

void BSP_Scheduler_Init(void)
{
    task_count = 0;
}

void BSP_Register_Task(TaskFunction task, uint32_t period_ms)
{
    if (task_count >= MAX_TASKS)
        return;

    tasks[task_count].task = task;
    tasks[task_count].period_ms = period_ms;
    tasks[task_count].last_run = 0;

    task_count++;
}

void BSP_Scheduler_Run(void)
{
    uint32_t now = BSP_Timer_Millis();

    for (uint32_t i = 0; i < task_count; i++)
    {
        if ((now - tasks[i].last_run) >= tasks[i].period_ms)
        {
            tasks[i].last_run = now;

            if (tasks[i].task)
                tasks[i].task();
        }
    }
}
