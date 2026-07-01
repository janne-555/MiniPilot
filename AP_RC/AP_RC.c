//------------------------------------------------------------------------------
// File    : AP_RC.c
// Purpose : RC Input Driver
// Project : MiniPilot
//------------------------------------------------------------------------------

#include "AP_RC.h"

static AP_RC_Data_t rc;

// Initialize RC
void AP_RC_Init(void)
{
    rc.roll = 1500;

    rc.pitch = 1500;

    rc.throttle = 1000;

    rc.yaw = 1500;
}

// Update RC
void AP_RC_Update(void)
{
    // Simulation
}

// Read RC
void AP_RC_Get(AP_RC_Data_t *data)
{
    *data = rc;
}
