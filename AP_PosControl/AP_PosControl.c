//------------------------------------------------------------------------------
// File    : AP_PosControl.c
// Purpose : Position Controller
// Project : MiniPilot
//------------------------------------------------------------------------------

#include "AP_PosControl.h"

#include "../AP_InertialNav/AP_InertialNav.h"

#include "../AP_Debug/AP_Debug.h"

static AP_PosControl_t pos;

/*
 PID storage
*/

static float integral;

/*
 Debug
*/

static float last_output = -999;

/*----------------------------------------------------------------------------
 Init
----------------------------------------------------------------------------*/

void AP_PosControl_Init(void)
{
    pos.target_altitude = 0.0f;

  pos.target_climb_rate = 0.0f;

  pos.current_altitude = 0.0f;

  pos.current_climb_rate = 0.0f;

  pos.throttle_output = 0.5f;

  pos.active = 0;

  integral = 0;
}

/*----------------------------------------------------------------------------
 Update
----------------------------------------------------------------------------*/

void AP_PosControl_Update(float dt) {
  if (!pos.active) {
    return;
  }

  /*
   * Get navigation state
   */

  pos.current_altitude = AP_InertialNav_GetAltitude();

  pos.current_climb_rate = AP_InertialNav_GetVelocityZ();

  /*
   * Altitude error
   */

  pos.altitude_error = pos.target_altitude - pos.current_altitude;

  /*
   * P controller creates climb demand
   */

  pos.target_climb_rate = pos.altitude_error * 0.5f;

  /*
   * Velocity loop
   */

  pos.velocity_error = pos.target_climb_rate - pos.current_climb_rate;

  /*
   * PID
   */

  integral += pos.velocity_error * dt;

  float output = (pos.velocity_error * 0.2f) + (integral * 0.01f);

  /*
   * Hover throttle + correction
   */

  pos.throttle_output = 0.5f + output;

  /*
   * limit
   */

  if (pos.throttle_output > 1.0f)
    pos.throttle_output = 1.0f;

  if (pos.throttle_output < 0.0f)
    pos.throttle_output = 0.0f;

  if ((pos.throttle_output - last_output > 0.05f) ||
      (last_output - pos.throttle_output > 0.05f)) {

    AP_Debug_Print(DBG_POS,

                   "\n===== POS CONTROL =====\n"
                   "Target Alt : %.2f\n"
                   "Current Alt: %.2f\n"
                   "Alt Error  : %.2f\n"
                   "Climb Err  : %.2f\n"
                   "Throttle   : %.2f\n",

                   pos.target_altitude,

                   pos.current_altitude,

                   pos.altitude_error,

                   pos.velocity_error,

                   pos.throttle_output);

    last_output = pos.throttle_output;
  }
}

/*----------------------------------------------------------------------------
 Setters
----------------------------------------------------------------------------*/

void AP_PosControl_SetAltTarget(float altitude)
{
    pos.target_altitude = altitude;

  pos.active = 1;
}

void AP_PosControl_SetClimbRate(float rate)
{
    pos.target_climb_rate = rate;
}

/*----------------------------------------------------------------------------
 Getters
----------------------------------------------------------------------------*/

float AP_PosControl_GetThrottle(void)
{
    return pos.throttle_output;
}

const AP_PosControl_t *AP_PosControl_Get(void) { return &pos; }

void AP_PosControl_Enable(uint8_t enable)
{
    pos.active = enable;
}
