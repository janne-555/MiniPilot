//------------------------------------------------------------------------------
// File    : AP_IMU.c
// Purpose : IMU Driver
// Project : MiniPilot
//------------------------------------------------------------------------------

#include "AP_IMU.h"
#include "../AP_Sim/AP_Sim.h"

#define DEG_TO_RAD 0.0174532925f
static AP_IMU_t imu;


void AP_IMU_Init(void)
{
    imu.gx = 0.0f;
    imu.gy = 0.0f;
    imu.gz = 0.0f;

    imu.ax = 0.0f;
    imu.ay = 0.0f;
    imu.az = 9.81f;

    imu.healthy = 1;
}

void AP_IMU_Update(void)
{
    float roll;
    float roll_rad;

    roll = AP_Sim_GetRoll();

    imu.gx = AP_Sim_GetRollRate();
    imu.gy = 0.0f;
    imu.gz = 0.0f;

    roll_rad = roll * DEG_TO_RAD;

    imu.ax = 0.0f;
    imu.ay = 9.81f * sinf(roll_rad);
    imu.az = 9.81f * cosf(roll_rad);

    imu.healthy = 1;
}
/*
void AP_IMU_Update(void)
{
    imu.gx = 0.0f;
    imu.gy = 0.0f;
    imu.gz = 0.0f;

    imu.ax = 0.0f;
    imu.ay = 0.0f;
    imu.az = 9.81f;

    imu.healthy = 1;
}
*/
const AP_IMU_t *AP_IMU_Get(void)
{
    return &imu;
}
