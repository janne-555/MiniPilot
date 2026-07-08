//------------------------------------------------------------------------------
// File    : GCS_GlobalPosition.c
// Purpose : Send GLOBAL_POSITION_INT Message
// Project : MiniPilot
//------------------------------------------------------------------------------

#include <stdint.h>
#include <stdio.h>

#include "../AP_HAL/AP_HAL.h"
#include "../AP_Vehicle/AP_Vehicle.h"

#include "GCS_MAVLink.h"

void GCS_send_global_position(void) {
  mavlink_message_t msg;

  uint8_t buffer[MAVLINK_MAX_PACKET_LEN];

  double latitude;
  double longitude;

  float altitude;

  /*
   * Read EKF fused position through vehicle
   */

  AP_Vehicle_Get_GPS(&latitude, &longitude, &altitude);

  /*
   * MAVLink units:
   *
   * lat/lon : degrees * 1E7
   * altitude: millimeters
   */

  int32_t lat = (int32_t)(latitude * 10000000.0);

  int32_t lon = (int32_t)(longitude * 10000000.0);

  int32_t alt = (int32_t)(altitude * 1000.0f);

  /*
   * Velocity
   *
   * Later from EKF velocity
   */

  int16_t vx = 0;

  int16_t vy = 0;

  int16_t vz = 0;

  /*
   * Heading
   *
   * centi-degrees
   */

  float roll;
  float pitch;
  float yaw;

  AP_Vehicle_Get_Attitude(&roll, &pitch, &yaw);

  uint16_t heading = (uint16_t)(yaw * 100.0f);

  mavlink_msg_global_position_int_pack(1, 1,

                                       &msg,

                                       hal_millis(),

                                       lat,

                                       lon,

                                       alt,

                                       alt,

                                       vx,

                                       vy,

                                       vz,

                                       heading);

  uint16_t len = mavlink_msg_to_send_buffer(buffer, &msg);

  hal_comm_write(buffer, len);

  //    printf("SEND GLOBAL POSITION\n");
}
