//------------------------------------------------------------------------------
// File    : AP_FlightMode.c
// Purpose : Flight Mode Manager
// Project : MiniPilot
//------------------------------------------------------------------------------

#include "AP_FlightMode.h"

#include "../AP_Config/AP_Config.h"
#include "../AP_RC/AP_RC.h"
#include "../AP_Failsafe/AP_Failsafe.h"
#include "../AP_Debug/AP_Debug.h"
#include "../AP_PosControl/AP_PosControl.h"
#include "../AP_InertialNav/AP_InertialNav.h"

/*---------------------------------------------------------------------------
 * Private Variables
 *---------------------------------------------------------------------------*/

static AP_FlightMode_State_t flight_mode;


static AP_FlightMode_t last_mode = 255;


/*---------------------------------------------------------------------------
 * Initialize
 *---------------------------------------------------------------------------*/

void AP_FlightMode_Init(void)
{
	flight_mode.mode = FLIGHTMODE_STABILIZE;

	flight_mode.reason = MODE_REASON_SYSTEM;


	flight_mode.desired_roll = 0.0f;

	flight_mode.desired_pitch = 0.0f;

	flight_mode.desired_yaw = 0.0f;

	flight_mode.desired_throttle = 0.0f;
}


/*---------------------------------------------------------------------------
 * Update
 *---------------------------------------------------------------------------*/

void AP_FlightMode_Update(void)
{
	const AP_RC_t *rc;


	/*
	 * Failsafe has highest priority
	 */

	if (AP_Failsafe_IsActive())
	{
		switch(AP_Failsafe_GetAction())
		{

			case FAILSAFE_ACTION_RTL:

				AP_FlightMode_SetMode(
						FLIGHTMODE_RTL,
						MODE_REASON_FAILSAFE);

				break;


			case FAILSAFE_ACTION_LAND:

				AP_FlightMode_SetMode(
						FLIGHTMODE_LAND,
						MODE_REASON_FAILSAFE);

				break;


			case FAILSAFE_ACTION_HOLD:

				AP_FlightMode_SetMode(
						FLIGHTMODE_ALTHOLD,
						MODE_REASON_FAILSAFE);

				break;


			case FAILSAFE_ACTION_DISARM:

				AP_FlightMode_SetMode(
						FLIGHTMODE_FAILSAFE,
						MODE_REASON_FAILSAFE);

				break;


			default:
				break;
		}
	}


	rc = AP_RC_Get();



	switch(flight_mode.mode)
	{

		/*----------------------------------------------------
		 * Stabilize
		 *---------------------------------------------------*/

		case FLIGHTMODE_STABILIZE:


			flight_mode.desired_roll =
				rc->roll * MAX_ROLL_ANGLE;


			flight_mode.desired_pitch =
				rc->pitch * MAX_PITCH_ANGLE;


			flight_mode.desired_yaw =
				rc->yaw * MAX_YAW_RATE;


			flight_mode.desired_throttle =
				rc->throttle;


			break;



			/*----------------------------------------------------
			 * Acro
			 *---------------------------------------------------*/

		case FLIGHTMODE_ACRO:


			flight_mode.desired_roll =
				rc->roll * MAX_ROLL_RATE;


			flight_mode.desired_pitch =
				rc->pitch * MAX_PITCH_RATE;


			flight_mode.desired_yaw =
				rc->yaw * MAX_YAW_RATE;


			flight_mode.desired_throttle =
				rc->throttle;


			break;



			/*----------------------------------------------------
			 * Land
			 *---------------------------------------------------*/

		case FLIGHTMODE_LAND:


			flight_mode.desired_roll = 0.0f;


			flight_mode.desired_pitch = 0.0f;


			flight_mode.desired_yaw = 0.0f;



			/*
			 * descend slowly
			 */

			float land_target;

			land_target =
				AP_InertialNav_GetAltitude()
				-
				0.5f;


			if (land_target < 0.0f)
			{
				land_target = 0.0f;
			}


			AP_PosControl_SetAltTarget(
					land_target
					);




			flight_mode.desired_throttle =

				AP_PosControl_GetThrottle();



			break;


			/*----------------------------------------------------
			 * RTL
			 *---------------------------------------------------*/

		case FLIGHTMODE_RTL:


			/*
			 * Placeholder until navigation
			 */

			flight_mode.desired_roll = 0.0f;

			flight_mode.desired_pitch = 0.0f;

			flight_mode.desired_yaw = 0.0f;


			break;



		case FLIGHTMODE_ALTHOLD:

			flight_mode.desired_roll =
				rc->roll * MAX_ROLL_ANGLE;


			flight_mode.desired_pitch =
				rc->pitch * MAX_PITCH_ANGLE;


			flight_mode.desired_yaw =
				rc->yaw * MAX_YAW_RATE;


			flight_mode.desired_throttle =
				AP_PosControl_GetThrottle();


			break;

		case FLIGHTMODE_LOITER:

		case FLIGHTMODE_AUTO:

		case FLIGHTMODE_FAILSAFE:

		default:

			break;
	}



	/*
	 * Debug only when mode changes
	 */

	if(last_mode != flight_mode.mode)
	{
		AP_Debug_Print(DBG_FLIGHTMODE,

				"\n===== FLIGHT MODE =====\n"
				"Mode   : %d\n"
				"Reason : %d\n",

				flight_mode.mode,
				flight_mode.reason);


		last_mode = flight_mode.mode;
	}

}


/*---------------------------------------------------------------------------
 * Set Mode
 *---------------------------------------------------------------------------*/

void AP_FlightMode_SetMode(AP_FlightMode_t mode,
		AP_FlightMode_Reason_t reason)
{
	if (flight_mode.mode == mode)
	{
		return;
	}


	flight_mode.mode = mode;

	flight_mode.reason = reason;



	switch(mode)
	{

		case FLIGHTMODE_STABILIZE:

			AP_PosControl_Enable(0);

			break;



		case FLIGHTMODE_ALTHOLD:


			AP_PosControl_Enable(1);


			AP_PosControl_SetAltTarget(
					AP_InertialNav_GetAltitude()
					);


			break;



		case FLIGHTMODE_LAND:


			AP_PosControl_Enable(1);


			AP_PosControl_SetAltTarget(
					AP_InertialNav_GetAltitude()
					);


			break;



		default:

			break;
	}
}

/*---------------------------------------------------------------------------
 * Get Mode
 *---------------------------------------------------------------------------*/

AP_FlightMode_t AP_FlightMode_GetMode(void)
{
	return flight_mode.mode;
}


/*---------------------------------------------------------------------------
 * Desired Outputs
 *---------------------------------------------------------------------------*/

float AP_FlightMode_GetRoll(void)
{
	return flight_mode.desired_roll;
}


float AP_FlightMode_GetPitch(void)
{
	return flight_mode.desired_pitch;
}


float AP_FlightMode_GetYaw(void)
{
	return flight_mode.desired_yaw;
}


float AP_FlightMode_GetThrottle(void)
{
	return flight_mode.desired_throttle;
}


/*---------------------------------------------------------------------------
 * Full State
 *---------------------------------------------------------------------------*/

const AP_FlightMode_State_t *AP_FlightMode_GetState(void)
{
	return &flight_mode;
}
