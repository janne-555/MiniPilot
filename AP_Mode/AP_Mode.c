#include "AP_Mode.h"

AP_Mode_t current_mode = MODE_STABILIZE;

void AP_Mode_Set(AP_Mode_t mode)
{
    current_mode = mode;
}
