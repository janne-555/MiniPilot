//------------------------------------------------------------------------------
// File    : GCS_BatteryStatus.c
// Purpose : Send BATTERY_STATUS Message
// Project : MiniPilot
//------------------------------------------------------------------------------

#include <stdio.h>
#include <stdint.h>

#include "../AP_HAL/AP_HAL.h"
#include "../AP_Battery/AP_Battery.h"

#include "GCS_MAVLink.h"


void GCS_send_battery_status(void)
{
    mavlink_message_t msg;

    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];


    const AP_Battery_t *bat;

    bat = AP_Battery_Get();


    //-------------------------------------
    // MAVLink wants millivolts
    // 10 cells max
    //-------------------------------------

    uint16_t voltages[10] =
    {
        UINT16_MAX,
        UINT16_MAX,
        UINT16_MAX,
        UINT16_MAX,
        UINT16_MAX,
        UINT16_MAX,
        UINT16_MAX,
        UINT16_MAX,
        UINT16_MAX,
        UINT16_MAX
    };


    voltages[0] =
        (uint16_t)(bat->voltage * 1000.0f);



    //-------------------------------------
    // extended voltages
    //-------------------------------------

    uint16_t voltages_ext[4] =
    {
        UINT16_MAX,
        UINT16_MAX,
        UINT16_MAX,
        UINT16_MAX
    };



    mavlink_msg_battery_status_pack(
        1,
        1,

        &msg,


        0,                          // battery id


        MAV_BATTERY_FUNCTION_ALL,


        MAV_BATTERY_TYPE_LIPO,


        INT16_MAX,                  // temperature unknown


        voltages,


        (int16_t)
        (bat->current * 100.0f),    // centi amps


        -1,                         // consumed mAh unknown


        -1,                         // energy unknown


        (int8_t)
        bat->remaining_percent,


        0,                          // time remaining


        MAV_BATTERY_CHARGE_STATE_OK,


        voltages_ext,


        MAV_BATTERY_MODE_UNKNOWN,


        0                           // fault bitmask
    );



    uint16_t len;


    len =
        mavlink_msg_to_send_buffer(
            buffer,
            &msg);


    hal_comm_write(
        buffer,
        len);


    printf("SEND BATTERY_STATUS\n");
}
