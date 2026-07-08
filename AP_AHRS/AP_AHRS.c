//------------------------------------------------------------------------------
// File    : AP_AHRS.c
// Purpose : Attitude Estimator
// Project : MiniPilot
//------------------------------------------------------------------------------

#include "AP_AHRS.h"

#include "../AP_Config/AP_Config.h"

#include "../AP_IMU/AP_IMU.h"

#include "../AP_Debug/AP_Debug.h"

#include <math.h>

#define RAD_TO_DEG 57.2957795f

/*----------------------------------------------------------------------------
 * Private Variables
 *---------------------------------------------------------------------------*/

static AP_AHRS_t ahrs;

/*
 * Debug control
 */

static float last_roll = 999.0f;

static float last_pitch = 999.0f;

static float last_yaw = 999.0f;

/*----------------------------------------------------------------------------
 * Initialize
 *---------------------------------------------------------------------------*/

void AP_AHRS_Init(void)
{
    ahrs.roll = 0.0f;

  ahrs.pitch = 0.0f;

  ahrs.yaw = 0.0f;

  ahrs.healthy = 0;
}

/*----------------------------------------------------------------------------
 * Update
 *---------------------------------------------------------------------------*/

void AP_AHRS_Update(void) {

  const AP_IMU_t *imu;

  imu = AP_IMU_Get();

  /*
   * IMU health check
   */

  if (!imu->healthy) {

    ahrs.healthy = 0;

    return;
  }

  ahrs.healthy = 1;

  /*
   * Accelerometer attitude
   */

  float roll_acc;

  float pitch_acc;

  roll_acc = atan2f(imu->ay, imu->az);

  pitch_acc = atan2f(-imu->ax,

                     sqrtf(

                         imu->ay * imu->ay +

                         imu->az * imu->az));

  roll_acc *= RAD_TO_DEG;

  pitch_acc *= RAD_TO_DEG;

  /*
   * Gyro prediction
   */

  ahrs.roll +=

      imu->gx * LOOP_DT;

  ahrs.pitch +=

      imu->gy * LOOP_DT;

  ahrs.yaw +=

      imu->gz * LOOP_DT;

  /*
   * Complementary filter
   *
   * gyro + accel fusion
   */

  ahrs.roll =

      AHRS_ALPHA * ahrs.roll +

      AHRS_BETA * roll_acc;

  ahrs.pitch =

      AHRS_ALPHA * ahrs.pitch +

      AHRS_BETA * pitch_acc;

  /*
   * Debug only when attitude changes
   */

  if ((fabsf(ahrs.roll - last_roll) > 1.0f) ||

      (fabsf(ahrs.pitch - last_pitch) > 1.0f) ||

      (fabsf(ahrs.yaw - last_yaw) > 1.0f))

  {

    AP_Debug_Print(DBG_AHRS,

                   "\n===== AHRS =====\n"

                   "Roll    : %.2f\n"

                   "Pitch   : %.2f\n"

                   "Yaw     : %.2f\n"

                   "Healthy : %u\n",

                   ahrs.roll,

                   ahrs.pitch,

                   ahrs.yaw,

                   ahrs.healthy);

    last_roll = ahrs.roll;

    last_pitch = ahrs.pitch;

    last_yaw = ahrs.yaw;
  }
}

/*----------------------------------------------------------------------------
 * Getters
 *---------------------------------------------------------------------------*/

float AP_AHRS_GetRoll(void)
{
    return ahrs.roll;
}

float AP_AHRS_GetPitch(void)
{
    return ahrs.pitch;
}

float AP_AHRS_GetYaw(void)
{
    return ahrs.yaw;
}

uint8_t AP_AHRS_IsHealthy(void)
{
    return ahrs.healthy;
}

const AP_AHRS_t *AP_AHRS_Get(void) { return &ahrs; }
