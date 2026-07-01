
//------------------------------------------------------------------------------
// File    : AP_Vehicle.c
// Purpose : Vehicle State
// Project : MiniPilot
//------------------------------------------------------------------------------

#include "AP_Vehicle.h"

static AP_Vehicle_State_t vehicle;

// Initialize vehicle
void AP_Vehicle_Init(void)
{
    vehicle.roll = 0.0f;
    vehicle.pitch = 0.0f;
    vehicle.yaw = 0.0f;

    vehicle.latitude = 12.971598;
    vehicle.longitude = 77.594566;

    vehicle.altitude = 920.0f;

    vehicle.ground_speed = 0.0f;

    vehicle.armed = 0;

    vehicle.mode = 0;
}

// Update vehicle
void AP_Vehicle_Update(void)
{
    // Reserved for future vehicle logic
}


// Set attitude
void AP_Vehicle_Set_Attitude(float roll,
                             float pitch,
                             float yaw)
{
    vehicle.roll = roll;
    vehicle.pitch = pitch;
    vehicle.yaw = yaw;
}

// Get attitude
void AP_Vehicle_Get_Attitude(float *roll,
                             float *pitch,
                             float *yaw)
{
    *roll = vehicle.roll;
    *pitch = vehicle.pitch;
    *yaw = vehicle.yaw;
}

// Set GPS
void AP_Vehicle_Set_GPS(double lat,
                        double lon,
                        float alt)
{
    vehicle.latitude = lat;
    vehicle.longitude = lon;
    vehicle.altitude = alt;
}

// Get GPS
void AP_Vehicle_Get_GPS(double *lat,
                        double *lon,
                        float *alt)
{
    *lat = vehicle.latitude;
    *lon = vehicle.longitude;
    *alt = vehicle.altitude;
}

// Set speed
void AP_Vehicle_Set_GroundSpeed(float speed)
{
    vehicle.ground_speed = speed;
}

// Get speed
float AP_Vehicle_Get_GroundSpeed(void)
{
    return vehicle.ground_speed;
}

// Arm state
void AP_Vehicle_Set_Armed(uint8_t armed)
{
    vehicle.armed = armed;
}

uint8_t AP_Vehicle_Get_Armed(void)
{
    return vehicle.armed;
}

// Flight mode
void AP_Vehicle_Set_Mode(uint8_t mode)
{
    vehicle.mode = mode;
}

uint8_t AP_Vehicle_Get_Mode(void)
{
    return vehicle.mode;
}
