//------------------------------------------------------------------------------
// File    : AP_Home.c
// Purpose : Home Location Manager
// Project : MiniPilot
//------------------------------------------------------------------------------

#include "AP_Home.h"


#include "../AP_EKF/AP_EKF.h"

#include "../AP_Debug/AP_Debug.h"


#include <math.h>



#define EARTH_RADIUS_M 6371000.0f



static AP_Home_t home;


static uint32_t debug_counter = 0;



void AP_Home_Init(void)
{
    home.latitude = 0.0;

    home.longitude = 0.0;


    home.altitude = 0.0f;


    home.heading = 0.0f;


    home.valid = 0;
}



void AP_Home_Update(void)
{

    /*
     * Auto set home when EKF ready
     */

    if(home.valid == 0 &&
       AP_EKF_IsHealthy())
    {
        AP_Home_SetCurrent();
    }



    debug_counter++;


    if(debug_counter >= 20)
    {
        debug_counter = 0;


        AP_Debug_Print(DBG_HOME,

        "\n===== HOME =====\n"
        "Valid : %d\n"
        "Lat   : %.7lf\n"
        "Lon   : %.7lf\n"
        "Alt   : %.2f\n"
        "Dist  : %.2f\n"
        "Bear  : %.2f\n",

        home.valid,
        home.latitude,
        home.longitude,
        home.altitude,
        AP_Home_GetDistance(),
        AP_Home_GetBearing());
    }
}



uint8_t AP_Home_SetCurrent(void)
{

    if(!AP_EKF_IsHealthy())
    {
        return 0;
    }


    home.latitude =
        AP_EKF_GetLatitude();


    home.longitude =
        AP_EKF_GetLongitude();


    home.altitude =
        AP_EKF_GetAltitude();


    home.heading =
        AP_EKF_GetYaw();


    home.valid = 1;


    AP_Debug_Print(DBG_HOME,
    "\nHOME SET\n");


    return 1;
}




void AP_Home_Set(double lat,
                 double lon,
                 float alt)
{

    home.latitude = lat;


    home.longitude = lon;


    home.altitude = alt;


    home.valid = 1;
}



void AP_Home_Clear(void)
{
    home.valid = 0;
}



uint8_t AP_Home_IsSet(void)
{
    return home.valid;
}




double AP_Home_GetLatitude(void)
{
    return home.latitude;
}


double AP_Home_GetLongitude(void)
{
    return home.longitude;
}



float AP_Home_GetAltitude(void)
{
    return home.altitude;
}




float AP_Home_GetDistance(void)
{

    if(!home.valid)
    {
        return 0;
    }


    double lat1 =
        home.latitude * M_PI / 180.0;


    double lat2 =
        AP_EKF_GetLatitude() * M_PI / 180.0;



    double dlat =
        lat2 - lat1;


    double dlon =
        (AP_EKF_GetLongitude() -
         home.longitude) *
         M_PI / 180.0;



    double a =
        sin(dlat/2) * sin(dlat/2) +

        cos(lat1) *
        cos(lat2) *
        sin(dlon/2) *
        sin(dlon/2);



    double c =
        2 *
        atan2(
        sqrt(a),
        sqrt(1-a));


    return EARTH_RADIUS_M * c;
}





float AP_Home_GetBearing(void)
{

    if(!home.valid)
    {
        return 0;
    }


    double lat1 =
        AP_EKF_GetLatitude() *
        M_PI / 180.0;


    double lat2 =
        home.latitude *
        M_PI / 180.0;



    double dlon =
        (home.longitude -
         AP_EKF_GetLongitude())
        *
        M_PI / 180.0;



    double y =
        sin(dlon) *
        cos(lat2);


    double x =
        cos(lat1) *
        sin(lat2) -

        sin(lat1) *
        cos(lat2) *
        cos(dlon);



    float bearing =
        atan2(y,x) *
        57.2957795f;



    if(bearing < 0)
    {
        bearing += 360;
    }


    return bearing;
}





const AP_Home_t *AP_Home_Get(void)
{
    return &home;
}
