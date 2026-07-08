//------------------------------------------------------------------------------
// File    : AP_Arming.h
// Purpose : Vehicle Arming
// Project : MiniPilot
//------------------------------------------------------------------------------
#ifndef AP_ARMING_H
#define AP_ARMING_H

#include <stdint.h>
typedef struct {
  uint8_t armed;

  uint8_t pre_arm_ok;

  uint8_t gyro_ok;

  uint8_t accel_ok;

  uint8_t compass_ok;

  uint8_t gps_ok;

  uint8_t battery_ok;

  uint8_t rc_ok;

  uint8_t failsafe;

} AP_Arming_t;

void AP_Arming_Init(void);

void AP_Arming_Update(void);

void AP_Arming_Arm(void);

void AP_Arming_Disarm(void);

void AP_Arming_Toggle(void);

const AP_Arming_t *AP_Arming_Get(void);

uint8_t AP_Arming_IsArmed(void);

#endif
