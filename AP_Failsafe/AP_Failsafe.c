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

static uint8_t last_state = 255;

/*----------------------------------------------------------------------------
 * Initialize
 *---------------------------------------------------------------------------*/

void AP_Failsafe_Init(void)
{
    failsafe.active = 0;

    failsafe.reason = FAILSAFE_NONE;

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

void AP_Failsafe_Update(void)
{
    failsafe.active = 0;

    failsafe.reason = FAILSAFE_NONE;

    if (failsafe.rc_lost)
    {
        failsafe.active = 1;
        failsafe.reason = FAILSAFE_RC;
    }

    else if (failsafe.battery_low)
    {
        failsafe.active = 1;
        failsafe.reason = FAILSAFE_BATTERY;
    }

    else if (failsafe.imu_failure)
    {
        failsafe.active = 1;
        failsafe.reason = FAILSAFE_IMU;
    }

    else if (failsafe.gps_failure)
    {
        failsafe.active = 1;
        failsafe.reason = FAILSAFE_GPS;
    }

    else if (failsafe.compass_failure)
    {
        failsafe.active = 1;
        failsafe.reason = FAILSAFE_COMPASS;
    }

    else if (failsafe.barometer_failure)
    {
        failsafe.active = 1;
        failsafe.reason = FAILSAFE_BAROMETER;
    }

    else if (failsafe.ekf_failure)
    {
        failsafe.active = 1;
        failsafe.reason = FAILSAFE_EKF;
    }

    else if (failsafe.motor_failure)
    {
        failsafe.active = 1;
        failsafe.reason = FAILSAFE_MOTOR;
    }

        AP_Debug_Print(DBG_FAILSAFE,
                       "\n===== FAILSAFE =====\n"
                       "Active : %u\n"
                       "Reason : %d\n",
                       failsafe.active,
                       failsafe.reason);

        last_state = failsafe.active;
    
}

/*----------------------------------------------------------------------------
 * Get State
 *---------------------------------------------------------------------------*/

const AP_Failsafe_t *AP_Failsafe_Get(void)
{
    return &failsafe;
}

uint8_t AP_Failsafe_IsActive(void)
{
    return failsafe.active;
}

AP_Failsafe_Type_t AP_Failsafe_GetReason(void)
{
    return failsafe.reason;
}
