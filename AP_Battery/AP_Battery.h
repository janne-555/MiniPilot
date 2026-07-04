//------------------------------------------------------------------------------
// File    : AP_Battery.h
// Purpose : Battery Monitor
// Project : MiniPilot
//------------------------------------------------------------------------------

#ifndef AP_BATTERY_H
#define AP_BATTERY_H

#include <stdint.h>


typedef struct
{
    float voltage;

    float current;

    float consumed_mah;

    float remaining_percent;


    uint8_t healthy;

    uint8_t low;

    uint8_t critical;

} AP_Battery_t;



void AP_Battery_Init(void);


void AP_Battery_Update(void);


/* Get complete battery status */

const AP_Battery_t *AP_Battery_Get(void);



float AP_Battery_GetVoltage(void);

float AP_Battery_GetCurrent(void);

float AP_Battery_GetRemaining(void);


uint8_t AP_Battery_IsLow(void);

uint8_t AP_Battery_IsHealthy(void);


#endif
