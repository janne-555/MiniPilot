//------------------------------------------------------------------------------
// File    : GCS_Timesync.c
// Purpose : MAVLink TIMESYNC
// Project : MiniPilot
//------------------------------------------------------------------------------

#include <stdint.h>
#include <stdio.h>

#include "../AP_HAL/AP_HAL.h"

#include "GCS_MAVLink.h"

void GCS_handle_timesync(mavlink_message_t *msg)
{
    mavlink_timesync_t ts;

  mavlink_msg_timesync_decode(msg, &ts);

  mavlink_message_t reply;

  uint8_t buffer[MAVLINK_MAX_PACKET_LEN];

  /*
   * MAVLink rule:
   *
   * Incoming:
   * tc1 = 0
   * ts1 = GCS timestamp
   *
   * Reply:
   * tc1 = autopilot timestamp
   * ts1 = original ts1
   */

  int64_t now_usec;

  now_usec = (int64_t)hal_millis() * 1000;

  mavlink_msg_timesync_pack(1, 1,

                            &reply,

                            now_usec,

                            ts.ts1,

                            msg->sysid,

                            msg->compid);

  uint16_t len;

  len = mavlink_msg_to_send_buffer(buffer, &reply);

  hal_comm_write(buffer, len);

  printf("SEND TIMESYNC\n");
}
