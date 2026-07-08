//------------------------------------------------------------------------------
// File    : AP_IMU.c
// Purpose : IMU Driver
// Project : MiniPilot
//------------------------------------------------------------------------------

#include "AP_IMU.h"
#include "../AP_Debug/AP_Debug.h"
#include "../AP_Sim/AP_Sim.h"
#include <math.h>
#define DEG_TO_RAD 0.0174532925f
static AP_IMU_t imu;
static float last_gx = 999.0f;

void AP_IMU_Init(void)
{
    imu.gx = 0.0f;
  imu.gy = 0.0f;
  imu.gz = 0.0f;

  imu.ax = 0.0f;
  imu.ay = 0.0f;
  imu.az = 9.81f;

  imu.healthy = 1;
}
void AP_IMU_Update(void) {
  const AP_Sim_State_t *sim;

  float roll_rad;

  /* Read simulator state */
  sim = AP_Sim_GetState();

  /* Convert degrees to radians */
  roll_rad = sim->roll * DEG_TO_RAD;

  /*----------------------------------------------------------
   * Gyroscope
   *
   * Measures angular velocity
   *---------------------------------------------------------*/

  imu.gx = sim->roll_rate;
  imu.gy = sim->pitch_rate;
  imu.gz = sim->yaw_rate;

  /*----------------------------------------------------------
   * Accelerometer
   *
   * Measures gravity components
   *---------------------------------------------------------*/

  imu.ax = 0.0f;

  imu.ay = 9.81f * sinf(roll_rad);

  imu.az = 9.81f * cosf(roll_rad);

  /* Sensor healthy */

  imu.healthy = 1;

  if ((imu.gx - last_gx > 1.0f) || (last_gx - imu.gx > 1.0f)) {
    AP_Debug_Print(DBG_IMU,
                   "\n===== IMU =====\n"
                   "GX : %.2f\n"
                   "GY : %.2f\n"
                   "GZ : %.2f\n"
                   "AX : %.2f\n"
                   "AY : %.2f\n"
                   "AZ : %.2f\n",
                   imu.gx, imu.gy, imu.gz, imu.ax, imu.ay, imu.az);

    last_gx = imu.gx;
  }
}

const AP_IMU_t *AP_IMU_Get(void) { return &imu; }
