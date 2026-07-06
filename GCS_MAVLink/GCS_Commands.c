#include "../AP_HAL/AP_HAL.h"

#include "GCS_MAVLink.h"

void GCS_send_command_ack(uint16_t command)
{
    mavlink_message_t msg;

    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];

    mavlink_msg_command_ack_pack(
        1,
        1,
        &msg,
        command,
        MAV_RESULT_ACCEPTED,
        0,
        0,
        255,
        190);

    uint16_t len =
        mavlink_msg_to_send_buffer(
            buffer,
            &msg);

    hal_comm_write(buffer,len);
}
