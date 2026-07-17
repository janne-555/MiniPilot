#include "bsp_timer.h"
#include "stm32h7xx.h"

static volatile uint32_t system_ms = 0;

void BSP_Timer_Init(void)
{
    system_ms = 0;

    SysTick_Config(SystemCoreClock / 1000);
}

void SysTick_Handler(void)
{
    system_ms++;
}

uint32_t BSP_Timer_Millis(void)
{
    return system_ms;
}

uint32_t BSP_Timer_Micros(void)
{
    return system_ms * 1000;
}

void BSP_Delay(uint32_t ms)
{
    uint32_t start = BSP_Timer_Millis();

    while ((BSP_Timer_Millis() - start) < ms)
    {
    }
}
