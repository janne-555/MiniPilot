//------------------------------------------------------------------------------
// File    : GCS_SysStatus.c
// Purpose : Send SYS_STATUS Message
// Project : MiniPilot
//------------------------------------------------------------------------------

#include <stdio.h>

#include "../AP_HAL/AP_HAL.h"
#include "../AP_Battery/AP_Battery.h"

#include "GCS_MAVLink.h"


void GCS_send_sys_status(void)
{
    mavlink_message_t msg;

    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];


    const AP_Battery_t *battery;

    battery = AP_Battery_Get();


    uint16_t voltage_mv;

    voltage_mv =
        (uint16_t)(battery->voltage * 1000.0f);


    int16_t current_ca;

    current_ca =
        (int16_t)(battery->current * 100.0f);


    int8_t remaining;

    remaining =
        (int8_t)battery->remaining_percent;



    mavlink_msg_sys_status_pack(
        1,
        1,
        &msg,


        MAV_SYS_STATUS_SENSOR_3D_GYRO |
        MAV_SYS_STATUS_SENSOR_3D_ACCEL |
        MAV_SYS_STATUS_SENSOR_GPS,

        MAV_SYS_STATUS_SENSOR_3D_GYRO |
        MAV_SYS_STATUS_SENSOR_3D_ACCEL |
        MAV_SYS_STATUS_SENSOR_GPS,

        MAV_SYS_STATUS_SENSOR_3D_GYRO |
        MAV_SYS_STATUS_SENSOR_3D_ACCEL |
        MAV_SYS_STATUS_SENSOR_GPS,


        500,


        voltage_mv,

        current_ca,


        remaining,


        0,

        0,


        0,

        0,

        0,

        0,


        0,

        0,

        0
    );



    uint16_t len;

    len =
        mavlink_msg_to_send_buffer(
            buffer,
            &msg);


    hal_comm_write(
        buffer,
        len);


//    printf("SEND SYS_STATUS\n");
}
