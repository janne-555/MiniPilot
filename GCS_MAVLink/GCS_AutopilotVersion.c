//------------------------------------------------------------------------------
// File    : GCS_AutopilotVersion.c
// Purpose : Send AUTOPILOT_VERSION
// Project : MiniPilot
//------------------------------------------------------------------------------

#include <stdio.h>

#include "../AP_HAL/AP_HAL.h"

#include "GCS_MAVLink.h"

void GCS_send_autopilot_version(void) {
  mavlink_message_t msg;

  uint8_t buffer[MAVLINK_MAX_PACKET_LEN];

  uint8_t flight_version[8] = {'M', 'I', 'N', 'I', '0', '1', 0, 0};

  uint8_t middleware_version[8] = {'G', 'C', 'S', '0', '1', 0, 0, 0};

  uint8_t os_version[8] = {'L', 'I', 'N', 'U', 'X', 0, 0, 0};

  uint8_t uid2[18] = {0};

  mavlink_msg_autopilot_version_pack(1, 1,

                                     &msg,

                                     MAV_PROTOCOL_CAPABILITY_MAVLINK2 |
                                         MAV_PROTOCOL_CAPABILITY_PARAM_FLOAT |
                                         MAV_PROTOCOL_CAPABILITY_COMMAND_INT,

                                     100, // flight software version

                                     100, // middleware version

                                     1, // OS version

                                     1, // board version

                                     flight_version,

                                     middleware_version,

                                     os_version,

                                     0, // vendor id

                                     0, // product id

                                     12345678, // unique id

                                     uid2);

  uint16_t len;

  len = mavlink_msg_to_send_buffer(buffer, &msg);

  hal_comm_write(buffer, len);

  printf("SEND AUTOPILOT_VERSION\n");
}
