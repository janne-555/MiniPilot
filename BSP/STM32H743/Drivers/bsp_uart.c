#include "bsp_uart.h"

/*
 * UART Driver
 *
 * Initial version.
 * Hardware initialization will be added later.
 */

void BSP_UART_Init(void)
{

}

void BSP_UART_SendChar(char c)
{
    (void)c;
}

void BSP_UART_SendString(const char *str)
{
    while (*str)
    {
        BSP_UART_SendChar(*str++);
    }
}

char BSP_UART_ReadChar(void)
{
    return 0;
}
