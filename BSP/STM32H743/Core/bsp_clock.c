#include "bsp_clock.h"

#include "stm32h7xx.h"

/*
 * Initialize system clock.
 *
 * Currently this simply calls the CMSIS clock initialization.
 * Later we will configure PLL, Flash latency,
 * bus clocks and peripheral clocks here.
 */

void BSP_Clock_Init(void)
{
    SystemInit();
}

/*
 * Return current CPU frequency.
 */

uint32_t BSP_Clock_GetFreq(void)
{
    return SystemCoreClock;
}
