//------------------------------------------------------------------------------
// File    : AP_Motors.c
// Purpose : Motor Driver
// Project : MiniPilot
//------------------------------------------------------------------------------
//
// Receives motor commands from AP_Mixer.
//
// Current Target:
//      Linux Simulator
//
// Future Target:
//      STM32 PWM
//      ESC
//      Brushless Motors
//
//------------------------------------------------------------------------------

#include "AP_Motors.h"
#include "../AP_Config/AP_Config.h"
#include "../AP_Mixer/AP_Mixer.h"
#include "../AP_Arming/AP_Arming.h"
#include "AP_Debug/AP_Debug.h"
#include <stdio.h>
/*----------------------------------------------------------------------------
 * Private Variables
 *---------------------------------------------------------------------------*/

static AP_Motors_Output_t motors;
static uint8_t last_armed = 255;
/*----------------------------------------------------------------------------
 * Initialize
 *---------------------------------------------------------------------------*/

void AP_Motors_Init(void)
{
	for (int i = 0; i < 4; i++)
	{
		motors.motor[i] = MOTOR_MIN_OUTPUT ;
	}
}

/*----------------------------------------------------------------------------
 * Update
 *---------------------------------------------------------------------------*/

void AP_Motors_Update(void)
{
	uint8_t armed;
	const AP_Mixer_Output_t *mixer;

	armed = AP_Arming_IsArmed();
	mixer = AP_Mixer_GetOutput();

	if (armed != last_armed)
	{
		AP_Debug_Print(DBG_MOTORS,
				"\n===== MOTORS =====\n"
				"State : %s\n",
				armed ? "ARMED" : "DISARMED");

		last_armed = armed;
	}
	if (!armed)
	{
		for (int i = 0; i < 4; i++)
		{
			motors.motor[i] = MOTOR_MIN_OUTPUT  ;
		}

		return;
	}

	/* Vehicle is armed */

	for (int i = 0; i < 4; i++)
	{
		motors.motor[i] = mixer->motor[i];
	}
	/* Motor limits */
	for (int i = 0; i < 4; i++)
	{
		if (motors.motor[i] < MOTOR_MIN_OUTPUT )
			motors.motor[i] = MOTOR_MIN_OUTPUT ;

		if (motors.motor[i] > MOTOR_MAX_OUTPUT )
			motors.motor[i] = MOTOR_MAX_OUTPUT ;
	}
	AP_Debug_Print(DBG_MOTORS,
			"\n===== MOTORS =====\n"
			"M1 : %.2f\n"
			"M2 : %.2f\n"
			"M3 : %.2f\n"
			"M4 : %.2f\n",
			motors.motor[0],
			motors.motor[1],
			motors.motor[2],
			motors.motor[3]);

}

/*----------------------------------------------------------------------------
 * Get Outputs
 *---------------------------------------------------------------------------*/

const AP_Motors_Output_t *AP_Motors_GetOutput(void)
{
	return &motors;
}
