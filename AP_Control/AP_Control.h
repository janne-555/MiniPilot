
//------------------------------------------------------------------------------
// File    : AP_Control.h
// Purpose : Flight Controller
// Project : MiniPilot
//------------------------------------------------------------------------------

#ifndef AP_CONTROL_H
#define AP_CONTROL_H
typedef struct
{
    /* Roll PID output */
    float roll_output;

    /* Pitch PID output */
    float pitch_output;

    /* Yaw PID output */
    float yaw_output;

    /* Throttle output */
    float throttle_output;

} AP_Control_Output_t;

void AP_Control_Init(void);

void AP_Control_Update(float dt);

const AP_Control_Output_t *AP_Control_GetOutput(void);

#endif
