//------------------------------------------------------------------------------
// File    : AP_Logger.c
// Purpose : Flight Data Logger
// Project : MiniPilot
//------------------------------------------------------------------------------

#include "AP_Logger.h"

#include "../AP_AHRS/AP_AHRS.h"
#include "../AP_Arming/AP_Arming.h"
#include "../AP_Battery/AP_Battery.h"
#include "../AP_Failsafe/AP_Failsafe.h"
#include "../AP_FlightMode/AP_FlightMode.h"
#include "../AP_Motors/AP_Motors.h"

#include <stdio.h>
#include <sys/time.h>

/*----------------------------------------------------------------------------
 Private
----------------------------------------------------------------------------*/

static AP_Logger_t logger;

static FILE *log_file;

static uint64_t boot_time_us;

/*----------------------------------------------------------------------------
 TimeUS
----------------------------------------------------------------------------*/

uint64_t AP_Logger_TimeUS(void)
{
    struct timeval tv;

  uint64_t now;

  gettimeofday(&tv, NULL);

  now = ((uint64_t)tv.tv_sec * 1000000ULL) + tv.tv_usec;

  return now - boot_time_us;
}

/*----------------------------------------------------------------------------
 Init
----------------------------------------------------------------------------*/

void AP_Logger_Init(void) {

  struct timeval tv;

  logger.enabled = 0;

  logger.messages = 0;

  gettimeofday(&tv, NULL);

  boot_time_us = ((uint64_t)tv.tv_sec * 1000000ULL) + tv.tv_usec;

  log_file = fopen("flight.log", "w");

  if (log_file) {
    logger.enabled = 1;

    fprintf(log_file, "# MiniPilot Flight Log\n");

    fprintf(log_file, "# TYPE,TimeUS,DATA\n");

    fflush(log_file);

    printf("Logger Started\n");
  } else {
    printf("Logger Failed\n");
  }
}

/*----------------------------------------------------------------------------
 Update
----------------------------------------------------------------------------*/

void AP_Logger_Update(void)
{
    if (!logger.enabled)
    return;

  AP_Logger_Write_Attitude();

  AP_Logger_Write_Battery();

  AP_Logger_Write_Motors();

  AP_Logger_Write_Mode();

  AP_Logger_Write_Arming();

  AP_Logger_Write_Failsafe();

  fflush(log_file);
}

/*----------------------------------------------------------------------------
 Attitude
----------------------------------------------------------------------------*/

void AP_Logger_Write_Attitude(void)
{
    fprintf(log_file,

          "ATT,%llu,%.2f,%.2f,%.2f\n",

          (unsigned long long)AP_Logger_TimeUS(),

          AP_AHRS_GetRoll(),

          AP_AHRS_GetPitch(),

          AP_AHRS_GetYaw());

  logger.messages++;
}

/*----------------------------------------------------------------------------
 Battery
----------------------------------------------------------------------------*/

void AP_Logger_Write_Battery(void)
{
    fprintf(log_file,

          "BAT,%llu,%.2f,%.2f,%.1f\n",

          (unsigned long long)AP_Logger_TimeUS(),

          AP_Battery_GetVoltage(),

          AP_Battery_GetCurrent(),

          AP_Battery_GetRemaining());

  logger.messages++;
}

/*----------------------------------------------------------------------------
 Motors
----------------------------------------------------------------------------*/

void AP_Logger_Write_Motors(void)
{
    const AP_Motors_Output_t *m;

  m = AP_Motors_GetOutput();

  fprintf(log_file,

          "MOT,%llu,%.2f,%.2f,%.2f,%.2f\n",

          (unsigned long long)AP_Logger_TimeUS(),

          m->motor[0],

          m->motor[1],

          m->motor[2],

          m->motor[3]);

  logger.messages++;
}

/*----------------------------------------------------------------------------
 Mode
----------------------------------------------------------------------------*/

void AP_Logger_Write_Mode(void)
{
    fprintf(log_file,

          "MODE,%llu,%d\n",

          (unsigned long long)AP_Logger_TimeUS(),

          AP_FlightMode_GetMode());

  logger.messages++;
}

/*----------------------------------------------------------------------------
 Arming
----------------------------------------------------------------------------*/

void AP_Logger_Write_Arming(void)
{
    fprintf(log_file,

          "ARM,%llu,%u\n",

          (unsigned long long)AP_Logger_TimeUS(),

          AP_Arming_IsArmed());

  logger.messages++;
}

/*----------------------------------------------------------------------------
 Failsafe
----------------------------------------------------------------------------*/

void AP_Logger_Write_Failsafe(void)
{
    fprintf(log_file,

          "FS,%llu,%u,%d\n",

          (unsigned long long)AP_Logger_TimeUS(),

          AP_Failsafe_IsActive(),

          AP_Failsafe_GetReason());

  logger.messages++;
}

/*----------------------------------------------------------------------------
 Events
----------------------------------------------------------------------------*/

void AP_Logger_Write_Event(const char *event)
{
    fprintf(log_file,

          "EV,%llu,%s\n",

          (unsigned long long)AP_Logger_TimeUS(),

          event);

  fflush(log_file);

  logger.messages++;
}

/*----------------------------------------------------------------------------
 Getter
----------------------------------------------------------------------------*/

const AP_Logger_t *AP_Logger_Get(void) { return &logger; }
