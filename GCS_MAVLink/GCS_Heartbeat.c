
//------------------------------------------------------------------------------
// File    : GCS_Heartbeat.c
// Purpose : Send HEARTBEAT Message
// Project : MiniPilot
//------------------------------------------------------------------------------
#include "../AP_HAL/AP_HAL.h"
#include "../AP_Vehicle/AP_Vehicle.h"
#include <stdio.h>

#include "GCS_MAVLink.h"

// Send heartbeat
void GCS_send_heartbeat(void) {
  mavlink_message_t msg;

  uint8_t buffer[MAVLINK_MAX_PACKET_LEN];

  // Read vehicle state
  uint8_t armed = AP_Vehicle_Get_Armed();

  uint8_t mode = AP_Vehicle_Get_Mode();

  uint8_t base_mode = 0;

  // Set armed flag
  if (armed)
{
    base_mode |= MAV_MODE_FLAG_SAFETY_ARMED;
}

  // Enable custom flight mode
  base_mode |= MAV_MODE_FLAG_CUSTOM_MODE_ENABLED;

  // Create heartbeat
  mavlink_msg_heartbeat_pack(1, 1, &msg, MAV_TYPE_QUADROTOR,
                             MAV_AUTOPILOT_ARDUPILOTMEGA, base_mode, mode,
                             MAV_STATE_ACTIVE);

  // Convert to MAVLink packet
  uint16_t len = mavlink_msg_to_send_buffer(buffer, &msg);

  // Send packet
  hal_comm_write(buffer, len);

  printf("SEND HEARTBEAT\n");
}
