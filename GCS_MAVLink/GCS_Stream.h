//------------------------------------------------------------------------------
// File    : GCS_Stream.h
// Purpose : MAVLink Stream Manager
// Project : MiniPilot
//------------------------------------------------------------------------------

#ifndef GCS_STREAM_H
#define GCS_STREAM_H


#include <stdint.h>


void GCS_stream_init(void);


void GCS_stream_set_rate(
        uint8_t stream_id,
        uint16_t rate_hz);


void GCS_stream_update(void);


#endif
