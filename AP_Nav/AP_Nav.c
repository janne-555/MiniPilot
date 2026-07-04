//------------------------------------------------------------------------------
// File    : AP_Nav.c
// Purpose : GPS Navigation Controller
// Project : MiniPilot
//------------------------------------------------------------------------------

#include "AP_Nav.h"

#include "../AP_InertialNav/AP_InertialNav.h"

#include "../AP_Debug/AP_Debug.h"


#include <math.h>



#define EARTH_RADIUS 6371000.0f



static AP_Nav_t nav;


static float last_distance = -999;


/*----------------------------------------------------------------------------
 Init
----------------------------------------------------------------------------*/

void AP_Nav_Init(void)
{

    nav.home_lat = 0;

    nav.home_lon = 0;


    nav.target_lat = 0;

    nav.target_lon = 0;


    nav.distance = 0;

    nav.bearing = 0;


    nav.error_x = 0;

    nav.error_y = 0;


    nav.target_roll = 0;

    nav.target_pitch = 0;


    nav.home_set = 0;


    nav.active = 0;


    AP_Nav_SetHome();

AP_Nav_SetTarget(
17.386000,
78.487000
);
}


/*----------------------------------------------------------------------------
 Set Home
----------------------------------------------------------------------------*/

void AP_Nav_SetHome(void)
{

    nav.home_lat =
        AP_InertialNav_GetLatitude();


    nav.home_lon =
        AP_InertialNav_GetLongitude();


    nav.home_set = 1;


}



/*----------------------------------------------------------------------------
 Target
----------------------------------------------------------------------------*/

void AP_Nav_SetTarget(double lat,
                      double lon)
{

    nav.target_lat = lat;

    nav.target_lon = lon;


    nav.active = 1;
}



/*----------------------------------------------------------------------------
 Update
----------------------------------------------------------------------------*/

void AP_Nav_Update(void)
{

    if(!nav.active)
    {
        return;
    }



    nav.current_lat =
        AP_InertialNav_GetLatitude();


    nav.current_lon =
        AP_InertialNav_GetLongitude();



    double lat1 =
        nav.current_lat * M_PI / 180.0;


    double lat2 =
        nav.target_lat * M_PI / 180.0;



    double dlat =
        (nav.target_lat -
        nav.current_lat)
        *
        M_PI / 180.0;


    double dlon =
        (nav.target_lon -
        nav.current_lon)
        *
        M_PI / 180.0;



    /*
     * Haversine distance
     */

    double a =
        sin(dlat/2) * sin(dlat/2)
        +
        cos(lat1)
        *
        cos(lat2)
        *
        sin(dlon/2)
        *
        sin(dlon/2);



    double c =
        2 *
        atan2(sqrt(a),
              sqrt(1-a));



    nav.distance =
        EARTH_RADIUS * c;




    /*
     * Bearing
     */

    double y =
        sin(dlon)
        *
        cos(lat2);



    double x =
        cos(lat1)
        *
        sin(lat2)
        -
        sin(lat1)
        *
        cos(lat2)
        *
        cos(dlon);



    nav.bearing =
        atan2(y,x)
        *
        180.0f /
        M_PI;



    /*
     * Simple position controller
     */


    nav.error_x =
        nav.distance *
        cos(nav.bearing);


    nav.error_y =
        nav.distance *
        sin(nav.bearing);



    nav.target_pitch =
        nav.error_x * 0.05f;


    nav.target_roll =
        nav.error_y * 0.05f;



    /*
     * limit angle
     */

    if(nav.target_roll > 30)
        nav.target_roll = 30;


    if(nav.target_roll < -30)
        nav.target_roll = -30;


    if(nav.target_pitch > 30)
        nav.target_pitch = 30;


    if(nav.target_pitch < -30)
        nav.target_pitch = -30;




    if(fabs(nav.distance-last_distance)>1)
    {

        AP_Debug_Print(DBG_NAV,

        "\n===== NAV =====\n"
        "DIST : %.2f m\n"
        "BEAR : %.2f\n"
        "ROLL : %.2f\n"
        "PITCH: %.2f\n",

        nav.distance,
        nav.bearing,
        nav.target_roll,
        nav.target_pitch);


        last_distance =
            nav.distance;
    }

}


/*----------------------------------------------------------------------------
 Enable
----------------------------------------------------------------------------*/

void AP_Nav_Enable(uint8_t enable)
{
    nav.active = enable;
}



/*----------------------------------------------------------------------------
 Getters
----------------------------------------------------------------------------*/

float AP_Nav_GetDistance(void)
{
    return nav.distance;
}


float AP_Nav_GetBearing(void)
{
    return nav.bearing;
}


float AP_Nav_GetRollTarget(void)
{
    return nav.target_roll;
}


float AP_Nav_GetPitchTarget(void)
{
    return nav.target_pitch;
}



const AP_Nav_t *AP_Nav_Get(void)
{
    return &nav;
}
