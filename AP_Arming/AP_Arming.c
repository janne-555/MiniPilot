#include "AP_Arming.h"

int vehicle_armed = 0;

void AP_Arming_Arm(void)
{
    vehicle_armed = 1;
}

void AP_Arming_Disarm(void)
{
    vehicle_armed = 0;
}
