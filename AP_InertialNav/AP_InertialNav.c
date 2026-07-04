//------------------------------------------------------------------------------
// File    : AP_InertialNav.c
// Purpose : Position Estimator
// Project : MiniPilot
//------------------------------------------------------------------------------

#include "AP_InertialNav.h"

#include "../AP_Baro/AP_Baro.h"

#include "../AP_GPS/AP_GPS.h"

#include "../AP_Debug/AP_Debug.h"



static AP_InertialNav_t nav;


static float last_altitude;
/*
 * Debug filters
 */
static float debug_last_alt = -999.0f;

static float debug_last_vz = -999.0f;

/*----------------------------------------------------------------------------
 Init
----------------------------------------------------------------------------*/

void AP_InertialNav_Init(void)
{

    nav.altitude = 0.0f;


    nav.latitude = 0.0;

    nav.longitude = 0.0;



    nav.velocity_x = 0.0f;

    nav.velocity_y = 0.0f;

    nav.velocity_z = 0.0f;



    nav.healthy = 1;


    last_altitude = 0.0f;
}


/*----------------------------------------------------------------------------
 Update
----------------------------------------------------------------------------*/

void AP_InertialNav_Update(float dt)
{


    /*
     * Altitude from Barometer
     */

    nav.altitude =
        AP_Baro_GetAltitude();



    /*
     * Vertical velocity
     */

    nav.velocity_z =
        (nav.altitude - last_altitude)
        /
        dt;



    last_altitude =
        nav.altitude;



    /*
     * GPS position
     */


    nav.latitude =
        AP_GPS_GetLatitude();


    nav.longitude =
        AP_GPS_GetLongitude();

/*
 * Debug only on significant change
 */

if (((nav.altitude - debug_last_alt) > 1.0f) ||
    ((debug_last_alt - nav.altitude) > 1.0f) ||
    ((nav.velocity_z - debug_last_vz) > 1.0f) ||
    ((debug_last_vz - nav.velocity_z) > 1.0f))
{

    AP_Debug_Print(DBG_NAV,

        "\n===== INERTIAL NAV =====\n"
        "ALT : %.2f m\n"
        "VZ  : %.2f m/s\n"
        "LAT : %.6lf\n"
        "LON : %.6lf\n",

        nav.altitude,

        nav.velocity_z,

        nav.latitude,

        nav.longitude);


    debug_last_alt = nav.altitude;

    debug_last_vz = nav.velocity_z;
}


}


/*----------------------------------------------------------------------------
 Getters
----------------------------------------------------------------------------*/


const AP_InertialNav_t *AP_InertialNav_Get(void)
{
    return &nav;
}



float AP_InertialNav_GetAltitude(void)
{
    return nav.altitude;
}



float AP_InertialNav_GetVelocityZ(void)
{
    return nav.velocity_z;
}



double AP_InertialNav_GetLatitude(void)
{
    return nav.latitude;
}



double AP_InertialNav_GetLongitude(void)
{
    return nav.longitude;
}
