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

typedef enum
{
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

/*----------------------------------------------------------------------------
 * Failsafe State
 *---------------------------------------------------------------------------*/

typedef struct
{
    uint8_t active;

    AP_Failsafe_Type_t reason;

    uint8_t rc_lost;

    uint8_t battery_low;

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

AP_Failsafe_Type_t AP_Failsafe_GetReason(void);

#endif
