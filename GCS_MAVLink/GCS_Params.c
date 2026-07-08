//------------------------------------------------------------------------------
// File    : GCS_Params.c
// Purpose : MAVLink Parameter Handler
// Project : MiniPilot
//------------------------------------------------------------------------------

#include "../AP_HAL/AP_HAL.h"

#include "../AP_Param/AP_Param.h"

#include "GCS_MAVLink.h"

#include <stdio.h>
#include <string.h>

void GCS_send_param(uint16_t index) {
  if (index >= g_param_count) {
    return;
  }

  mavlink_message_t msg;

  uint8_t buffer[MAVLINK_MAX_PACKET_LEN];

  char id[16] = {0};

  strncpy(id, g_params[index].name, sizeof(id));

  mavlink_msg_param_value_pack(1, 1, &msg,

                               id,

                               g_params[index].value,

                               MAV_PARAM_TYPE_REAL32,

                               g_param_count,

                               index);

  uint16_t len = mavlink_msg_to_send_buffer(buffer, &msg);

  hal_comm_write(buffer, len);

  printf("RX MAV ID = %u\n", msg.msgid);
}

void GCS_Handle_Param_Set(mavlink_message_t *msg)
{
    mavlink_param_set_t pkt;

  mavlink_msg_param_set_decode(msg, &pkt);

  // update MiniPilot parameter
  AP_Param_Set(pkt.param_id, pkt.param_value);

  // send confirmation back
  mavlink_message_t reply;

  mavlink_msg_param_value_pack(1, MAV_COMP_ID_AUTOPILOT1, &reply,

                               pkt.param_id, pkt.param_value,

                               MAV_PARAM_TYPE_REAL32,

                               g_param_count, 0);

  uint8_t buffer[MAVLINK_MAX_PACKET_LEN];

  uint16_t len = mavlink_msg_to_send_buffer(buffer, &reply);
  hal_comm_write(buffer, len);
}
