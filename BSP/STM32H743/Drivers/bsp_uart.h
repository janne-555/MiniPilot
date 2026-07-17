#ifndef BSP_UART_H
#define BSP_UART_H

#include "stm32h7xx.h"

#ifdef __cplusplus
extern "C" {
#endif

void BSP_UART_Init(void);

void BSP_UART_SendChar(char c);

void BSP_UART_SendString(const char *str);

char BSP_UART_ReadChar(void);

#ifdef __cplusplus
}
#endif

#endif
