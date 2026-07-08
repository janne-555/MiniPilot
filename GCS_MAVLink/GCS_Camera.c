//------------------------------------------------------------------------------
// File    : GCS_Camera.c
// Purpose : MAVLink Camera / Gimbal Information
// Project : MiniPilot
//------------------------------------------------------------------------------

#include <stdint.h>
#include <stdio.h>

#include "../AP_HAL/AP_HAL.h"

#include "GCS_MAVLink.h"

void GCS_send_camera_information(void) {
  mavlink_message_t msg;

  uint8_t buffer[MAVLINK_MAX_PACKET_LEN];

  uint8_t vendor_name[32] = {'M', 'i', 'n', 'i', 'P', 'i', 'l', 'o', 't'};

  uint8_t model_name[32] = {'N', 'o', 'C', 'a', 'm', 'e', 'r', 'a'};

  char uri[140] = {0};

  mavlink_msg_camera_information_pack(1, 1,

                                      &msg,

                                      hal_millis(),

                                      vendor_name,

                                      model_name,

                                      1, // firmware version

                                      0.0f, // focal length

                                      0.0f, // sensor h

                                      0.0f, // sensor v

                                      0, // resolution h

                                      0, // resolution v

                                      0, // lens id

                                      0, // flags

                                      0, // definition version

                                      uri, // definition uri

                                      0, // gimbal device id

                                      0 // camera device id
  );

  uint16_t len;

  len = mavlink_msg_to_send_buffer(buffer, &msg);

  hal_comm_write(buffer, len);

  printf("SEND CAMERA_INFORMATION\n");
}

void GCS_send_gimbal_information(void)
{
    /*
   * MiniPilot currently has no gimbal.
   *
   * Mission Planner requests this.
   *
   * We safely ignore it.
   */

  printf("GIMBAL ignored\n");
}
