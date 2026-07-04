//------------------------------------------------------------------------------
// File    : AP_Baro.c
// Purpose : Barometer Driver
// Project : MiniPilot
//------------------------------------------------------------------------------

#include "AP_Baro.h"
#include "../AP_Failsafe/AP_Failsafe.h"
#include "../AP_Debug/AP_Debug.h"

#include <math.h>

#define BARO_DT 0.02f

/*----------------------------------------------------------------------------
 Private
----------------------------------------------------------------------------*/

static AP_Baro_t baro;


static float last_altitude = 0.0f;
static float last_print_alt = -999;


/*----------------------------------------------------------------------------
 Init
----------------------------------------------------------------------------*/

void AP_Baro_Init(void)
{
    /*
     * Sea level default
     */

    baro.pressure = 101325.0f;


    baro.temperature = 25.0f;


    baro.altitude = 0.0f;


    baro.climb_rate = 0.0f;


    baro.healthy = 1;


    last_altitude = 0.0f;
}



/*----------------------------------------------------------------------------
 Update
----------------------------------------------------------------------------*/

void AP_Baro_Update(void)
{

    /*
     * SIMULATION
     *
     * Later:
     * BMP280 / MS5611 driver
     */


    baro.pressure -= 0.05f;



    /*
     * Pressure -> Altitude
     *
     * Standard atmosphere formula
     */


    baro.altitude =
        44330.0f *
        (1.0f -
        powf(baro.pressure / 101325.0f,
             0.1903f));



    /*
     * Vertical speed
     *
     * Scheduler 100Hz
     *
     * dt = 0.01
     */


    baro.climb_rate =
        (baro.altitude - last_altitude)
        / BARO_DT;



    last_altitude = baro.altitude;


if ((baro.altitude - last_print_alt > 0.5f) ||
    (last_print_alt - baro.altitude > 0.5f))
{

    AP_Debug_Print(DBG_BARO,

        "\n===== BARO =====\n"
        "Pressure : %.2f Pa\n"
        "Temp     : %.2f C\n"
        "Altitude : %.2f m\n"
        "Climb    : %.2f m/s\n",

        baro.pressure,
        baro.temperature,
        baro.altitude,
        baro.climb_rate);


    last_print_alt = baro.altitude;
}

}



/*----------------------------------------------------------------------------
 Getters
----------------------------------------------------------------------------*/

const AP_Baro_t *AP_Baro_Get(void)
{
    return &baro;
}



float AP_Baro_GetPressure(void)
{
    return baro.pressure;
}



float AP_Baro_GetTemperature(void)
{
    return baro.temperature;
}



float AP_Baro_GetAltitude(void)
{
    return baro.altitude;
}



float AP_Baro_GetClimbRate(void)
{
    return baro.climb_rate;
}



uint8_t AP_Baro_IsHealthy(void)
{
    return baro.healthy;
}
