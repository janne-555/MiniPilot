//------------------------------------------------------------------------------
// File    : AP_PosControl.h
// Purpose : Position / Altitude Controller
// Project : MiniPilot
//------------------------------------------------------------------------------

#ifndef AP_POSCONTROL_H
#define AP_POSCONTROL_H

#include <stdint.h>

typedef struct {

  /*
   * Targets
   */

  float target_altitude;

  float target_climb_rate;

  /*
   * Current state
   */

  float current_altitude;

  float current_climb_rate;

  /*
   * Errors
   */

  float altitude_error;

  float velocity_error;

  /*
   * Output
   */

  float throttle_output;

  uint8_t active;

} AP_PosControl_t;

void AP_PosControl_Init(void);

void AP_PosControl_Update(float dt);

void AP_PosControl_Enable(uint8_t enable);

void AP_PosControl_SetAltTarget(float altitude);

void AP_PosControl_SetClimbRate(float rate);

float AP_PosControl_GetThrottle(void);

const AP_PosControl_t *AP_PosControl_Get(void);

#endif
