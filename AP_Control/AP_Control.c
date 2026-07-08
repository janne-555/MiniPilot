//------------------------------------------------------------------------------
// File    : AP_Control.c
// Purpose : Flight Controller
// Project : MiniPilot
//------------------------------------------------------------------------------

#include "AP_Control.h"
#include "../AP_FlightMode/AP_FlightMode.h"
#include "../AP_PID/AP_PID.h"
#include "../AP_Sim/AP_Sim.h"
#include "../AP_Vehicle/AP_Vehicle.h"
#include "AP_Debug/AP_Debug.h"

#include <stdio.h>
static float last_error = 999.0f;
static float last_pid = 999.0f;
/*---------------------------------------------------------------------------
 * Private Variables
 *---------------------------------------------------------------------------*/
/* Roll PID */
static AP_PID_t roll_pid;

/* Latest controller outputs */
static AP_Control_Output_t control_output;

void AP_Control_Init(void) { AP_PID_Init(&roll_pid, 2.0f, 0.05f, 0.1f); }

void AP_Control_Update(float dt) {
  float current_roll;
  float pitch;
  float yaw;

  float pid_output;

  float desired_roll;

  desired_roll = AP_FlightMode_GetRoll();

  /* Read estimated attitude */
  AP_Vehicle_Get_Attitude(&current_roll, &pitch, &yaw);

  /* PID controller */
  pid_output = AP_PID_Update(&roll_pid, desired_roll, current_roll, dt);

  /* Store controller outputs */
  control_output.roll_output = pid_output;
  control_output.pitch_output = 0.0f;
  control_output.yaw_output = 0.0f;
  control_output.throttle_output = 0.5f;

  if ((pid_output - last_pid > 0.5f) || (last_pid - pid_output > 0.5f)) {
    AP_Debug_Print(DBG_CONTROL,
                   "\n===== CONTROL =====\n"
                   "Desired Roll : %.2f\n"
                   "Current Roll : %.2f\n"
                   "Error        : %.2f\n"
                   "PID Output   : %.2f\n",
                   desired_roll, current_roll, desired_roll - current_roll,
                   pid_output);
    last_pid = pid_output;
  }
}
/*---------------------------------------------------------------------------
 * Get Control Outputs
 *---------------------------------------------------------------------------*/
const AP_Control_Output_t *AP_Control_GetOutput(void) {
  return &control_output;
}
