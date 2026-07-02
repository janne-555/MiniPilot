//------------------------------------------------------------------------------
// File    : AP_AHRS.c
// Purpose : Attitude Estimator
// Project : MiniPilot
//------------------------------------------------------------------------------

#include "AP_AHRS.h"
#include "../AP_Config/AP_Config.h"
#include "../AP_IMU/AP_IMU.h"
#include "../AP_Vehicle/AP_Vehicle.h"
#include "AP_Debug/AP_Debug.h"

#include <math.h>

#define RAD_TO_DEG 57.2957795f
static float roll;

static float pitch;

static float yaw;

// Initialize AHRS
void AP_AHRS_Init(void)
{
	roll = 0.0f;

	pitch = 0.0f;

	yaw = 0.0f;
}

// Update attitude
void AP_AHRS_Update(void)
{

	const AP_IMU_t *imu = AP_IMU_Get();

	if(!imu->healthy)
	{
		return;
	}

	float roll_acc;

	roll_acc = 
		atan2f(
				imu->ay,
				imu->az);

	float pitch_acc;
	pitch_acc = 
		atan2f(
				-imu->ax,
				sqrtf(imu->ay*imu->ay +
					imu->az*imu->az));

	roll_acc *= RAD_TO_DEG;
	pitch_acc *= RAD_TO_DEG;

	roll += imu->gx * LOOP_DT;
	pitch += imu->gy * LOOP_DT;
	yaw += imu->gz * LOOP_DT;
	roll =
		AHRS_ALPHA * roll +
		AHRS_BETA * roll_acc;
	pitch =
		AHRS_ALPHA * pitch +
		AHRS_BETA * pitch_acc;


	AP_Vehicle_Set_Attitude(roll,pitch,yaw);

	AP_Debug_Print(DBG_AHRS,
			"\n===== AHRS =====\n"
			"Roll  : %.2f\n"
			"Pitch : %.2f\n"
			"Yaw   : %.2f\n",
			roll,
			pitch,
			yaw);
}

float AP_AHRS_GetRoll(void)
{
	return roll;
}

float AP_AHRS_GetPitch(void)
{
	return pitch;
}

float AP_AHRS_GetYaw(void)
{
	return yaw;
}

