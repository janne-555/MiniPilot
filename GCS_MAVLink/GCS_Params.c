#include "../AP_HAL/AP_HAL.h"
#include "../AP_Param/AP_Param.h"

#include "../libraries/generated/include/mavlink/v2.0/common/mavlink.h"

void GCS_send_param(uint16_t index)
{
    if(index >= g_param_count)
        return;

    mavlink_message_t msg;

    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];

    mavlink_msg_param_value_pack(
        1,
        1,
        &msg,
        g_params[index].name,
        g_params[index].value,
        MAV_PARAM_TYPE_REAL32,
        g_param_count,
        index);

    uint16_t len =
        mavlink_msg_to_send_buffer(
            buffer,
            &msg);

    hal_comm_write(buffer,len);
}
