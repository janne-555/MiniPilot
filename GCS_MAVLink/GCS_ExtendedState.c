//------------------------------------------------------------------------------
// File    : GCS_ExtendedState.c
// Purpose : Send MAVLink EXTENDED_SYS_STATE
// Project : MiniPilot
//------------------------------------------------------------------------------

#include <stdio.h>

#include "../AP_HAL/AP_HAL.h"
#include "../AP_Arming/AP_Arming.h"

#include "GCS_MAVLink.h"


void GCS_send_extended_state(void)
{
    mavlink_message_t msg;

    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];


    uint8_t landed_state;


    /*
     * Simple logic:
     *
     * Disarmed = On ground
     * Armed    = Flying
     *
     * Later AP_Landing will update this
     */

    if(AP_Arming_IsArmed())
    {
        landed_state =
            MAV_LANDED_STATE_IN_AIR;
    }
    else
    {
        landed_state =
            MAV_LANDED_STATE_ON_GROUND;
    }



    mavlink_msg_extended_sys_state_pack(
            1,
            1,
            &msg,

            MAV_VTOL_STATE_UNDEFINED,

            landed_state
    );



    uint16_t len;

    len =
        mavlink_msg_to_send_buffer(
                buffer,
                &msg);



    hal_comm_write(
            buffer,
            len);


    printf("SEND EXTENDED_SYS_STATE\n");
}
