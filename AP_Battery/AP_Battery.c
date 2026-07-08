//------------------------------------------------------------------------------
// File    : AP_Battery.c
// Purpose : Battery Monitor
// Project : MiniPilot
//------------------------------------------------------------------------------

#include "AP_Battery.h"
#include "../AP_Debug/AP_Debug.h"
#include "../AP_Failsafe/AP_Failsafe.h"

static AP_Battery_t battery;
static float last_voltage = -1.0f;
static uint8_t last_low = 255;
static uint8_t last_critical = 255;

/*----------------------------------------------------------------------------
  Init
  ----------------------------------------------------------------------------*/

void AP_Battery_Init(void) {
  battery.voltage = 12.2f;

  battery.current = 0.0f;

  battery.consumed_mah = 0.0f;

  battery.remaining_percent = 100.0f;

  battery.healthy = 1;

  battery.low = 0;

  battery.critical = 0;
}

/*----------------------------------------------------------------------------
  Update
  ----------------------------------------------------------------------------*/

void AP_Battery_Update(void) {

  /*
     SIMULATION for now

Later:
voltage = ADC conversion
*/

  battery.voltage -= 0.0005f;

  if (battery.voltage >= 12.6f) {
    battery.remaining_percent = 100;
  } else if (battery.voltage <= 9.9f) {
    battery.remaining_percent = 0;
  } else {
    battery.remaining_percent =
        ((battery.voltage - 9.9f) / (12.6f - 9.9f)) * 100.0f;
  }

  if (battery.remaining_percent < 20) {
    battery.low = 1;
  } else {
    battery.low = 0;
  }

  if (battery.remaining_percent < 10) {
    battery.critical = 1;
  } else {
    battery.critical = 0;
  }

  /*
   * Update failsafe
   */
  AP_Failsafe_SetBattery(battery.low);

  if ((last_voltage < 0) || (battery.low != last_low) ||
      (battery.critical != last_critical) ||
      (last_voltage - battery.voltage > 0.1f)) {
    AP_Debug_Print(DBG_BATTERY,
                   "\n===== BATTERY =====\n"
                   "Voltage   : %.2f V\n"
                   "Current   : %.2f A\n"
                   "Remain    : %.1f %%\n"
                   "Low       : %u\n"
                   "Critical  : %u\n",
                   battery.voltage, battery.current, battery.remaining_percent,
                   battery.low, battery.critical);

    last_voltage = battery.voltage;
    last_low = battery.low;
    last_critical = battery.critical;
  }
}

/* Getters */

const AP_Battery_t *AP_Battery_Get(void) { return &battery; }

float AP_Battery_GetVoltage(void) { return battery.voltage; }

float AP_Battery_GetCurrent(void) { return battery.current; }

float AP_Battery_GetRemaining(void) { return battery.remaining_percent; }

uint8_t AP_Battery_IsLow(void) { return battery.low; }

uint8_t AP_Battery_IsHealthy(void) { return battery.healthy; }
