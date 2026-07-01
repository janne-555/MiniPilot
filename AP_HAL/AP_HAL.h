#ifndef AP_HAL_H
#define AP_HAL_H

#include <stdint.h>

int hal_init(void);

void hal_comm_write(uint8_t *data, uint16_t len);
int  hal_comm_read(uint8_t *data, uint16_t len);

uint32_t hal_millis(void);

#endif
