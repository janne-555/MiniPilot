//------------------------------------------------------------------------------
// File    : GCS_VFR_HUD.c
// Purpose : Send VFR HUD Message
// Project : MiniPilot
//------------------------------------------------------------------------------

#include "../AP_HAL/AP_HAL.h"
#include "../AP_Vehicle/AP_Vehicle.h"

#include "GCS_MAVLink.h"

// Send VFR HUD
void GCS_send_vfr_hud(void) {
  mavlink_message_t msg;

  uint8_t buffer[MAVLINK_MAX_PACKET_LEN];

  float roll;
  float pitch;
  float yaw;

  double lat;
  double lon;
  float altitude;

  // Read vehicle attitude
  AP_Vehicle_Get_Attitude(&roll, &pitch, &yaw);

  // Read vehicle GPS
  AP_Vehicle_Get_GPS(&lat, &lon, &altitude);

  // Read vehicle speed
  float groundspeed = AP_Vehicle_Get_GroundSpeed();

  mavlink_msg_vfr_hud_pack(1, 1, &msg,
                           0.0f,                   // Airspeed
                           groundspeed,            // Ground speed
                           (int16_t)(yaw * 57.3f), // Heading
                           0,                      // Throttle
                           altitude,               // Altitude
                           0.0f);                  // Climb

  uint16_t len = mavlink_msg_to_send_buffer(buffer, &msg);

  hal_comm_write(buffer, len);
}
