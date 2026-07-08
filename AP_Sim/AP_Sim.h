//------------------------------------------------------------------------------
// File    : AP_Sim.h
// Purpose : Drone Physics Simulator
// Project : MiniPilot
//------------------------------------------------------------------------------

#ifndef AP_SIM_H
#define AP_SIM_H

/*----------------------------------------------------------------------------
 * Simulator State
 *---------------------------------------------------------------------------*/

typedef struct {
  /* Attitude (degrees) */
  float roll;
  float pitch;
  float yaw;

  /* Angular Velocity (deg/sec) */
  float roll_rate;
  float pitch_rate;
  float yaw_rate;

  /* Angular Acceleration (deg/sec²) */
  float roll_accel;
  float pitch_accel;
  float yaw_accel;

} AP_Sim_State_t;

/*----------------------------------------------------------------------------
 * API
 *---------------------------------------------------------------------------*/

void AP_Sim_Init(void);

void AP_Sim_Update(float dt);

const AP_Sim_State_t *AP_Sim_GetState(void);

#endif
