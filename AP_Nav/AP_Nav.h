//------------------------------------------------------------------------------
// File    : AP_Nav.h
// Purpose : Navigation Controller
// Project : MiniPilot
//------------------------------------------------------------------------------

#ifndef AP_NAV_H
#define AP_NAV_H

#include <stdint.h>

typedef struct {
  /*
   * Home position
   */

  double home_lat;

  double home_lon;

  /*
   * Target position
   */

  double target_lat;

  double target_lon;

  /*
   * Current position
   */

  double current_lat;

  double current_lon;

  /*
   * Navigation data
   */

  float distance;

  float bearing;

  float error_x;

  float error_y;

  /*
   * Output to attitude controller
   */

  float target_roll;

  float target_pitch;

  uint8_t home_set;

  uint8_t active;

} AP_Nav_t;

void AP_Nav_Init(void);

void AP_Nav_Update(void);

void AP_Nav_SetHome(void);

void AP_Nav_SetTarget(double lat, double lon);

void AP_Nav_Enable(uint8_t enable);

float AP_Nav_GetDistance(void);

float AP_Nav_GetBearing(void);

float AP_Nav_GetRollTarget(void);

float AP_Nav_GetPitchTarget(void);

const AP_Nav_t *AP_Nav_Get(void);

#endif
