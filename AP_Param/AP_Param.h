//------------------------------------------------------------------------------
// File    : AP_Param.h
// Purpose : Parameter System
// Project : MiniPilot
//------------------------------------------------------------------------------

#ifndef AP_PARAM_H
#define AP_PARAM_H

#include <stdint.h>

typedef struct {
  const char *name;
  float value;

} AP_Param_t;

extern AP_Param_t g_params[];

extern const uint16_t g_param_count;

float AP_Param_Get(const char *name);

void AP_Param_Set(const char *name, float value);

#endif
