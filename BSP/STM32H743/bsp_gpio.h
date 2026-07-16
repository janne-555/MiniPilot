#ifndef BSP_GPIO_H
#define BSP_GPIO_H

#include "stm32h7xx.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    BSP_GPIO_LOW = 0,
    BSP_GPIO_HIGH = 1

} BSP_GPIO_State;

void BSP_GPIO_Init(void);

void BSP_GPIO_Write(GPIO_TypeDef *port,
                    uint16_t pin,
                    BSP_GPIO_State state);

void BSP_GPIO_Toggle(GPIO_TypeDef *port,
                     uint16_t pin);

BSP_GPIO_State BSP_GPIO_Read(GPIO_TypeDef *port,
                             uint16_t pin);

#ifdef __cplusplus
}
#endif

#endif
