
//------------------------------------------------------------------------------
// File    : AP_Sim.c
// Purpose : Simple Drone Physics Simulator
// Project : MiniPilot
//------------------------------------------------------------------------------

#include "AP_Sim.h"

/*---------------------------------------------------------------------------
 * Private Variables
 *---------------------------------------------------------------------------*/

// Roll angle (degrees)
static float roll = 0.0f;

// Roll rate (deg/sec)
static float roll_rate = 0.0f;

/*---------------------------------------------------------------------------
 * Initialize Simulator
 *---------------------------------------------------------------------------*/

void AP_Sim_Init(void)
{
    roll = 0.0f;
    roll_rate = 0.0f;
}

/*---------------------------------------------------------------------------
 * Update Simulator
 *---------------------------------------------------------------------------*/

void AP_Sim_Update(float roll_command,
                   float dt)
{
    /*---------------------------------------------------------------
     * Physics
     *
     * Roll Command
     *      ↓
     * Roll Acceleration
     *      ↓
     * Roll Rate
     *      ↓
     * Roll Angle
     *--------------------------------------------------------------*/

    /* Update roll rate */
    roll_rate += roll_command * dt;

    /* Simple damping to stop infinite acceleration */
    roll_rate *= 0.98f;

    /* Update roll angle */
    roll += roll_rate * dt;
}

/*---------------------------------------------------------------------------
 * Get Roll Angle
 *---------------------------------------------------------------------------*/

float AP_Sim_GetRoll(void)
{
    return roll;
}

/*---------------------------------------------------------------------------
 * Get Roll Rate
 *---------------------------------------------------------------------------*/

float AP_Sim_GetRollRate(void)
{
    return roll_rate;
}
