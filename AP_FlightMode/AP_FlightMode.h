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

typedef enum {
  FLIGHTMODE_STABILIZE = 0,

  FLIGHTMODE_ACRO,

  FLIGHTMODE_ALTHOLD,

  FLIGHTMODE_LOITER,

  FLIGHTMODE_AUTO,

  FLIGHTMODE_RTL,

  FLIGHTMODE_LAND,

  FLIGHTMODE_FAILSAFE

} AP_FlightMode_t;

/*---------------------------------------------------------------------------
 * Mode Change Reason
 *---------------------------------------------------------------------------*/

typedef enum {
  MODE_REASON_USER = 0,

  MODE_REASON_FAILSAFE,

  MODE_REASON_MISSION,

  MODE_REASON_SYSTEM

} AP_FlightMode_Reason_t;

/*---------------------------------------------------------------------------
 * Flight Mode State
 *---------------------------------------------------------------------------*/

typedef struct {
  AP_FlightMode_t mode;

  AP_FlightMode_Reason_t reason;

  float desired_roll;

  float desired_pitch;

  float desired_yaw;

  float desired_throttle;

} AP_FlightMode_State_t;
/*---------------------------------------------------------------------------
 * API
 *---------------------------------------------------------------------------*/

void AP_FlightMode_Init(void);

void AP_FlightMode_Update(void);

void AP_FlightMode_SetMode(AP_FlightMode_t mode, AP_FlightMode_Reason_t reason);

AP_FlightMode_t AP_FlightMode_GetMode(void);

/*
 * Desired attitude outputs
 */

float AP_FlightMode_GetRoll(void);

float AP_FlightMode_GetPitch(void);

float AP_FlightMode_GetYaw(void);

float AP_FlightMode_GetThrottle(void);

/*
 * Full state access
 */

const AP_FlightMode_State_t *AP_FlightMode_GetState(void);

#endif
