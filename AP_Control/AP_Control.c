//------------------------------------------------------------------------------
// File    : AP_Control.c
// Purpose : Flight Controller
// Project : MiniPilot
//------------------------------------------------------------------------------

#include "AP_Control.h"

#include "../AP_PID/AP_PID.h"
#include "../AP_Vehicle/AP_Vehicle.h"
#include "../AP_Sim/AP_Sim.h"

#include <stdio.h>

/*---------------------------------------------------------------------------
 * Private Variables
 *---------------------------------------------------------------------------*/
/* Roll PID */
static AP_PID_t roll_pid;

/* Latest controller outputs */
static AP_Control_Output_t control_output;

/* Desired roll angle */
static float desired_roll = 20.0f;


void AP_Control_Init(void)
{
    AP_PID_Init(&roll_pid,
                2.0f,
                0.05f,
                0.1f);
}

void AP_Control_Update(float dt)
{
    float current_roll;
    float pitch;
    float yaw;

    float pid_output;

    /* Read estimated attitude */
    AP_Vehicle_Get_Attitude(&current_roll,
                            &pitch,
                            &yaw);

    /* PID controller */
    pid_output =
        AP_PID_Update(&roll_pid,
                      desired_roll,
                      current_roll,
                      dt);

    /* Store controller outputs */
control_output.roll_output = pid_output;
control_output.pitch_output = 0.0f;
control_output.yaw_output = 0.0f;
control_output.throttle_output = 0.5f;

    /* Send command to simulator */
    AP_Sim_Update(pid_output,
                  dt);

/*    printf("Desired : %6.2f  "
           "Current : %6.2f  "
           "PID : %7.2f\n",
           desired_roll,
           current_roll,
           pid_output);

*/
printf("Roll = %.2f  Rate = %.2f  PID = %.2f\n",
       AP_Sim_GetRoll(),
       AP_Sim_GetRollRate(),
       pid_output);

}


/*---------------------------------------------------------------------------
 * Get Control Outputs
 *---------------------------------------------------------------------------*/
const AP_Control_Output_t *AP_Control_GetOutput(void)
{
    return &control_output;
}
