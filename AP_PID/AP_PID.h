//------------------------------------------------------------------------------
// File    : AP_PID.h
// Purpose : PID Controller
// Project : MiniPilot
//------------------------------------------------------------------------------

#ifndef AP_PID_H
#define AP_PID_H

typedef struct
{
    float kp;
    float ki;
    float kd;

    float integral;
    float previous_error;

} AP_PID_t;

// Initialize PID
void AP_PID_Init(AP_PID_t *pid,
                 float kp,
                 float ki,
                 float kd);

// Calculate PID output
float AP_PID_Update(AP_PID_t *pid,
                    float setpoint,
                    float measurement,
                    float dt);

#endif
