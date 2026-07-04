//------------------------------------------------------------------------------
// File    : AP_GPS.h
// Purpose : GPS Manager
// Project : MiniPilot
//------------------------------------------------------------------------------

#ifndef AP_GPS_H
#define AP_GPS_H

#include <stdint.h>


/*----------------------------------------------------------------------------
 * GPS Fix Types
 *---------------------------------------------------------------------------*/

typedef enum
{
    GPS_FIX_NONE = 0,

    GPS_FIX_2D,

    GPS_FIX_3D

} AP_GPS_Fix_t;


/*----------------------------------------------------------------------------
 * GPS State
 *---------------------------------------------------------------------------*/

typedef struct
{
    double latitude;

    double longitude;


    float altitude;


    float ground_speed;


    float course;


    uint8_t satellites;


    AP_GPS_Fix_t fix;


    uint8_t healthy;


} AP_GPS_t;



/*----------------------------------------------------------------------------
 * API
 *---------------------------------------------------------------------------*/

void AP_GPS_Init(void);


void AP_GPS_Update(void);



const AP_GPS_t *AP_GPS_Get(void);



double AP_GPS_GetLatitude(void);


double AP_GPS_GetLongitude(void);


float AP_GPS_GetAltitude(void);


float AP_GPS_GetGroundSpeed(void);


float AP_GPS_GetCourse(void);


uint8_t AP_GPS_GetSatellites(void);


uint8_t AP_GPS_IsHealthy(void);


AP_GPS_Fix_t AP_GPS_GetFix(void);


#endif
