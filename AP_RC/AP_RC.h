//------------------------------------------------------------------------------
// File    : AP_RC.h
// Purpose : RC Input Driver
// Project : MiniPilot
//------------------------------------------------------------------------------

#ifndef AP_RC_H
#define AP_RC_H

#include <stdint.h>

typedef struct
{
    uint16_t roll;

    uint16_t pitch;

    uint16_t throttle;

    uint16_t yaw;

} AP_RC_Data_t;

// Initialize RC
void AP_RC_Init(void);

// Update RC
void AP_RC_Update(void);

// Read RC
void AP_RC_Get(AP_RC_Data_t *rc);

#endif
