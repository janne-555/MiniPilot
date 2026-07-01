//------------------------------------------------------------------------------
// File    : AP_IMU.h
// Purpose : IMU Driver
// Project : MiniPilot
//------------------------------------------------------------------------------


#ifndef AP_IMU_H
#define AP_IMU_H

typedef struct
{
    /* Gyroscope (deg/s) */
    float gx;
    float gy;
    float gz;

    /* Accelerometer (m/s²) */
    float ax;
    float ay;
    float az;

    /* Sensor health */
    int healthy;

} AP_IMU_t;

/* Initialize IMU */
void AP_IMU_Init(void);

/* Update IMU measurements */
void AP_IMU_Update(void);

/* Get latest IMU data */
const AP_IMU_t *AP_IMU_Get(void);

#endif
