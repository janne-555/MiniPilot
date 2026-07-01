//------------------------------------------------------------------------------
// File    : main.c
// Purpose : MiniPilot Main Entry
// Project : MiniPilot
//------------------------------------------------------------------------------

#include <stdio.h>
#include "AP_HAL/AP_HAL.h"
#include "AP_Scheduler/AP_Scheduler.h"
#include "AP_Vehicle/AP_Vehicle.h"
#include "AP_GPS/AP_GPS.h"
#include "AP_IMU/AP_IMU.h"
#include "AP_AHRS/AP_AHRS.h"
#include "AP_RC/AP_RC.h"
#include "AP_Control/AP_Control.h"
#include "AP_Motors/AP_Motors.h"
#include "AP_Sim/AP_Sim.h"
#include "AP_Mixer/AP_Mixer.h"
#include "GCS_MAVLink/GCS_MAVLink.h"


#define CONTROL_DT 0.01f
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
// AHRS
static void Task_AHRS(void)
{
    AP_AHRS_Update();
}
// Flight Controller
static void Task_Control(void)
{
    AP_Control_Update(CONTROL_DT);
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
//----------------------------
// 10 Hz Tasks
//----------------------------
// Send Attitude
static void Task_Attitude(void)
{
    GCS_send_attitude();
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
//------------------------------------------------------------------------------
// Main
//------------------------------------------------------------------------------
int main(void)
{
    //----------------------------------------------------------------------
    // HAL
    //----------------------------------------------------------------------
    if (hal_init() < 0)
    {
        printf("HAL Init Failed\n");
        return -1;
    }
    printf("MiniPilot Started\n");
    //----------------------------------------------------------------------
    // Initialize Modules
    //----------------------------------------------------------------------
    AP_Vehicle_Init();
    AP_GPS_Init();
    AP_IMU_Init();
    AP_RC_Init();
    AP_Control_Init();
    AP_Mixer_Init();
    AP_Motors_Init();
    AP_Sim_Init();


    //----------------------------------------------------------------------
    // Scheduler
    //----------------------------------------------------------------------
    AP_Scheduler_Init();
    //----------------------------------------------------------------------
    // Register 100 Hz Tasks
    //----------------------------------------------------------------------
    AP_Scheduler_Add_Task(Task_IMU,10);
    AP_Scheduler_Add_Task(Task_AHRS,10);
    AP_Scheduler_Add_Task(Task_Control,10);
    AP_Scheduler_Add_Task(Task_Mixer,10);
    AP_Scheduler_Add_Task(Task_Motors,10);
    //----------------------------------------------------------------------
    // Register 50 Hz Tasks
    //----------------------------------------------------------------------
    AP_Scheduler_Add_Task(Task_RC,20);
    AP_Scheduler_Add_Task(Task_GCS,20);
    //----------------------------------------------------------------------
    // Register 5 Hz Tasks
    //----------------------------------------------------------------------
    AP_Scheduler_Add_Task(Task_GPS,200);
    //----------------------------------------------------------------------
    // Register 10 Hz Tasks
    //----------------------------------------------------------------------
    AP_Scheduler_Add_Task(Task_Attitude,100);
    //----------------------------------------------------------------------
    // Register 2 Hz Tasks
    //----------------------------------------------------------------------
    AP_Scheduler_Add_Task(Task_VFR_HUD,500);
    //----------------------------------------------------------------------
    // Register 1 Hz Tasks
    AP_Scheduler_Add_Task(Task_Heartbeat,1000);
    AP_Scheduler_Add_Task(Task_SysStatus,1000);
    //----------------------------------------------------------------------
    // Main Loop
    //----------------------------------------------------------------------
    while (1)
    {
        AP_Scheduler_Run();

    }
    return 0;
}
