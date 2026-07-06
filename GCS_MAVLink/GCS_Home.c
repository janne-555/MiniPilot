//------------------------------------------------------------------------------
// File    : GCS_Home.c
// Purpose : Send MAVLink HOME_POSITION
// Project : MiniPilot
//------------------------------------------------------------------------------

#include <stdio.h>
#include <stdint.h>

#include "../AP_HAL/AP_HAL.h"
#include "../AP_Home/AP_Home.h"

#include "GCS_MAVLink.h"


void GCS_send_home_position(void)
{
    const AP_Home_t *home;


    home = AP_Home_Get();


    if(home->valid == 0)
    {
        return;
    }


    mavlink_message_t msg;

    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];


    int32_t latitude =
        (int32_t)(home->latitude * 10000000.0);


    int32_t longitude =
        (int32_t)(home->longitude * 10000000.0);


    int32_t altitude =
        (int32_t)(home->altitude * 1000.0f);



    /*
     * Vehicle attitude at home
     *
     * Quaternion:
     * no rotation
     */

    float q[4];

    q[0] = 1.0f;
    q[1] = 0.0f;
    q[2] = 0.0f;
    q[3] = 0.0f;



    mavlink_msg_home_position_pack(
        1,
        1,

        &msg,


        latitude,

        longitude,

        altitude,


        0.0f,     // local X

        0.0f,     // local Y

        0.0f,     // local Z


        q,


        0.0f,     // approach X

        0.0f,     // approach Y

        0.0f,     // approach Z


        (uint64_t)hal_millis() * 1000
    );



    uint16_t len;


    len =
        mavlink_msg_to_send_buffer(
            buffer,
            &msg);


    hal_comm_write(
        buffer,
        len);



    printf("SEND HOME_POSITION\n");
}
