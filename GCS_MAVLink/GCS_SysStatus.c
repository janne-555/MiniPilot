#include "../AP_HAL/AP_HAL.h"
#include "../libraries/generated/include/mavlink/v2.0/common/mavlink.h"

void GCS_send_sys_status(void)
{
    mavlink_message_t msg;

    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];

    mavlink_msg_sys_status_pack(
        1,      // system id
        1,      // component id
        &msg,

        0,      // onboard_control_sensors_present
        0,      // onboard_control_sensors_enabled
        0,      // onboard_control_sensors_health

        500,    // load (50%)

        12000,  // battery voltage (mV)
        1000,   // current (10A)

        90,     // battery remaining %

        0,      // drop_rate_comm
        0,      // errors_comm

        0,      // errors_count1
        0,      // errors_count2
        0,      // errors_count3
        0,      // errors_count4

        0,      // sensors_present_extended
        0,      // sensors_enabled_extended
        0       // sensors_health_extended
    );

    uint16_t len =
        mavlink_msg_to_send_buffer(
            buffer,
            &msg);

    hal_comm_write(buffer, len);
}
