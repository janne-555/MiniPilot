#include "bsp_gpio.h"

void BSP_GPIO_Init(void)
{
    /* GPIO initialization will be added later */
}

void BSP_GPIO_Write(GPIO_TypeDef *port,
                    uint16_t pin,
                    BSP_GPIO_State state)
{
    if(state == BSP_GPIO_HIGH)
    {
        port->BSRR = pin;
    }
    else
    {
        port->BSRR = (uint32_t)pin << 16U;
    }
}

void BSP_GPIO_Toggle(GPIO_TypeDef *port,
                     uint16_t pin)
{
    port->ODR ^= pin;
}

BSP_GPIO_State BSP_GPIO_Read(GPIO_TypeDef *port,
                             uint16_t pin)
{
    if(port->IDR & pin)
    {
        return BSP_GPIO_HIGH;
    }

    return BSP_GPIO_LOW;
}
