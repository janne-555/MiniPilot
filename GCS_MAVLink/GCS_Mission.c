//------------------------------------------------------------------------------
// File    : GCS_Mission.c
// Purpose : MAVLink Mission Handler
// Project : MiniPilot
//------------------------------------------------------------------------------

#include <stdio.h>

#include "GCS_MAVLink.h"

#include "../AP_HAL/AP_HAL.h"
#include "../AP_Mission/AP_Mission.h"


static uint16_t upload_count = 0;
static uint16_t upload_seq   = 0;



static void send_msg(mavlink_message_t *msg)
{
    uint8_t buf[MAVLINK_MAX_PACKET_LEN];


    uint16_t len =
        mavlink_msg_to_send_buffer(
                buf,
                msg);


    hal_comm_write(
            buf,
            len);
}





void GCS_send_mission_ack(void)
{
    mavlink_message_t msg;


    mavlink_msg_mission_ack_pack(
            1,
            1,
            &msg,

            255,
            190,

            MAV_MISSION_ACCEPTED,

            MAV_MISSION_TYPE_MISSION,

            0);


    send_msg(&msg);


    printf("SEND MISSION_ACK\n");
}






void GCS_send_mission_count(void)
{
    mavlink_message_t msg;


    mavlink_msg_mission_count_pack(
            1,
            1,
            &msg,

            255,
            190,

            AP_Mission_Count(),

            MAV_MISSION_TYPE_MISSION,

            0);


    send_msg(&msg);


    printf("SEND MISSION_COUNT\n");
}








void GCS_send_mission_request(uint16_t seq)
{

    mavlink_message_t msg;


    mavlink_msg_mission_request_int_pack(
            1,
            1,
            &msg,

            255,
            190,

            seq,

            MAV_MISSION_TYPE_MISSION);


    send_msg(&msg);


    printf(
        "REQUEST MISSION ITEM %u\n",
        seq);
}









void GCS_handle_mission_count(mavlink_message_t *msg)
{

    mavlink_mission_count_t cnt;


    mavlink_msg_mission_count_decode(
            msg,
            &cnt);



    printf(
        "MISSION COUNT RX %u\n",
        cnt.count);



    AP_Mission_Clear();



    upload_count = cnt.count;

    upload_seq = 0;



    if(upload_count)
    {
        GCS_send_mission_request(0);
    }

}









void GCS_handle_mission_item(mavlink_message_t *msg)
{

    mavlink_mission_item_int_t item;


    mavlink_msg_mission_item_int_decode(
            msg,
            &item);



    AP_Mission_Item_t wp;



    wp.seq = item.seq;

    wp.command = item.command;



    wp.lat = item.x / 10000000.0;

    wp.lon = item.y / 10000000.0;


    wp.alt = item.z;


    wp.param1 = item.param1;
    wp.param2 = item.param2;
    wp.param3 = item.param3;
    wp.param4 = item.param4;



    AP_Mission_AddItem(
            &wp);



    printf(
        "MISSION ITEM RX %u\n",
        item.seq);



    upload_seq++;



    if(upload_seq < upload_count)
    {

        GCS_send_mission_request(
                upload_seq);

    }
    else
    {

        GCS_send_mission_ack();

    }

}









void GCS_handle_mission_request_list(void)
{

    printf("MISSION LIST REQUEST\n");


    GCS_send_mission_count();

}
