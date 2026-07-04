//------------------------------------------------------------------------------
// File    : AP_EKF.c
// Purpose : Extended Kalman Filter
// Project : MiniPilot
//------------------------------------------------------------------------------

#include "AP_EKF.h"


#include "../AP_AHRS/AP_AHRS.h"

#include "../AP_GPS/AP_GPS.h"

#include "../AP_Baro/AP_Baro.h"

#include "../AP_Compass/AP_Compass.h"

#include "../AP_Debug/AP_Debug.h"



#define EKF_YAW_GYRO_WEIGHT      0.98f

#define EKF_YAW_COMPASS_WEIGHT   0.02f



static AP_EKF_t ekf;


static uint32_t debug_counter = 0;




void AP_EKF_Init(void)
{
    ekf.roll = 0.0f;

    ekf.pitch = 0.0f;

    ekf.yaw = 0.0f;


    ekf.latitude = 0.0;

    ekf.longitude = 0.0;


    ekf.altitude = 0.0f;


    ekf.velocity_z = 0.0f;


    ekf.imu_ok = 0;

    ekf.gps_ok = 0;

    ekf.baro_ok = 0;

    ekf.compass_ok = 0;


    ekf.healthy = 0;
}




void AP_EKF_Update(float dt)
{

    /*
     * IMU / AHRS Fusion
     */

    ekf.roll =
        AP_AHRS_GetRoll();


    ekf.pitch =
        AP_AHRS_GetPitch();



    /*
     * Compass yaw correction
     *
     * Gyro = fast
     * Compass = drift correction
     */

    float gyro_yaw =
        AP_AHRS_GetYaw();


    float compass_yaw =
        AP_Compass_GetHeading();



    ekf.yaw =
        (gyro_yaw * EKF_YAW_GYRO_WEIGHT) +

        (compass_yaw * EKF_YAW_COMPASS_WEIGHT);





    /*
     * GPS Fusion
     */

    ekf.latitude =
        AP_GPS_GetLatitude();


    ekf.longitude =
        AP_GPS_GetLongitude();




    /*
     * BARO Fusion
     */

    ekf.altitude =
        AP_Baro_GetAltitude();



    ekf.velocity_z =
        AP_Baro_GetClimbRate();





    /*
     * Sensor health
     */


    ekf.imu_ok = 1;


    ekf.gps_ok =
        AP_GPS_IsHealthy();



    ekf.baro_ok = 1;



    ekf.compass_ok =
        AP_Compass_IsHealthy();




    /*
     * Overall EKF health
     */

    if(ekf.imu_ok &&
       ekf.gps_ok &&
       ekf.baro_ok &&
       ekf.compass_ok)
    {
        ekf.healthy = 1;
    }
    else
    {
        ekf.healthy = 0;
    }




    /*
     * Debug slow
     */

    debug_counter++;


    if(debug_counter >= 100)
    {
        debug_counter = 0;


        AP_Debug_Print(DBG_EKF,

        "\n===== EKF =====\n"
        "Roll    : %.2f\n"
        "Pitch   : %.2f\n"
        "Yaw     : %.2f\n"
        "Lat     : %.7lf\n"
        "Lon     : %.7lf\n"
        "Alt     : %.2f\n"
        "VelZ    : %.2f\n"
        "IMU     : %d\n"
        "GPS     : %d\n"
        "BARO    : %d\n"
        "COMPASS : %d\n"
        "Health  : %d\n",

        ekf.roll,
        ekf.pitch,
        ekf.yaw,

        ekf.latitude,
        ekf.longitude,

        ekf.altitude,
        ekf.velocity_z,

        ekf.imu_ok,
        ekf.gps_ok,
        ekf.baro_ok,
        ekf.compass_ok,

        ekf.healthy);
    }
}




float AP_EKF_GetRoll(void)
{
    return ekf.roll;
}


float AP_EKF_GetPitch(void)
{
    return ekf.pitch;
}


float AP_EKF_GetYaw(void)
{
    return ekf.yaw;
}



double AP_EKF_GetLatitude(void)
{
    return ekf.latitude;
}


double AP_EKF_GetLongitude(void)
{
    return ekf.longitude;
}



float AP_EKF_GetAltitude(void)
{
    return ekf.altitude;
}


float AP_EKF_GetVelocityZ(void)
{
    return ekf.velocity_z;
}



uint8_t AP_EKF_IsHealthy(void)
{
    return ekf.healthy;
}



uint8_t AP_EKF_CompassHealthy(void)
{
    return ekf.compass_ok;
}



const AP_EKF_t *AP_EKF_Get(void)
{
    return &ekf;
}
