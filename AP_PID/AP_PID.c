//------------------------------------------------------------------------------
// File    : AP_PID.c
// Purpose : PID Controller
// Project : MiniPilot
//------------------------------------------------------------------------------
#include "AP_PID.h"
#include "../AP_Config/AP_Config.h"
#include <stdio.h>
// Initialize PID
void AP_PID_Init(AP_PID_t *pid, float kp, float ki, float kd) {
  pid->kp = kp;
  pid->ki = ki;
  pid->kd = kd;

  pid->integral = 0.0f;
  pid->previous_error = 0.0f;
}

// Update PID
float AP_PID_Update(AP_PID_t *pid, float setpoint, float measurement,
                    float dt) {
  if (dt <= 0.0f) {
    return 0.0f;
  }

  float error = setpoint - measurement;

  pid->integral += error * dt;

  /* Anti-windup */
  if (pid->integral > PID_INTEGRAL_LIMIT) {
    pid->integral = PID_INTEGRAL_LIMIT;
  }

  if (pid->integral < -PID_INTEGRAL_LIMIT) {
    pid->integral = -PID_INTEGRAL_LIMIT;
  }

  float derivative = (error - pid->previous_error) / dt;

  pid->previous_error = error;

  float p = pid->kp * error;
  float i = pid->ki * pid->integral;
  float d = pid->kd * derivative;

  float output = p + i + d;

  /*	printf(
                  "P=%7.2f  I=%7.2f  D=%7.2f  OUT=%7.2f\n",
                  p,
                  i,
                  d,
                  output);
  */
  return output;
}
