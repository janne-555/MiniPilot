//------------------------------------------------------------------------------
// File    : AP_Vehicle.c
// Purpose : Vehicle State Manager
// Project : MiniPilot
//------------------------------------------------------------------------------

#include "AP_Vehicle.h"

#include "../AP_AHRS/AP_AHRS.h"
#include "../AP_GPS/AP_GPS.h"
#include "../AP_InertialNav/AP_InertialNav.h"
#include "../AP_Arming/AP_Arming.h"
#include "../AP_FlightMode/AP_FlightMode.h"


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



/*----------------------------------------------------------------------------
 * Update
 *---------------------------------------------------------------------------*/

void AP_Vehicle_Update(void)
{

    /*
     * AHRS attitude
     */

    vehicle.roll =
        AP_AHRS_GetRoll();


    vehicle.pitch =
        AP_AHRS_GetPitch();


    vehicle.yaw =
        AP_AHRS_GetYaw();



    /*
     * GPS position
     */

    vehicle.latitude =
        AP_GPS_GetLatitude();


    vehicle.longitude =
        AP_GPS_GetLongitude();


    vehicle.ground_speed =
        AP_GPS_GetGroundSpeed();



    /*
     * Navigation altitude
     */

    vehicle.altitude =
        AP_InertialNav_GetAltitude();


    vehicle.climb_rate =
        AP_InertialNav_GetVelocityZ();



    /*
     * Vehicle status
     */

    vehicle.armed =
        AP_Arming_IsArmed();


    vehicle.mode =
        AP_FlightMode_GetMode();

}



/*----------------------------------------------------------------------------
 * Get attitude
 *---------------------------------------------------------------------------*/

void AP_Vehicle_Get_Attitude(float *roll,
                             float *pitch,
                             float *yaw)
{
    *roll = vehicle.roll;

    *pitch = vehicle.pitch;

    *yaw = vehicle.yaw;
}



/*----------------------------------------------------------------------------
 * Get GPS
 *---------------------------------------------------------------------------*/

void AP_Vehicle_Get_GPS(double *lat,
                        double *lon,
                        float *alt)
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



const AP_Vehicle_State_t *AP_Vehicle_GetState(void)
{
    return &vehicle;
}
