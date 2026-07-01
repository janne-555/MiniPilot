#ifndef AP_PARAM_H
#define AP_PARAM_H

typedef struct
{
    const char *name;
    float value;
} AP_Param_t;

extern AP_Param_t g_params[];
extern const int g_param_count;

#endif
