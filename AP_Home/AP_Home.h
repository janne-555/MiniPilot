//------------------------------------------------------------------------------
// File    : AP_Home.h
// Purpose : Home Location Manager
// Project : MiniPilot
//------------------------------------------------------------------------------

#ifndef AP_HOME_H
#define AP_HOME_H

#include <stdint.h>

typedef struct {
  double latitude;

  double longitude;

  float altitude;

  float heading;

  uint8_t valid;

} AP_Home_t;

void AP_Home_Init(void);

void AP_Home_Update(void);

uint8_t AP_Home_SetCurrent(void);

void AP_Home_Set(double lat, double lon, float alt);

void AP_Home_Clear(void);

uint8_t AP_Home_IsSet(void);

double AP_Home_GetLatitude(void);

double AP_Home_GetLongitude(void);

float AP_Home_GetAltitude(void);

float AP_Home_GetDistance(void);

float AP_Home_GetBearing(void);

const AP_Home_t *AP_Home_Get(void);

#endif
