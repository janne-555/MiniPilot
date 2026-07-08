//------------------------------------------------------------------------------
// File    : AP_RC.h
// Purpose : Radio Control Receiver
// Project : MiniPilot
//------------------------------------------------------------------------------

#ifndef AP_RC_H
#define AP_RC_H

#include <stdint.h>

/*----------------------------------------------------------------------------
 * RC Input
 *---------------------------------------------------------------------------*/

typedef struct {
  /* Stick Commands */

  float roll;

  float pitch;

  float yaw;

  float throttle;

  /* Switches */

  uint8_t arm;

  uint8_t mode;

} AP_RC_t;

/*----------------------------------------------------------------------------
 * API
 *---------------------------------------------------------------------------*/

void AP_RC_Init(void);

void AP_RC_Update(void);

/* Get latest RC data */

const AP_RC_t *AP_RC_Get(void);

#endif
