#include "AP_Param.h"

AP_Param_t g_params[] =
{
    {"SYSID_THISMAV", 1},
    {"ARMING_CHECK", 1},
    {"RTL_ALT", 1500},
    {"BATT_CAPACITY", 2200},
    {"FS_THR_ENABLE", 1}
};

const int g_param_count =
    sizeof(g_params) /
    sizeof(g_params[0]);
