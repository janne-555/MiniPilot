//------------------------------------------------------------------------------
// File    : AP_Config.h
// Purpose : Global MiniPilot Configuration
// Project : MiniPilot
//------------------------------------------------------------------------------

#ifndef AP_CONFIG_H
#define AP_CONFIG_H

/*----------------------------------------------------------------------------
 * Scheduler
 *---------------------------------------------------------------------------*/

#define LOOP_RATE_HZ           100
#define LOOP_DT                0.01f
/* Scheduler Periods (ms) */

#define TASK_100HZ    10
#define TASK_50HZ     20
#define TASK_10HZ    100
#define TASK_5HZ     200
#define TASK_2HZ     500
#define TASK_1HZ    1000

/*
 * Task delta time (seconds)
 */

#define TASK_100HZ_DT            0.01f

#define TASK_50HZ_DT             0.02f

#define TASK_10HZ_DT             0.10f

#define TASK_5HZ_DT              0.20f

#define TASK_2HZ_DT              0.50f

#define TASK_1HZ_DT              1.00f

/*----------------------------------------------------------------------------
 * AHRS
 *---------------------------------------------------------------------------*/

#define AHRS_ALPHA             0.98f
#define AHRS_BETA              0.02f

/*----------------------------------------------------------------------------
 * Flight Limits
 *---------------------------------------------------------------------------*/

#define MAX_ROLL_ANGLE         45.0f
#define MAX_PITCH_ANGLE        45.0f
#define MAX_YAW_RATE          180.0f

/* Rate limits - deg/sec */

#define MAX_ROLL_RATE       180.0f

#define MAX_PITCH_RATE      180.0f

#define MAX_YAW_RATE        120.0f
/*----------------------------------------------------------------------------
 * RC
 *---------------------------------------------------------------------------*/

#define RC_MIN                (-1.0f)
#define RC_MAX                 (1.0f)

#define RC_THROTTLE_MIN        (0.0f)
#define RC_THROTTLE_MAX        (1.0f)

#define RC_DEADBAND            (0.02f)

/*----------------------------------------------------------------------------
 * PID
 *---------------------------------------------------------------------------*/

#define PID_INTEGRAL_LIMIT    100.0f

/*----------------------------------------------------------------------------
 * Motors
 *---------------------------------------------------------------------------*/

#define MOTOR_MIN_OUTPUT       0.0f
#define MOTOR_MAX_OUTPUT     100.0f

#endif
