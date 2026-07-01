//------------------------------------------------------------------------------
// File    : AP_Motors.h
// Purpose : Motor Output Driver
// Project : MiniPilot
//------------------------------------------------------------------------------

#ifndef AP_MOTORS_H
#define AP_MOTORS_H

/*----------------------------------------------------------------------------
 * Motor Outputs
 *---------------------------------------------------------------------------*/

typedef struct
{
    float motor1;
    float motor2;
    float motor3;
    float motor4;

} AP_Motors_Output_t;

/*----------------------------------------------------------------------------
 * API
 *---------------------------------------------------------------------------*/

void AP_Motors_Init(void);

void AP_Motors_Update(void);

/* Get latest motor outputs */
const AP_Motors_Output_t *AP_Motors_GetOutput(void);

#endif
