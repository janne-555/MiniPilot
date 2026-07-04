//------------------------------------------------------------------------------
// File    : AP_Baro.h
// Purpose : Barometer Driver
// Project : MiniPilot
//------------------------------------------------------------------------------

#ifndef AP_BARO_H
#define AP_BARO_H


#include <stdint.h>


/*----------------------------------------------------------------------------
 * Barometer Data
 *---------------------------------------------------------------------------*/

typedef struct
{
    float pressure;

    float ground_pressure;

    float temperature;


    float altitude;

    float altitude_filtered;


    float climb_rate;


    uint8_t calibrated;

    uint8_t healthy;


} AP_Baro_t;

/*----------------------------------------------------------------------------
 * API
 *---------------------------------------------------------------------------*/

void AP_Baro_Init(void);


void AP_Baro_Update(void);


float AP_Baro_GetPressure(void);


float AP_Baro_GetTemperature(void);


float AP_Baro_GetAltitude(void);


float AP_Baro_GetClimbRate(void);


uint8_t AP_Baro_IsHealthy(void);


const AP_Baro_t *AP_Baro_Get(void);


#endif
