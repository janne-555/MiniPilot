//------------------------------------------------------------------------------
// File    : AP_Sim.c
// Purpose : Drone Physics Simulator
// Project : MiniPilot
//------------------------------------------------------------------------------

#include "AP_Sim.h"
#include "AP_Debug/AP_Debug.h"
#include "../AP_Motors/AP_Motors.h"

/*----------------------------------------------------------------------------
 * Private Variables
 *---------------------------------------------------------------------------*/

static AP_Sim_State_t sim;

/* Moment of inertia (simulation constant) */
static const float inertia = 10.0f;

/*----------------------------------------------------------------------------
 * Initialize
 *---------------------------------------------------------------------------*/

void AP_Sim_Init(void)
{
	sim.roll = 0.0f;
	sim.pitch = 0.0f;
	sim.yaw = 0.0f;

	sim.roll_rate = 0.0f;
	sim.pitch_rate = 0.0f;
	sim.yaw_rate = 0.0f;

	sim.roll_accel = 0.0f;
	sim.pitch_accel = 0.0f;
	sim.yaw_accel = 0.0f;
}

/*----------------------------------------------------------------------------
 * Update Physics
 *---------------------------------------------------------------------------*/

void AP_Sim_Update(float dt)
{
	const AP_Motors_Output_t *motor;

	float roll_torque;

	motor = AP_Motors_GetOutput();

	/*--------------------------------------------------------------
	 * Roll Torque
	 *
	 *      Front
	 *
	 *   M1       M2
	 *
	 *   M4       M3
	 *
	 *       Back
	 *
	 * Left Motors  : M1 M4
	 * Right Motors : M2 M3
	 *-------------------------------------------------------------*/

roll_torque =
    (motor->motor[0] + motor->motor[3]) -
    (motor->motor[1] + motor->motor[2]);
	/*--------------------------------------------------------------
	 * Newton's Law
	 *
	 * Torque = Inertia × Angular Acceleration
	 *-------------------------------------------------------------*/

	sim.roll_accel = roll_torque / inertia;

	/* Update angular velocity */

	sim.roll_rate += sim.roll_accel * dt;

	/* Air resistance */

	sim.roll_rate *= 0.995f;

	/* Update angle */

	sim.roll += sim.roll_rate * dt;

	AP_Debug_Print(DBG_SIM,
			"\n===== SIM =====\n"
			"Roll      : %.2f\n"
			"Roll Rate : %.2f\n",
			sim.roll,
			sim.roll_rate);
}

/*----------------------------------------------------------------------------
 * Get Simulator State
 *---------------------------------------------------------------------------*/

const AP_Sim_State_t *AP_Sim_GetState(void)
{
	return &sim;
}
