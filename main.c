//------------------------------------------------------------------------------
// File    : main.c
// Purpose : MiniPilot Main Entry
// Project : MiniPilot
//------------------------------------------------------------------------------

#include <stdio.h>
#include "AP_HAL/AP_HAL.h"
#include "AP_Config/AP_Config.h"
#include "AP_Scheduler/AP_Scheduler.h"
#include "AP_Vehicle/AP_Vehicle.h"
#include "AP_GPS/AP_GPS.h"
#include "AP_IMU/AP_IMU.h"
#include "AP_EKF/AP_EKF.h"
#include "AP_AHRS/AP_AHRS.h"
#include "AP_RC/AP_RC.h"
#include "AP_Control/AP_Control.h"
#include "AP_Motors/AP_Motors.h"
#include "AP_Arming/AP_Arming.h"
#include "AP_Battery/AP_Battery.h"
#include "AP_Baro/AP_Baro.h"
#include "AP_Sim/AP_Sim.h"
#include "AP_Mixer/AP_Mixer.h"
#include "AP_Debug/AP_Debug.h"
#include "AP_Input/AP_Keyboard.h"
#include "AP_InertialNav/AP_InertialNav.h"
#include "AP_FlightMode/AP_FlightMode.h"
#include "AP_Failsafe/AP_Failsafe.h"
#include "AP_Param/AP_Param.h"
#include "AP_Compass/AP_Compass.h"
#include "GCS_MAVLink/GCS_MAVLink.h"
#include "GCS_MAVLink/GCS_Statustext.h"

//------------------------------------------------------------------------------
// Scheduler Tasks
//------------------------------------------------------------------------------
//----------------------------
// 100 Hz Flight Control Tasks
//----------------------------
// IMU
static void Task_IMU(void)
{
	AP_IMU_Update();
}
static void Task_EKF(void)
{
    AP_EKF_Update(LOOP_DT);
}
// AHRS
static void Task_AHRS(void)
{
	AP_AHRS_Update();
}
// Flight Controller
static void Task_Control(void)
{
	AP_Control_Update(LOOP_DT);
}
// Mixer
static void Task_Mixer(void)
{
	AP_Mixer_Update();
}
// Motors
static void Task_Motors(void)
{
	AP_Motors_Update();
}
static void Task_Sim(void)
{
	AP_Sim_Update(LOOP_DT);
}
//----------------------------
// 50 Hz Tasks
//----------------------------
// RC Receiver
static void Task_RC(void)
{
	AP_RC_Update();
}
// Ground Control Station
static void Task_GCS(void)
{
	GCS_update();
}
static void Task_InertialNav(void)
{
	AP_InertialNav_Update(TASK_50HZ);
}
static void Task_Vehicle(void)
{
	AP_Vehicle_Update();
}
static void Task_Baro(void)
{
	AP_Baro_Update();
}
//----------------------------
// 5 Hz Tasks
//----------------------------
// GPS Driver
static void Task_GPS_Driver(void)
{
	AP_GPS_Update();
}
// Send GPS
static void Task_GPS(void)
{
	GCS_send_gps_raw_int();
}
static void Task_FlightMode(void)
{
	AP_FlightMode_Update();
}
static void Task_GlobalPosition(void)
{
    GCS_send_global_position();
}
//----------------------------
// 10 Hz Tasks
//----------------------------
// Send Attitude
static void Task_Attitude(void)
{
	GCS_send_attitude();
}

static void Task_Arming(void)
{
	AP_Arming_Update();
}
static void Task_Failsafe(void)
{
	AP_Failsafe_Update();
}
static void Task_Battery(void)
{
	AP_Battery_Update();
}
// Compass
static void Task_Compass(void)
{
    AP_Compass_Update();
}
//----------------------------
// 2 Hz Tasks
//----------------------------
// Send VFR HUD
static void Task_VFR_HUD(void)
{
	GCS_send_vfr_hud();
}
//----------------------------
// 1 Hz Tasks
//----------------------------
// Heartbeat
static void Task_Heartbeat(void)
{
	GCS_send_heartbeat();
}
// System Status
static void Task_SysStatus(void)
{
	GCS_send_sys_status();
}
static void Task_EKFStatus(void)
{
    GCS_send_ekf_status();
}
//------------------------------------------------------------------------------
// Main
//------------------------------------------------------------------------------
int main(void)
{
    if (hal_init() < 0)
    {
        printf("HAL Init Failed\n");
        return -1;
    }

    printf("MiniPilot Started\n");

    AP_Debug_Init();

    AP_Keyboard_Init();
    AP_Sim_Init();

    AP_IMU_Init();
    AP_Compass_Init();
    AP_GPS_Init();
    AP_Baro_Init();
    AP_Battery_Init();

    AP_AHRS_Init();
    AP_InertialNav_Init();
    AP_EKF_Init();

    AP_Vehicle_Init();

    AP_RC_Init();
    AP_FlightMode_Init();

    AP_Control_Init();
    AP_Mixer_Init();
    AP_Motors_Init();

    AP_Arming_Init();
    AP_Failsafe_Init();


    AP_Debug_Enable(DBG_RC);
    AP_Debug_Enable(DBG_CONTROL);
    AP_Debug_Enable(DBG_BARO);
    AP_Debug_Enable(DBG_IMU);
    AP_Debug_Enable(DBG_INAV);
    AP_Debug_Enable(DBG_MIXER);
    AP_Debug_Enable(DBG_MOTORS);
    AP_Debug_Enable(DBG_ARMING);
    AP_Debug_Enable(DBG_BATTERY);
    AP_Debug_Enable(DBG_FAILSAFE);
    AP_Debug_Enable(DBG_POS);
    AP_Debug_Enable(DBG_NAV);
    AP_Debug_Enable(DBG_COMPASS);
    AP_Debug_Enable(DBG_EKF);
    AP_Debug_Enable(DBG_VEHICLE);


    AP_Scheduler_Init();


    /* 100Hz */

    AP_Scheduler_Add_Task(Task_Sim,TASK_100HZ);
    AP_Scheduler_Add_Task(Task_IMU,TASK_100HZ);
    AP_Scheduler_Add_Task(Task_AHRS,TASK_100HZ);
    AP_Scheduler_Add_Task(Task_EKF,TASK_100HZ);
    AP_Scheduler_Add_Task(Task_Control,TASK_100HZ);
    AP_Scheduler_Add_Task(Task_Mixer,TASK_100HZ);
    AP_Scheduler_Add_Task(Task_Motors,TASK_100HZ);


    /* 50Hz */

    AP_Scheduler_Add_Task(Task_GCS,TASK_50HZ);
    AP_Scheduler_Add_Task(Task_RC,TASK_50HZ);
    AP_Scheduler_Add_Task(Task_Baro,TASK_50HZ);
    AP_Scheduler_Add_Task(Task_InertialNav,TASK_50HZ);
    AP_Scheduler_Add_Task(Task_FlightMode,TASK_50HZ);
    AP_Scheduler_Add_Task(Task_Vehicle,TASK_50HZ);
	AP_Scheduler_Add_Task(Task_Baro,TASK_50HZ);


	//================================================
	// 10HZ
	//================================================

	AP_Scheduler_Add_Task(Task_Attitude,TASK_10HZ);


	AP_Scheduler_Add_Task(Task_Compass,TASK_10HZ);

	AP_Scheduler_Add_Task(Task_Arming,TASK_10HZ);

	AP_Scheduler_Add_Task(Task_Failsafe,TASK_10HZ);

	AP_Scheduler_Add_Task(Task_Battery,TASK_10HZ);
	

	//================================================
	// 5HZ
	//================================================

	AP_Scheduler_Add_Task(Task_GPS_Driver,TASK_5HZ);

	AP_Scheduler_Add_Task(Task_GPS,TASK_5HZ);

	AP_Scheduler_Add_Task(Task_GlobalPosition,TASK_5HZ);


	//================================================
	// 2HZ
	//================================================

	AP_Scheduler_Add_Task(Task_VFR_HUD,TASK_2HZ);


	//================================================
	// 1HZ
	//================================================

	AP_Scheduler_Add_Task(Task_Heartbeat,TASK_1HZ);

	AP_Scheduler_Add_Task(Task_SysStatus,TASK_1HZ);
	
	AP_Scheduler_Add_Task(Task_EKFStatus,TASK_1HZ);

	//----------------------------------------------------------------------
	// Main Loop
	//----------------------------------------------------------------------
	while (1)
	{

		AP_Scheduler_Run();

	}
	AP_Keyboard_Close();
	return 0;
}
