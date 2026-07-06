//------------------------------------------------------------------------------
// File    : GCS_Attitude.c
// Purpose : Send ATTITUDE Message
// Project : MiniPilot
//------------------------------------------------------------------------------

#include "../AP_HAL/AP_HAL.h"
#include "../AP_Vehicle/AP_Vehicle.h"

#include "GCS_MAVLink.h"

// Send attitude
void GCS_send_attitude(void)
{
    mavlink_message_t msg;

    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];

    float roll;
    float pitch;
    float yaw;

    // Read vehicle attitude
    AP_Vehicle_Get_Attitude(
        &roll,
        &pitch,
        &yaw);

    mavlink_msg_attitude_pack(
        1,
        1,
        &msg,
        hal_millis(),
        roll,
        pitch,
        yaw,
        0.0f,
        0.0f,
        0.0f);

    uint16_t len =
        mavlink_msg_to_send_buffer(
            buffer,
            &msg);

    hal_comm_write(buffer,len);
//printf("SEND ATTITUDE\n");
}
