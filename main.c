#include "stm32h7xx.h"

#include "bsp_clock.h"
#include "bsp_gpio.h"
#include "bsp_uart.h"
#include "bsp_timer.h"
#include "bsp_scheduler.h"

int main(void)
{
    SystemInit();

    BSP_Clock_Init();
    BSP_GPIO_Init();
    BSP_UART_Init();
    BSP_Timer_Init();
    BSP_Scheduler_Init();

    while (1)
    {
	    BSP_Scheduler_Run();
    }
}
