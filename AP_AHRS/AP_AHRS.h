//------------------------------------------------------------------------------
// File    : AP_AHRS.h
// Purpose : Attitude Heading Reference System
// Project : MiniPilot
//------------------------------------------------------------------------------

#ifndef AP_AHRS_H
#define AP_AHRS_H

#include <stdint.h>

/*----------------------------------------------------------------------------
 * AHRS State
 *---------------------------------------------------------------------------*/

typedef struct {
  float roll;

  float pitch;

  float yaw;

  uint8_t healthy;

} AP_AHRS_t;

/*----------------------------------------------------------------------------
 * API
 *---------------------------------------------------------------------------*/

void AP_AHRS_Init(void);

void AP_AHRS_Update(void);

float AP_AHRS_GetRoll(void);

float AP_AHRS_GetPitch(void);

float AP_AHRS_GetYaw(void);

uint8_t AP_AHRS_IsHealthy(void);

const AP_AHRS_t *AP_AHRS_Get(void);

#endif
