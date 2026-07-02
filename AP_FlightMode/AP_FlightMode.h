//------------------------------------------------------------------------------
// File    : AP_FlightMode.h
// Purpose : Flight Mode Manager
// Project : MiniPilot
//------------------------------------------------------------------------------

#ifndef AP_FLIGHTMODE_H
#define AP_FLIGHTMODE_H

#include <stdint.h>

/*---------------------------------------------------------------------------
 * Flight Modes
 *---------------------------------------------------------------------------*/

typedef enum
{
    FLIGHTMODE_STABILIZE = 0,
    FLIGHTMODE_ACRO,
    FLIGHTMODE_ALTHOLD,
    FLIGHTMODE_LOITER,
    FLIGHTMODE_AUTO,
    FLIGHTMODE_RTL

} AP_FlightMode_t;

/*---------------------------------------------------------------------------
 * API
 *---------------------------------------------------------------------------*/

void AP_FlightMode_Init(void);

void AP_FlightMode_Update(void);

void AP_FlightMode_SetMode(AP_FlightMode_t mode);

AP_FlightMode_t AP_FlightMode_GetMode(void);

float AP_FlightMode_GetRoll(void);

float AP_FlightMode_GetPitch(void);

float AP_FlightMode_GetYaw(void);

float AP_FlightMode_GetThrottle(void);

#endif
