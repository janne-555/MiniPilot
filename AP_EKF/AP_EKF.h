//------------------------------------------------------------------------------
// File    : AP_EKF.h
// Purpose : Extended Kalman Filter
// Project : MiniPilot
//------------------------------------------------------------------------------

#ifndef AP_EKF_H
#define AP_EKF_H

#include <stdint.h>

/*----------------------------------------------------------------------------
 * EKF State
 *---------------------------------------------------------------------------*/

typedef struct {
  /*
   * Attitude estimate
   */

  float roll;

  float pitch;

  float yaw;

  /*
   * Position estimate
   */

  double latitude;

  double longitude;

  float altitude;

  /*
   * Velocity estimate
   */

  float velocity_z;

  /*
   * Sensor status
   */

  uint8_t imu_ok;

  uint8_t gps_ok;

  uint8_t baro_ok;

  uint8_t compass_ok;

  uint8_t healthy;

} AP_EKF_t;

/*----------------------------------------------------------------------------
 * API
 *---------------------------------------------------------------------------*/

void AP_EKF_Init(void);

void AP_EKF_Update(float dt);

float AP_EKF_GetRoll(void);

float AP_EKF_GetPitch(void);

float AP_EKF_GetYaw(void);

double AP_EKF_GetLatitude(void);

double AP_EKF_GetLongitude(void);

float AP_EKF_GetAltitude(void);

float AP_EKF_GetVelocityZ(void);

uint8_t AP_EKF_CompassHealthy(void);

uint8_t AP_EKF_IsHealthy(void);

const AP_EKF_t *AP_EKF_Get(void);

#endif
