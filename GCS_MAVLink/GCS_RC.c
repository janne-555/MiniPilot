//------------------------------------------------------------------------------
// File    : GCS_RC.c
// Purpose : Send RC_CHANNELS Message
// Project : MiniPilot
//------------------------------------------------------------------------------

#include <stdio.h>

#include "../AP_HAL/AP_HAL.h"
#include "../AP_RC/AP_RC.h"

#include "GCS_MAVLink.h"

void GCS_send_rc_channels(void) {
  mavlink_message_t msg;

  uint8_t buffer[MAVLINK_MAX_PACKET_LEN];

  const AP_RC_t *rc;

  rc = AP_RC_Get();

  /*
   * Mission Planner RC PWM:
   *
   * roll/pitch/yaw:
   * -1.0 -> 1000
   *  0.0 -> 1500
   * +1.0 -> 2000
   *
   * throttle:
   * 0.0 -> 1000
   * 1.0 -> 2000
   */

  uint16_t roll = (uint16_t)(1500 + (rc->roll * 500));

  uint16_t pitch = (uint16_t)(1500 + (rc->pitch * 500));

  uint16_t throttle = (uint16_t)(1000 + (rc->throttle * 1000));

  uint16_t yaw = (uint16_t)(1500 + (rc->yaw * 500));

  uint16_t mode = (uint16_t)(1000 + (rc->mode * 500));

  uint16_t arm = rc->arm ? 2000 : 1000;

  mavlink_msg_rc_channels_pack(1, 1, &msg,

                               hal_millis(),

                               18,

                               roll,     // CH1
                               pitch,    // CH2
                               throttle, // CH3
                               yaw,      // CH4

                               mode, // CH5
                               arm,  // CH6

                               1500, // CH7
                               1500, // CH8

                               0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

                               255);

  uint16_t len;

  len = mavlink_msg_to_send_buffer(buffer, &msg);

  hal_comm_write(buffer, len);

  printf("SEND RC_CHANNELS\n");
}
