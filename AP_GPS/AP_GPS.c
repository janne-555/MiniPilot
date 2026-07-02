//------------------------------------------------------------------------------
// File    : AP_GPS.c
// Purpose : GPS Driver
// Project : MiniPilot
//------------------------------------------------------------------------------

#include "AP_GPS.h"
#include "AP_Debug/AP_Debug.h"
#include "../AP_Vehicle/AP_Vehicle.h"

static double latitude;

static double longitude;

static float altitude;

// Initialize GPS
void AP_GPS_Init(void)
{
	latitude = 12.971598;

	longitude = 77.594566;

	altitude = 920.0f;
}

// Update GPS
void AP_GPS_Update(void)
{
	// Simple movement simulation

	longitude += 0.000010;

	AP_Vehicle_Set_GPS(
			latitude,
			longitude,
			altitude);

	AP_Debug_Print(DBG_GPS,
			"\n===== GPS =====\n"
			"Lat : %.7f\n"
			"Lon : %.7f\n"
			"Alt : %.2f\n",
			latitude,
			longitude,
			altitude);
}
