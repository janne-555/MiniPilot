//------------------------------------------------------------------------------
// File    : GCS_ProtocolVersion.c
// Purpose : Send MAVLink PROTOCOL_VERSION
// Project : MiniPilot
//------------------------------------------------------------------------------

#include <stdio.h>

#include "../AP_HAL/AP_HAL.h"

#include "GCS_MAVLink.h"

void GCS_send_protocol_version(void) {
  mavlink_message_t msg;

  uint8_t buffer[MAVLINK_MAX_PACKET_LEN];

  uint8_t spec_hash[8] = {0};

  uint8_t library_hash[8] = {0};

  mavlink_msg_protocol_version_pack(1, 1,

                                    &msg,

                                    200, // MAVLink 2.0

                                    100, // minimum MAVLink 1.0

                                    200, // maximum MAVLink 2.0

                                    spec_hash,

                                    library_hash);

  uint16_t len;

  len = mavlink_msg_to_send_buffer(buffer, &msg);

  hal_comm_write(buffer, len);

  printf("SEND PROTOCOL_VERSION\n");
}
