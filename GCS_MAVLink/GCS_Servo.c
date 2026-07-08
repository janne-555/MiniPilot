//------------------------------------------------------------------------------
// File    : GCS_Servo.c
// Purpose : Send SERVO_OUTPUT_RAW Message
// Project : MiniPilot
//------------------------------------------------------------------------------

#include <stdio.h>

#include "../AP_HAL/AP_HAL.h"
#include "../AP_Motors/AP_Motors.h"

#include "GCS_MAVLink.h"

static uint16_t motor_to_pwm(float value) {
  /*
   * Motor value:
   *
   * 0.0 -> 1000 us
   * 0.5 -> 1500 us
   * 1.0 -> 2000 us
   */

  if (value < 0.0f) {
    value = 0.0f;
  }

  if (value > 1.0f) {
    value = 1.0f;
  }

  return (uint16_t)(1000 + (value * 1000));
}

void GCS_send_servo_output(void) {
  mavlink_message_t msg;

  uint8_t buffer[MAVLINK_MAX_PACKET_LEN];

  const AP_Motors_Output_t *motors;

  motors = AP_Motors_GetOutput();

  uint16_t m1 = motor_to_pwm(motors->motor[0]);

  uint16_t m2 = motor_to_pwm(motors->motor[1]);

  uint16_t m3 = motor_to_pwm(motors->motor[2]);

  uint16_t m4 = motor_to_pwm(motors->motor[3]);

  mavlink_msg_servo_output_raw_pack(1, 1, &msg,

                                    hal_millis(),

                                    0, // port

                                    m1, // Motor 1
                                    m2, // Motor 2
                                    m3, // Motor 3
                                    m4, // Motor 4

                                    0, 0, 0, 0,

                                    0, 0, 0, 0,

                                    0, 0, 0, 0);

  uint16_t len;

  len = mavlink_msg_to_send_buffer(buffer, &msg);

  hal_comm_write(buffer, len);

  printf("SEND SERVO_OUTPUT_RAW "
         "%u %u %u %u\n",
         m1, m2, m3, m4);
}
