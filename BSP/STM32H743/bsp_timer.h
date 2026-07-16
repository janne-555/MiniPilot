#ifndef BSP_TIMER_H
#define BSP_TIMER_H

#include <stdint.h>

void BSP_Timer_Init(void);

uint32_t BSP_Timer_Millis(void);

uint32_t BSP_Timer_Micros(void);

void BSP_Delay(uint32_t ms);

#endif
