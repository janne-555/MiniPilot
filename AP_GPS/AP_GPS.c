//------------------------------------------------------------------------------
// File    : AP_GPS.c
// Purpose : GPS Manager
// Project : MiniPilot
//------------------------------------------------------------------------------

#include "AP_GPS.h"

#include "../AP_Debug/AP_Debug.h"

#include "../AP_Failsafe/AP_Failsafe.h"

/*----------------------------------------------------------------------------
 Private
----------------------------------------------------------------------------*/

static AP_GPS_t gps;

static uint8_t last_fix = 255;

/*----------------------------------------------------------------------------
 Init
----------------------------------------------------------------------------*/

void AP_GPS_Init(void)
{
    /*
   * Simulator position
   */

  gps.latitude = 17.385044;

  gps.longitude = 78.486671;

  gps.altitude = 100.0f;

  gps.ground_speed = 0.0f;

  gps.course = 0.0f;

  gps.satellites = 10;

  gps.fix = GPS_FIX_3D;

  gps.healthy = 1;
}

/*----------------------------------------------------------------------------
 Update
----------------------------------------------------------------------------*/

void AP_GPS_Update(void) {

  /*
   * Simulation movement
   *
   * Later:
   * UART NMEA/UBX parser
   */

  gps.latitude += 0.00000001;

  gps.longitude += 0.00000001;

  /*
   * Health check
   */

  if (gps.fix == GPS_FIX_NONE || gps.satellites < 5) {
    gps.healthy = 0;

    AP_Failsafe_SetGPS(1);
  } else {
    gps.healthy = 1;

    AP_Failsafe_SetGPS(0);
  }

  /*
   * Debug only when fix changes
   */

  if (last_fix != gps.fix) {
    AP_Debug_Print(DBG_GPS,

                   "\n===== GPS =====\n"
                   "Fix       : %d\n"
                   "Sat       : %u\n"
                   "Lat       : %.7lf\n"
                   "Lon       : %.7lf\n"
                   "Alt       : %.2f\n",

                   gps.fix,

                   gps.satellites,

                   gps.latitude,

                   gps.longitude,

                   gps.altitude);

    last_fix = gps.fix;
  }
}

/*----------------------------------------------------------------------------
 Getters
----------------------------------------------------------------------------*/

const AP_GPS_t *AP_GPS_Get(void) { return &gps; }

double AP_GPS_GetLatitude(void)
{
    return gps.latitude;
}

double AP_GPS_GetLongitude(void)
{
    return gps.longitude;
}

float AP_GPS_GetAltitude(void)
{
    return gps.altitude;
}

float AP_GPS_GetGroundSpeed(void)
{
    return gps.ground_speed;
}

float AP_GPS_GetCourse(void)
{
    return gps.course;
}

uint8_t AP_GPS_GetSatellites(void)
{
    return gps.satellites;
}

uint8_t AP_GPS_IsHealthy(void)
{
    return gps.healthy;
}

AP_GPS_Fix_t AP_GPS_GetFix(void)
{
    return gps.fix;
}
