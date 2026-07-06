//------------------------------------------------------------------------------
// File    : GCS_Stream.c
// Purpose : Mission Planner MAVLink Streams
// Project : MiniPilot
//------------------------------------------------------------------------------

#include <stdio.h>

#include "../AP_HAL/AP_HAL.h"

#include "GCS_MAVLink.h"
#include "GCS_Stream.h"


typedef struct
{
    uint8_t enabled;

    uint16_t rate_hz;

    uint32_t last_ms;

} GCS_Stream_t;



static GCS_Stream_t streams[16];



void GCS_stream_init(void)
{
    for(int i=0;i<16;i++)
    {
        streams[i].enabled = 0;

        streams[i].rate_hz = 0;

        streams[i].last_ms = 0;
    }
}




void GCS_stream_set_rate(
        uint8_t stream_id,
        uint16_t rate_hz)
{

    if(stream_id >= 16)
    {
        return;
    }


    streams[stream_id].enabled = 1;

    streams[stream_id].rate_hz = rate_hz;


    printf(
        "STREAM ENABLE %u RATE %u\n",
        stream_id,
        rate_hz);
}





static uint8_t stream_ready(uint8_t id)
{
    if(streams[id].enabled == 0)
    {
        return 0;
    }


    if(streams[id].rate_hz == 0)
    {
        return 0;
    }


    uint32_t now = hal_millis();


    uint32_t period =
        1000 / streams[id].rate_hz;



    if(now - streams[id].last_ms >= period)
    {
        streams[id].last_ms = now;

        return 1;
    }


    return 0;
}





void GCS_stream_update(void)
{


    /*
        MAV_DATA_STREAM_EXTENDED_STATUS = 2
    */

    if(stream_ready(2))
    {
        GCS_send_sys_status();

	GCS_send_extended_state();

        GCS_send_ekf_status();
    }




    /*
        MAV_DATA_STREAM_POSITION = 6
    */

    if(stream_ready(6))
    {
        GCS_send_gps_raw_int();

        GCS_send_global_position();

        GCS_send_local_position();
    }




    /*
        MAV_DATA_STREAM_EXTRA1 = 10

        attitude
    */

    if(stream_ready(10))
    {
        GCS_send_attitude();
    }





    /*
        MAV_DATA_STREAM_EXTRA2 = 11
    */

    if(stream_ready(11))
    {
        GCS_send_vfr_hud();
    }




    /*
        MAV_DATA_STREAM_EXTRA3 = 12
    */

    if(stream_ready(12))
    {
        GCS_send_ekf_status();
    }
}
