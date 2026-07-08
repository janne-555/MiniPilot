//------------------------------------------------------------------------------
// File    : GCS_SystemTime.c
// Purpose : Send MAVLink SYSTEM_TIME
// Project : MiniPilot
//------------------------------------------------------------------------------

#include <stdint.h>
#include <stdio.h>

#include "../AP_HAL/AP_HAL.h"

#include "GCS_MAVLink.h"

void GCS_send_system_time(void) {
  mavlink_message_t msg;

  uint8_t buffer[MAVLINK_MAX_PACKET_LEN];

  uint64_t unix_time;

  unix_time = 0;

  uint32_t boot_time;

  boot_time = hal_millis();

  mavlink_msg_system_time_pack(1, 1, &msg,

                               unix_time,

                               boot_time);

  uint16_t len;

  len = mavlink_msg_to_send_buffer(buffer, &msg);

  hal_comm_write(buffer, len);

  printf("SEND SYSTEM_TIME\n");
}
