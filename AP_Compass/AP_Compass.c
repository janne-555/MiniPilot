//------------------------------------------------------------------------------
// File    : AP_Compass.c
// Purpose : Compass / Magnetometer Manager
// Project : MiniPilot
//------------------------------------------------------------------------------

#include "AP_Compass.h"

#include "../AP_Debug/AP_Debug.h"

#include <math.h>

#define RAD_TO_DEG 57.2957795f

static AP_Compass_t compass;

static uint32_t debug_counter = 0;

void AP_Compass_Init(void) {
  compass.mag_x = 100.0f;
  compass.mag_y = 0.0f;
  compass.mag_z = 40.0f;

  compass.offset_x = 0.0f;
  compass.offset_y = 0.0f;
  compass.offset_z = 0.0f;

  compass.field_x = 0.0f;
  compass.field_y = 0.0f;
  compass.field_z = 0.0f;

  compass.heading = 0.0f;

  compass.calibrated = 1;

  compass.healthy = 1;
}

void AP_Compass_Update(void) {

  /*
   * Simulation magnetometer
   *
   * Later replace this section with:
   *
   * HMC5883
   * QMC5883
   * IST8310
   * RM3100
   *
   */

  compass.mag_x += 0.01f;

  if (compass.mag_x > 110.0f) {
    compass.mag_x = 100.0f;
  }

  /*
   * Apply calibration
   */

  compass.field_x = compass.mag_x - compass.offset_x;

  compass.field_y = compass.mag_y - compass.offset_y;

  compass.field_z = compass.mag_z - compass.offset_z;

  /*
   * Heading calculation
   */

  compass.heading = atan2f(compass.field_y, compass.field_x) * RAD_TO_DEG;

  if (compass.heading < 0) {
    compass.heading += 360.0f;
  }

  /*
   * Health check
   */

  if (compass.field_x == 0 && compass.field_y == 0) {
    compass.healthy = 0;
  } else {
    compass.healthy = 1;
  }

  /*
   * Debug slow print
   */

  debug_counter++;

  if (debug_counter >= 100) {
    debug_counter = 0;

    AP_Debug_Print(DBG_COMPASS,

                   "\n===== COMPASS =====\n"
                   "MAG X   : %.2f\n"
                   "MAG Y   : %.2f\n"
                   "MAG Z   : %.2f\n"
                   "Heading : %.2f\n"
                   "Health  : %d\n",

                   compass.field_x, compass.field_y, compass.field_z,
                   compass.heading, compass.healthy);
  }
}

void AP_Compass_Calibrate(void) {
  compass.offset_x = compass.mag_x;

  compass.offset_y = compass.mag_y;

  compass.offset_z = compass.mag_z;

  compass.calibrated = 1;
}

const AP_Compass_t *AP_Compass_Get(void) { return &compass; }

float AP_Compass_GetHeading(void) { return compass.heading; }

float AP_Compass_GetMagX(void) { return compass.field_x; }

float AP_Compass_GetMagY(void) { return compass.field_y; }

float AP_Compass_GetMagZ(void) { return compass.field_z; }

uint8_t AP_Compass_IsHealthy(void) { return compass.healthy; }
