//------------------------------------------------------------------------------
// File    : AP_InertialNav.h
// Purpose : Position Estimator
// Project : MiniPilot
//------------------------------------------------------------------------------

#ifndef AP_INERTIALNAV_H
#define AP_INERTIALNAV_H

#include <stdint.h>

typedef struct {
  /*
   * Position
   */

  float altitude;

  double latitude;

  double longitude;

  /*
   * Velocity
   */

  float velocity_x;

  float velocity_y;

  float velocity_z;

  /*
   * Health
   */

  uint8_t healthy;

} AP_InertialNav_t;

void AP_InertialNav_Init(void);

void AP_InertialNav_Update(float dt);

float AP_InertialNav_GetAltitude(void);

float AP_InertialNav_GetVelocityZ(void);

double AP_InertialNav_GetLatitude(void);

double AP_InertialNav_GetLongitude(void);

const AP_InertialNav_t *AP_InertialNav_Get(void);

#endif
