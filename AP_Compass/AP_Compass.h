//------------------------------------------------------------------------------
// File    : AP_Compass.h
// Purpose : Compass / Magnetometer Manager
// Project : MiniPilot
//------------------------------------------------------------------------------

#ifndef AP_COMPASS_H
#define AP_COMPASS_H

#include <stdint.h>

typedef struct
{
    float mag_x;
    float mag_y;
    float mag_z;

    float offset_x;
    float offset_y;
    float offset_z;

    float field_x;
    float field_y;
    float field_z;

    float heading;

    uint8_t calibrated;
    uint8_t healthy;

} AP_Compass_t;


void AP_Compass_Init(void);

void AP_Compass_Update(void);

void AP_Compass_Calibrate(void);


const AP_Compass_t *AP_Compass_Get(void);


float AP_Compass_GetHeading(void);


float AP_Compass_GetMagX(void);

float AP_Compass_GetMagY(void);

float AP_Compass_GetMagZ(void);


uint8_t AP_Compass_IsHealthy(void);


#endif
