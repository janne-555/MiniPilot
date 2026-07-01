//------------------------------------------------------------------------------
// File    : AP_AHRS.h
// Purpose : Attitude Estimator
// Project : MiniPilot
//------------------------------------------------------------------------------

#ifndef AP_AHRS_H
#define AP_AHRS_H

/* Initialize AHRS */
void AP_AHRS_Init(void);

/* Update attitude estimation */
void AP_AHRS_Update(void);

/* Get estimated roll angle (degrees) */
float AP_AHRS_GetRoll(void);

/* Get estimated pitch angle (degrees) */
float AP_AHRS_GetPitch(void);

/* Get estimated yaw angle (degrees) */
float AP_AHRS_GetYaw(void);

#endif
