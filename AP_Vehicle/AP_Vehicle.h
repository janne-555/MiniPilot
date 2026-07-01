
//------------------------------------------------------------------------------
// File    : AP_Vehicle.h
// Purpose : Vehicle State
// Project : MiniPilot
//------------------------------------------------------------------------------

#ifndef AP_VEHICLE_H
#define AP_VEHICLE_H

#include <stdint.h>

// Vehicle state
typedef struct
{
    float roll;
    float pitch;
    float yaw;

    double latitude;
    double longitude;

    float altitude;

    float ground_speed;

    uint8_t armed;

    uint8_t mode;

} AP_Vehicle_State_t;

// Initialize vehicle
void AP_Vehicle_Init(void);

// Update vehicle
void AP_Vehicle_Update(void);

// Set attitude
void AP_Vehicle_Set_Attitude(float roll,
                             float pitch,
                             float yaw);

// Get attitude
void AP_Vehicle_Get_Attitude(float *roll,
                             float *pitch,
                             float *yaw);

// Set GPS
void AP_Vehicle_Set_GPS(double lat,
                        double lon,
                        float alt);

// Get GPS
void AP_Vehicle_Get_GPS(double *lat,
                        double *lon,
                        float *alt);

// Set speed
void AP_Vehicle_Set_GroundSpeed(float speed);

// Get speed
float AP_Vehicle_Get_GroundSpeed(void);

// Arm state
void AP_Vehicle_Set_Armed(uint8_t armed);

uint8_t AP_Vehicle_Get_Armed(void);

// Flight mode
void AP_Vehicle_Set_Mode(uint8_t mode);

uint8_t AP_Vehicle_Get_Mode(void);

#endif
