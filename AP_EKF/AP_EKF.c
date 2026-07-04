//------------------------------------------------------------------------------
// File    : AP_EKF.c
// Purpose : Sensor Fusion
// Project : MiniPilot
//------------------------------------------------------------------------------

#include "AP_EKF.h"


#include "../AP_IMU/AP_IMU.h"

#include "../AP_GPS/AP_GPS.h"

#include "../AP_Baro/AP_Baro.h"

#include "../AP_Debug/AP_Debug.h"


#include <math.h>



#define RAD_TO_DEG 57.2957795f



/*----------------------------------------------------------------------------
 * Private
 *---------------------------------------------------------------------------*/

static AP_EKF_t ekf;



/*
 * Debug memory
 */

static float last_alt = 9999.0f;


/*----------------------------------------------------------------------------
 * Init
 *---------------------------------------------------------------------------*/

void AP_EKF_Init(void)
{

    ekf.roll = 0.0f;

    ekf.pitch = 0.0f;

    ekf.yaw = 0.0f;



    ekf.latitude = 0;

    ekf.longitude = 0;


    ekf.altitude = 0;


    ekf.velocity_z = 0;



    ekf.imu_ok = 0;

    ekf.gps_ok = 0;

    ekf.baro_ok = 0;


    ekf.healthy = 0;

}



/*----------------------------------------------------------------------------
 * Update
 *---------------------------------------------------------------------------*/

void AP_EKF_Update(float dt)
{

    const AP_IMU_t *imu;

    const AP_GPS_t *gps;

    const AP_Baro_t *baro;



    imu = AP_IMU_Get();

    gps = AP_GPS_Get();

    baro = AP_Baro_Get();



    ekf.imu_ok = imu->healthy;


    ekf.gps_ok = gps->healthy;


    ekf.baro_ok = baro->healthy;



    if (!ekf.imu_ok)
    {
        ekf.healthy = 0;

        return;
    }



    /*
     * --------------------------------
     * Prediction
     * IMU integration
     * --------------------------------
     */


    ekf.roll += imu->gx * dt;


    ekf.pitch += imu->gy * dt;


    ekf.yaw += imu->gz * dt;



    /*
     * --------------------------------
     * Accel correction
     * --------------------------------
     */


    float acc_roll;


    float acc_pitch;



    acc_roll =
        atan2f(
            imu->ay,
            imu->az
        ) * RAD_TO_DEG;



    acc_pitch =
        atan2f(
            -imu->ax,

            sqrtf(
                imu->ay * imu->ay +
                imu->az * imu->az
            )

        ) * RAD_TO_DEG;




    ekf.roll =

        0.98f * ekf.roll +

        0.02f * acc_roll;



    ekf.pitch =

        0.98f * ekf.pitch +

        0.02f * acc_pitch;



    /*
     * --------------------------------
     * Barometer correction
     * --------------------------------
     */


    if (ekf.baro_ok)
    {

        ekf.altitude =

            0.90f * ekf.altitude +

            0.10f * baro->altitude;



        ekf.velocity_z =

            baro->climb_rate;

    }



    /*
     * --------------------------------
     * GPS correction
     * --------------------------------
     */


    if (ekf.gps_ok)
    {

        ekf.latitude =

            (0.95 * ekf.latitude) +

            (0.05 * gps->latitude);



        ekf.longitude =

            (0.95 * ekf.longitude) +

            (0.05 * gps->longitude);

    }




    ekf.healthy =

        ekf.imu_ok &&

        ekf.baro_ok;



    /*
     * Debug no spam
     */

    if (fabsf(ekf.altitude - last_alt) > 0.5f)
    {


        AP_Debug_Print(DBG_EKF,


            "\n===== EKF =====\n"

            "Roll   : %.2f\n"

            "Pitch  : %.2f\n"

            "Yaw    : %.2f\n"

            "Lat    : %.7lf\n"

            "Lon    : %.7lf\n"

            "Alt    : %.2f\n"

            "VelZ   : %.2f\n"

            "IMU    : %u\n"

            "GPS    : %u\n"

            "BARO   : %u\n"

            "Health : %u\n",


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

            ekf.healthy);


        last_alt = ekf.altitude;

    }

}



/*----------------------------------------------------------------------------
 * Getters
 *---------------------------------------------------------------------------*/


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



const AP_EKF_t *AP_EKF_Get(void)
{
    return &ekf;
}
