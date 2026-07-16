#ifndef BSP_CLOCK_H
#define BSP_CLOCK_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Initialize STM32 System Clock */
void BSP_Clock_Init(void);

/* Return current CPU frequency */
uint32_t BSP_Clock_GetFreq(void);

#ifdef __cplusplus
}
#endif

#endif
