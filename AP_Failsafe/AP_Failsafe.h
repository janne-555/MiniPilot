//------------------------------------------------------------------------------
// File    : AP_Failsafe.h
// Purpose : Vehicle Safety Monitor
// Project : MiniPilot
//------------------------------------------------------------------------------

#ifndef AP_FAILSAFE_H
#define AP_FAILSAFE_H

#include <stdint.h>

/*----------------------------------------------------------------------------
 * Failsafe Types
 *---------------------------------------------------------------------------*/

typedef enum {
  FAILSAFE_NONE = 0,

  FAILSAFE_RC,

  FAILSAFE_BATTERY,

  FAILSAFE_IMU,

  FAILSAFE_GPS,

  FAILSAFE_COMPASS,

  FAILSAFE_BAROMETER,

  FAILSAFE_EKF,

  FAILSAFE_MOTOR

} AP_Failsafe_Type_t;

typedef enum {
  FAILSAFE_ACTION_NONE = 0,

  FAILSAFE_ACTION_LAND,

  FAILSAFE_ACTION_RTL,

  FAILSAFE_ACTION_HOLD,

  FAILSAFE_ACTION_DISARM,

  FAILSAFE_ACTION_TERMINATE

} AP_Failsafe_Action_t;
/*----------------------------------------------------------------------------
 * Failsafe State
 *---------------------------------------------------------------------------*/

typedef struct {
  uint8_t active;

  AP_Failsafe_Type_t reason;

  AP_Failsafe_Action_t action;

  uint8_t rc_lost;

  uint8_t battery_low;

  uint8_t battery_critical;

  uint8_t imu_failure;

  uint8_t gps_failure;

  uint8_t compass_failure;

  uint8_t barometer_failure;

  uint8_t ekf_failure;

  uint8_t motor_failure;

} AP_Failsafe_t;

/*----------------------------------------------------------------------------
 * API
 *---------------------------------------------------------------------------*/

void AP_Failsafe_Init(void);

void AP_Failsafe_Update(void);

const AP_Failsafe_t *AP_Failsafe_Get(void);

uint8_t AP_Failsafe_IsActive(void);

void AP_Failsafe_SetRC(uint8_t state);

void AP_Failsafe_SetBattery(uint8_t state);

void AP_Failsafe_SetIMU(uint8_t state);

void AP_Failsafe_SetGPS(uint8_t state);

void AP_Failsafe_SetCompass(uint8_t state);

void AP_Failsafe_SetBarometer(uint8_t state);

void AP_Failsafe_SetEKF(uint8_t state);

void AP_Failsafe_SetMotor(uint8_t state);

AP_Failsafe_Type_t AP_Failsafe_GetReason(void);
AP_Failsafe_Action_t AP_Failsafe_GetAction(void);
#endif
