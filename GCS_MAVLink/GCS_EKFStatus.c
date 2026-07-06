//------------------------------------------------------------------------------
// File    : GCS_EKFStatus.c
// Purpose : Send EKF / Estimator Status
// Project : MiniPilot
//------------------------------------------------------------------------------

#include <stdio.h>
#include <stdint.h>

#include "../AP_HAL/AP_HAL.h"
#include "../AP_EKF/AP_EKF.h"

#include "GCS_MAVLink.h"


void GCS_send_ekf_status(void)
{
    mavlink_message_t msg;

    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];


    const AP_EKF_t *ekf;

    ekf = AP_EKF_Get();


    uint16_t flags = 0;


    /*
     * Attitude estimate
     */
    if(ekf->imu_ok)
    {
        flags |= ESTIMATOR_ATTITUDE;

        flags |= ESTIMATOR_VELOCITY_HORIZ;
        flags |= ESTIMATOR_VELOCITY_VERT;
    }


    /*
     * GPS position
     */
    if(ekf->gps_ok)
    {
        flags |= ESTIMATOR_POS_HORIZ_ABS;
    }


    /*
     * Barometer altitude
     */
    if(ekf->baro_ok)
    {
        flags |= ESTIMATOR_POS_VERT_ABS;
    }

mavlink_msg_estimator_status_pack(
    1,
    1,

    &msg,


    (uint64_t)hal_millis() * 1000,


    flags,


    0.01f,     // velocity ratio


    0.01f,     // horizontal position ratio


    0.01f,     // vertical position ratio


    0.01f,     // compass ratio


    0.01f,     // terrain ratio


    0.0f,      // airspeed ratio


    0.0f,      // horizontal accuracy


    0.0f       // vertical accuracy
);



    uint16_t len;

    len =
        mavlink_msg_to_send_buffer(
            buffer,
            &msg);


    hal_comm_write(
        buffer,
        len);


//    printf("SEND EKF STATUS\n");
}
