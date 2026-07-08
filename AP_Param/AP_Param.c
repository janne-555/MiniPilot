//------------------------------------------------------------------------------
// File    : AP_Param.c
// Purpose : Parameter Storage
// Project : MiniPilot
//------------------------------------------------------------------------------

#include "AP_Param.h"

#include <string.h>

AP_Param_t g_params[] = {{"SYSID_THISMAV", 1.0f},

                         {"ARMING_CHECK", 1.0f},

                         {"RTL_ALT", 1500.0f},

                         {"BATT_CAPACITY", 2200.0f},

                         {"FS_THR_ENABLE", 1.0f},

                         /* Controller */

                         {"ROLL_P", 4.5f},

                         {"ROLL_I", 0.1f},

                         {"ROLL_D", 0.02f},

                         {"PITCH_P", 4.5f},

                         {"PITCH_I", 0.1f},

                         {"PITCH_D", 0.02f},

                         {"ALT_P", 1.0f}};

const uint16_t g_param_count = sizeof(g_params) / sizeof(g_params[0]);

float AP_Param_Get(const char *name) {
  for (uint16_t i = 0; i < g_param_count; i++) {
    if (strcmp(g_params[i].name, name) == 0) {
      return g_params[i].value;
    }
  }

  return 0.0f;
}

void AP_Param_Set(const char *name, float value) {
  for (uint16_t i = 0; i < g_param_count; i++) {
    if (strcmp(g_params[i].name, name) == 0) {
      g_params[i].value = value;
      return;
    }
  }
}
