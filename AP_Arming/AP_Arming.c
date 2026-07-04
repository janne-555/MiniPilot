//------------------------------------------------------------------------------
// File    : AP_Arming.c
// Purpose : Vehicle Arming
// Project : MiniPilot
//------------------------------------------------------------------------------

#include "AP_Arming.h"
#include "../AP_Failsafe/AP_Failsafe.h"
#include "AP_Debug/AP_Debug.h"
#include <stdio.h>

static uint8_t last_armed = 255;
static uint8_t last_prearm = 255;
static uint8_t last_failsafe = 255;
/*---------------------------------------------------------------------------
 * Private Variable
 *--------------------------------------------------------------------------*/

static AP_Arming_t arming;
/*---------------------------------------------------------------------------
 * Initialize
 *--------------------------------------------------------------------------*/
void AP_Arming_Init(void)
{
	arming.armed = 0;

	/* Simulator */
	arming.pre_arm_ok = 1;
	arming.gyro_ok = 1;
	arming.accel_ok = 1;
	arming.compass_ok = 1;
	arming.gps_ok = 1;
	arming.battery_ok = 1;
	arming.rc_ok = 1;
	arming.failsafe = 0;
}

void AP_Arming_Update(void)
{
        /*
         * Read system safety status
         */
        arming.failsafe =
                AP_Failsafe_IsActive();


        /*
         * Battery status comes from failsafe decision
         */
        if (AP_Failsafe_GetReason() ==
                        FAILSAFE_BATTERY)
        {
                arming.battery_ok = 0;
        }
        else
        {
                arming.battery_ok = 1;
        }



        /*
         * Pre arm checks
         */
        if (arming.gyro_ok &&
            arming.accel_ok &&
            arming.rc_ok &&
            arming.battery_ok &&
            !arming.failsafe)
        {
                arming.pre_arm_ok = 1;
        }
        else
        {
                arming.pre_arm_ok = 0;
        }

if ((arming.armed != last_armed) ||
    (arming.pre_arm_ok != last_prearm) ||
    (arming.failsafe != last_failsafe))
{

    AP_Debug_Print(DBG_ARMING,
        "\n===== ARMING =====\n"
        "Armed      : %u\n"
        "PreArm OK  : %u\n"
        "Gyro OK    : %u\n"
        "Accel OK   : %u\n"
        "Compass OK : %u\n"
        "GPS OK     : %u\n"
        "Battery OK : %u\n"
        "RC OK      : %u\n"
        "Failsafe   : %u\n",
        arming.armed,
        arming.pre_arm_ok,
        arming.gyro_ok,
        arming.accel_ok,
        arming.compass_ok,
        arming.gps_ok,
        arming.battery_ok,
        arming.rc_ok,
        arming.failsafe);


    last_armed = arming.armed;
    last_prearm = arming.pre_arm_ok;
    last_failsafe = arming.failsafe;
}

}

/*---------------------------------------------------------------------------
 * Arm
 *--------------------------------------------------------------------------*/
void AP_Arming_Arm(void)
{
	if (!arming.pre_arm_ok)
	{
		AP_Debug_Print(DBG_ARMING,
				"\n===== ARMING =====\n"
				"Cannot Arm!\n");
		return;
	}

	arming.armed = 1;
	AP_Debug_Print(DBG_ARMING,
			"\n===== ARMING =====\n"
			"*** VEHICLE ARMED ***\n");
}
/*---------------------------------------------------------------------------
 * Disarm
 *--------------------------------------------------------------------------*/
void AP_Arming_Disarm(void)
{
	arming.armed = 0;
	AP_Debug_Print(DBG_ARMING,
			"\n===== ARMING =====\n"
			"*** VEHICLE DISARMED ***\n");
}

void AP_Arming_Toggle(void)
{
	if (arming.armed)
	{
		AP_Arming_Disarm();
	}
	else
	{
		AP_Arming_Arm();
	}
}

const AP_Arming_t *AP_Arming_Get(void)
{
	return &arming;
}
/*---------------------------------------------------------------------------
 * Status
 *--------------------------------------------------------------------------*/
uint8_t AP_Arming_IsArmed(void)
{
	return arming.armed;
}
