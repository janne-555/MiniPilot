#include "GCS_MAVLink.h"
#include <stdio.h>

#include "../AP_HAL/AP_HAL.h"

void GCS_send_statustext(const char *text)
{
    mavlink_message_t msg;

  uint8_t buffer[MAVLINK_MAX_PACKET_LEN];

  mavlink_msg_statustext_pack(1, // system id
                              1, // component id
                              &msg, MAV_SEVERITY_INFO, text, 0, 0);

  uint16_t len = mavlink_msg_to_send_buffer(buffer, &msg);

  hal_comm_write(buffer, len);

  printf("STATUSTEXT: %s\n", text);
}
