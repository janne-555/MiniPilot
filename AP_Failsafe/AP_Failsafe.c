//------------------------------------------------------------------------------
// File    : AP_Failsafe.c
// Purpose : Vehicle Safety Monitor
// Project : MiniPilot
//------------------------------------------------------------------------------

#include "AP_Failsafe.h"

#include "AP_Debug/AP_Debug.h"

/*----------------------------------------------------------------------------
 * Private Variables
 *---------------------------------------------------------------------------*/

static AP_Failsafe_t failsafe;

static uint8_t last_active = 255;
static uint8_t last_action = 255;
static AP_Failsafe_Type_t last_reason = 255;

/*----------------------------------------------------------------------------
 * Initialize
 *---------------------------------------------------------------------------*/

void AP_Failsafe_Init(void)
{
    failsafe.active = 0;

  failsafe.reason = FAILSAFE_NONE;

  failsafe.action = FAILSAFE_ACTION_NONE;

  failsafe.rc_lost = 0;

  failsafe.battery_low = 0;

  failsafe.imu_failure = 0;

  failsafe.gps_failure = 0;

  failsafe.compass_failure = 0;

  failsafe.barometer_failure = 0;

  failsafe.ekf_failure = 0;

  failsafe.motor_failure = 0;
}

/*----------------------------------------------------------------------------
 * Update
 *---------------------------------------------------------------------------*/

void AP_Failsafe_Update(void) {
  /*
   * Reset decision every loop
   */

  failsafe.active = 0;

  failsafe.reason = FAILSAFE_NONE;

  failsafe.action = FAILSAFE_ACTION_NONE;

  /*
   * Priority order:
   *
   * Critical sensors first
   */

  if (failsafe.imu_failure) {
    failsafe.active = 1;

    failsafe.reason = FAILSAFE_IMU;

    failsafe.action = FAILSAFE_ACTION_DISARM;
  }

  else if (failsafe.ekf_failure)
{
    failsafe.active = 1;

    failsafe.reason = FAILSAFE_EKF;

    failsafe.action = FAILSAFE_ACTION_LAND;
}

  else if (failsafe.motor_failure)
{
    failsafe.active = 1;

    failsafe.reason = FAILSAFE_MOTOR;

    failsafe.action = FAILSAFE_ACTION_DISARM;
}

  else if (failsafe.battery_low)
{
    failsafe.active = 1;

    failsafe.reason = FAILSAFE_BATTERY;

    failsafe.action = FAILSAFE_ACTION_LAND;
}

  else if (failsafe.rc_lost)
{
    failsafe.active = 1;

    failsafe.reason = FAILSAFE_RC;

    failsafe.action = FAILSAFE_ACTION_RTL;
}

  else if (failsafe.gps_failure)
{
    failsafe.active = 1;

    failsafe.reason = FAILSAFE_GPS;

    failsafe.action = FAILSAFE_ACTION_HOLD;
}

  else if (failsafe.compass_failure)
{
    failsafe.active = 1;

    failsafe.reason = FAILSAFE_COMPASS;

    failsafe.action = FAILSAFE_ACTION_HOLD;
}

  else if (failsafe.barometer_failure)
{
    failsafe.active = 1;

    failsafe.reason = FAILSAFE_BAROMETER;

    failsafe.action = FAILSAFE_ACTION_HOLD;
}

  /*
   * Debug only on change
   */
  if ((failsafe.active != last_active) || (failsafe.reason != last_reason) ||
      (failsafe.action != last_action)) {
    AP_Debug_Print(DBG_FAILSAFE,
                   "\n===== FAILSAFE =====\n"
                   "Active : %u\n"
                   "Reason : %d\n"
                   "Action : %d\n",
                   failsafe.active, failsafe.reason, failsafe.action);

    last_active = failsafe.active;
    last_reason = failsafe.reason;
    last_action = failsafe.action;
  }
}

/*----------------------------------------------------------------------------
 * External Inputs
 *---------------------------------------------------------------------------*/

void AP_Failsafe_SetRC(uint8_t state)
{
    failsafe.rc_lost = state;
}

void AP_Failsafe_SetBattery(uint8_t state)
{
    failsafe.battery_low = state;
}

void AP_Failsafe_SetIMU(uint8_t state)
{
    failsafe.imu_failure = state;
}

void AP_Failsafe_SetGPS(uint8_t state)
{
    failsafe.gps_failure = state;
}

void AP_Failsafe_SetCompass(uint8_t state)
{
    failsafe.compass_failure = state;
}

void AP_Failsafe_SetBarometer(uint8_t state)
{
    failsafe.barometer_failure = state;
}

void AP_Failsafe_SetEKF(uint8_t state)
{
    failsafe.ekf_failure = state;
}

void AP_Failsafe_SetMotor(uint8_t state)
{
    failsafe.motor_failure = state;
}

/*----------------------------------------------------------------------------
 * Get State
 *---------------------------------------------------------------------------*/

const AP_Failsafe_t *AP_Failsafe_Get(void) { return &failsafe; }

uint8_t AP_Failsafe_IsActive(void)
{
    return failsafe.active;
}

AP_Failsafe_Type_t AP_Failsafe_GetReason(void)
{
    return failsafe.reason;
}

AP_Failsafe_Action_t AP_Failsafe_GetAction(void)
{
    return failsafe.action;
}
