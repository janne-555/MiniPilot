//------------------------------------------------------------------------------
// File    : AP_Vehicle.c
// Purpose : Vehicle State Manager
// Project : MiniPilot
//------------------------------------------------------------------------------

#include "AP_Vehicle.h"
#include "../AP_Arming/AP_Arming.h"
#include "../AP_Debug/AP_Debug.h"
#include "../AP_EKF/AP_EKF.h"
#include "../AP_FlightMode/AP_FlightMode.h"
#include "../AP_GPS/AP_GPS.h"

/*----------------------------------------------------------------------------
 * Private
 *---------------------------------------------------------------------------*/

static AP_Vehicle_State_t vehicle;

/*----------------------------------------------------------------------------
 * Init
 *---------------------------------------------------------------------------*/

void AP_Vehicle_Init(void)
{
    vehicle.roll = 0.0f;
  vehicle.pitch = 0.0f;
  vehicle.yaw = 0.0f;

  vehicle.latitude = 0;
  vehicle.longitude = 0;

  vehicle.altitude = 0;

  vehicle.ground_speed = 0;

  vehicle.climb_rate = 0;

  vehicle.armed = 0;

  vehicle.mode = 0;
}

//------------------------------------------------------------------------------
// Update vehicle
//------------------------------------------------------------------------------

void AP_Vehicle_Update(void)
{
    /*
   * EKF attitude estimate
   */

  vehicle.roll = AP_EKF_GetRoll();

  vehicle.pitch = AP_EKF_GetPitch();

  vehicle.yaw = AP_EKF_GetYaw();

  /*
   * EKF position estimate
   */

  vehicle.latitude = AP_EKF_GetLatitude();

  vehicle.longitude = AP_EKF_GetLongitude();

  vehicle.altitude = AP_EKF_GetAltitude();

  /*
   * EKF velocity
   */

  vehicle.climb_rate = AP_EKF_GetVelocityZ();

  /*
   * GPS raw info still comes from GPS driver
   */

  vehicle.ground_speed = AP_GPS_GetGroundSpeed();

  /*
   * Vehicle status
   */

  vehicle.armed = AP_Arming_IsArmed();

  vehicle.mode = AP_FlightMode_GetMode();

  /*
      AP_Debug_Print(DBG_VEHICLE,

  "\n===== VEHICLE =====\n"
  "Roll %.2f\n"
  "Pitch %.2f\n"
  "Yaw %.2f\n"
  "Lat %.7lf\n"
  "Lon %.7lf\n"
  "Alt %.2f\n",

  vehicle.roll,
  vehicle.pitch,
  vehicle.yaw,
  vehicle.latitude,
  vehicle.longitude,
  vehicle.altitude);
  */
}

/*----------------------------------------------------------------------------
 * Get attitude
 *---------------------------------------------------------------------------*/

void AP_Vehicle_Get_Attitude(float *roll, float *pitch, float *yaw)
{
    *roll = vehicle.roll;

  *pitch = vehicle.pitch;

  *yaw = vehicle.yaw;
}

/*----------------------------------------------------------------------------
 * Get GPS
 *---------------------------------------------------------------------------*/

void AP_Vehicle_Get_GPS(double *lat, double *lon, float *alt)
{
    *lat = vehicle.latitude;

  *lon = vehicle.longitude;

  *alt = vehicle.altitude;
}

float AP_Vehicle_Get_Altitude(void)
{
    return vehicle.altitude;
}

/*----------------------------------------------------------------------------
 * Velocity
 *---------------------------------------------------------------------------*/

float AP_Vehicle_Get_GroundSpeed(void)
{
    return vehicle.ground_speed;
}

float AP_Vehicle_Get_ClimbRate(void)
{
    return vehicle.climb_rate;
}

/*----------------------------------------------------------------------------
 * Status
 *---------------------------------------------------------------------------*/

uint8_t AP_Vehicle_Get_Armed(void)
{
    return vehicle.armed;
}

uint8_t AP_Vehicle_Get_Mode(void)
{
    return vehicle.mode;
}

const AP_Vehicle_State_t *AP_Vehicle_GetState(void) { return &vehicle; }
