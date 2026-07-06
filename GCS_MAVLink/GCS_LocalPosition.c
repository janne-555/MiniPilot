//------------------------------------------------------------------------------
// File    : GCS_LocalPosition.c
// Purpose : Send LOCAL_POSITION_NED Message
// Project : MiniPilot
//------------------------------------------------------------------------------

#include <stdio.h>

#include "../AP_HAL/AP_HAL.h"
#include "../AP_EKF/AP_EKF.h"

#include "GCS_MAVLink.h"



void GCS_send_local_position(void)
{
    mavlink_message_t msg;


    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];


    const AP_EKF_t *ekf;


    ekf = AP_EKF_Get();



    /*
        MAVLink NED frame

        X = North  (meters)
        Y = East   (meters)
        Z = Down   (meters)

        MiniPilot altitude:
        + value means UP

        NED:
        +Z means DOWN

        so z = -altitude
    */


    float x = 0.0f;

    float y = 0.0f;

    float z;


    float vx = 0.0f;

    float vy = 0.0f;

    float vz;



    z =
        -ekf->altitude;


    vz =
        -ekf->velocity_z;




    mavlink_msg_local_position_ned_pack(
        1,
        1,
        &msg,


        hal_millis(),


        x,
        y,
        z,


        vx,
        vy,
        vz
    );




    uint16_t len;


    len =
        mavlink_msg_to_send_buffer(
            buffer,
            &msg);



    hal_comm_write(
        buffer,
        len);



    printf(
        "SEND LOCAL_POSITION_NED\n");
}
