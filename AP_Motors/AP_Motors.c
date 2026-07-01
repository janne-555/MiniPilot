//------------------------------------------------------------------------------
// File    : AP_Motors.c
// Purpose : Motor Driver
// Project : MiniPilot
//------------------------------------------------------------------------------
//
// Receives motor commands from AP_Mixer.
//
// Current Target:
//      Linux Simulator
//
// Future Target:
//      STM32 PWM
//      ESC
//      Brushless Motors
//
//------------------------------------------------------------------------------

#include "AP_Motors.h"

#include "../AP_Mixer/AP_Mixer.h"

#include <stdio.h>

/*----------------------------------------------------------------------------
 * Private Variables
 *---------------------------------------------------------------------------*/

static AP_Motors_Output_t motors;

/*----------------------------------------------------------------------------
 * Initialize
 *---------------------------------------------------------------------------*/

void AP_Motors_Init(void)
{
    motors.motor1 = 0.0f;
    motors.motor2 = 0.0f;
    motors.motor3 = 0.0f;
    motors.motor4 = 0.0f;
}

/*----------------------------------------------------------------------------
 * Update
 *---------------------------------------------------------------------------*/

void AP_Motors_Update(void)
{
    const AP_Mixer_Output_t *mixer;

    mixer = AP_Mixer_GetOutput();

    motors.motor1 = mixer->motor1;
    motors.motor2 = mixer->motor2;
    motors.motor3 = mixer->motor3;
    motors.motor4 = mixer->motor4;

    /* Motor limits */
    if(motors.motor1 < 0.0f) motors.motor1 = 0.0f;
    if(motors.motor2 < 0.0f) motors.motor2 = 0.0f;
    if(motors.motor3 < 0.0f) motors.motor3 = 0.0f;
    if(motors.motor4 < 0.0f) motors.motor4 = 0.0f;

    if(motors.motor1 > 100.0f) motors.motor1 = 100.0f;
    if(motors.motor2 > 100.0f) motors.motor2 = 100.0f;
    if(motors.motor3 > 100.0f) motors.motor3 = 100.0f;
    if(motors.motor4 > 100.0f) motors.motor4 = 100.0f;

    printf("Motor : %.2f %.2f %.2f %.2f\n",
            motors.motor1,
            motors.motor2,
            motors.motor3,
            motors.motor4);
}

/*----------------------------------------------------------------------------
 * Get Outputs
 *---------------------------------------------------------------------------*/

const AP_Motors_Output_t *AP_Motors_GetOutput(void)
{
    return &motors;
}
