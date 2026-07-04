//------------------------------------------------------------------------------
// File    : AP_Vehicle.h
// Purpose : Vehicle State Manager
// Project : MiniPilot
//------------------------------------------------------------------------------

#ifndef AP_VEHICLE_H
#define AP_VEHICLE_H

#include <stdint.h>

/*----------------------------------------------------------------------------
 * Vehicle State
 *---------------------------------------------------------------------------*/

typedef struct
{
    /* Attitude */
    float roll;
    float pitch;
    float yaw;


    /* Position */
    double latitude;
    double longitude;

    float altitude;


    /* Velocity */
    float ground_speed;

    float climb_rate;


    /* System */
    uint8_t armed;

    uint8_t mode;


} AP_Vehicle_State_t;


/*----------------------------------------------------------------------------
 * API
 *---------------------------------------------------------------------------*/

void AP_Vehicle_Init(void);


void AP_Vehicle_Update(void);


/* Attitude */

void AP_Vehicle_Get_Attitude(float *roll,
                             float *pitch,
                             float *yaw);


/* Position */

void AP_Vehicle_Get_GPS(double *lat,
                        double *lon,
                        float *alt);


float AP_Vehicle_Get_Altitude(void);


/* Velocity */

float AP_Vehicle_Get_GroundSpeed(void);


float AP_Vehicle_Get_ClimbRate(void);


/* System */

uint8_t AP_Vehicle_Get_Armed(void);


uint8_t AP_Vehicle_Get_Mode(void);


const AP_Vehicle_State_t *AP_Vehicle_GetState(void);


#endif
