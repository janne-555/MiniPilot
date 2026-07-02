//------------------------------------------------------------------------------
// File    : AP_FlightMode.c
// Purpose : Flight Mode Manager
// Project : MiniPilot
//------------------------------------------------------------------------------

#include "AP_FlightMode.h"
#include "../AP_Config/AP_Config.h"
#include "../AP_RC/AP_RC.h"
#include "AP_Debug/AP_Debug.h"
/*---------------------------------------------------------------------------
 * Private Variables
 *---------------------------------------------------------------------------*/

static AP_FlightMode_t current_mode;

/* Desired aircraft attitude */
static float desired_roll;
static float desired_pitch;
static float desired_yaw;
static float desired_throttle;

/*---------------------------------------------------------------------------
 * Initialize
 *---------------------------------------------------------------------------*/

void AP_FlightMode_Init(void)
{
	current_mode = FLIGHTMODE_STABILIZE;

	desired_roll = 20.0f;
	desired_pitch = 0.0f;
	desired_yaw = 0.0f;
	desired_throttle = 50.0f;
}

/*---------------------------------------------------------------------------
 * Update
 *---------------------------------------------------------------------------*/

void AP_FlightMode_Update(void)
{
	const AP_RC_t *rc;

	rc = AP_RC_Get();
	switch(current_mode)
	{
		case FLIGHTMODE_STABILIZE:

			/* Temporary fixed commands */
			desired_roll = rc->roll * MAX_ROLL_ANGLE;
			desired_pitch = rc->pitch * MAX_PITCH_ANGLE;
			desired_yaw = rc->yaw * MAX_YAW_RATE;
			desired_throttle = rc->throttle;

			AP_Debug_Print(DBG_FLIGHTMODE,
					"\n===== FLIGHT MODE =====\n"
					"Mode           : %d\n"
					"Stick Roll     : %.2f\n"
					"Desired Roll   : %.2f\n"
					"Desired Pitch  : %.2f\n"
					"Throttle       : %.2f\n",
					current_mode,
					rc->roll,
					desired_roll,
					desired_pitch,
					desired_throttle);
			break;

		case FLIGHTMODE_ACRO:

			/* Placeholder */
			break;

		case FLIGHTMODE_ALTHOLD:

			/* Placeholder */
			break;

		case FLIGHTMODE_LOITER:

			/* Placeholder */
			break;

		case FLIGHTMODE_AUTO:

			/* Placeholder */
			break;

		case FLIGHTMODE_RTL:

			/* Placeholder */
			break;
	}
}

/*---------------------------------------------------------------------------
 * Mode Functions
 *---------------------------------------------------------------------------*/

void AP_FlightMode_SetMode(AP_FlightMode_t mode)
{
	current_mode = mode;
}

AP_FlightMode_t AP_FlightMode_GetMode(void)
{
	return current_mode;
}

/*---------------------------------------------------------------------------
 * Desired Commands
 *---------------------------------------------------------------------------*/

float AP_FlightMode_GetRoll(void)
{
	return desired_roll;
}

float AP_FlightMode_GetPitch(void)
{
	return desired_pitch;
}

float AP_FlightMode_GetYaw(void)
{
	return desired_yaw;
}

float AP_FlightMode_GetThrottle(void)
{
	return desired_throttle;
}
