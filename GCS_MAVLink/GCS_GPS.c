//------------------------------------------------------------------------------
// File    : GCS_GPS.c
// Purpose : Send GPS_RAW_INT Message
// Project : MiniPilot
//------------------------------------------------------------------------------

#include "../AP_HAL/AP_HAL.h"
#include "../AP_Vehicle/AP_Vehicle.h"

#include "../libraries/generated/include/mavlink/v2.0/common/mavlink.h"

// Send GPS
void GCS_send_gps_raw_int(void)
{
    mavlink_message_t msg;

    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];

    double latitude;
    double longitude;
    float altitude;

    // Read GPS
    AP_Vehicle_Get_GPS(
        &latitude,
        &longitude,
        &altitude);

    int32_t lat =
        (int32_t)(latitude * 10000000.0);

    int32_t lon =
        (int32_t)(longitude * 10000000.0);

    int32_t alt =
        (int32_t)(altitude * 1000.0);

    mavlink_msg_gps_raw_int_pack(
        1,
        1,
        &msg,
        0,
        3,
        lat,
        lon,
        alt,
        100,
        100,
        0,
        0,
        10,
        alt,
        100,
        100,
        100,
        100,
        0);

    uint16_t len =
        mavlink_msg_to_send_buffer(
            buffer,
            &msg);

    hal_comm_write(buffer,len);
}
