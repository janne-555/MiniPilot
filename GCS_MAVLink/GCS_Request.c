//------------------------------------------------------------------------------
// File    : GCS_Request.c
// Purpose : MAVLink REQUEST_MESSAGE Handler
// Project : MiniPilot
//------------------------------------------------------------------------------

#include <stdio.h>

#include "GCS_MAVLink.h"

void GCS_handle_request_message(uint16_t msgid) {

  printf("REQUEST MESSAGE ID : %u\n", msgid);

  switch (msgid) {

    //--------------------------------------------------
    // HEARTBEAT
    // MSG ID : 0
    //--------------------------------------------------

  case MAVLINK_MSG_ID_HEARTBEAT:

    GCS_send_heartbeat();

    break;

    //--------------------------------------------------
    // SYS_STATUS
    // MSG ID : 1
    //--------------------------------------------------

  case MAVLINK_MSG_ID_SYS_STATUS:

    GCS_send_sys_status();

    break;
    //--------------------------------------------------
    // SYSTEM_TIME #2
    //--------------------------------------------------

  case MAVLINK_MSG_ID_SYSTEM_TIME:

    GCS_send_system_time();

    break;

    //--------------------------------------------------
    // GPS_RAW_INT
    // MSG ID : 24
    //--------------------------------------------------

  case MAVLINK_MSG_ID_GPS_RAW_INT:

    GCS_send_gps_raw_int();

    break;

    //--------------------------------------------------
    // ATTITUDE
    // MSG ID : 30
    //--------------------------------------------------

  case MAVLINK_MSG_ID_ATTITUDE:

    GCS_send_attitude();

    break;

    //--------------------------------------------------
    // GLOBAL_POSITION_INT
    // MSG ID : 33
    //--------------------------------------------------

  case MAVLINK_MSG_ID_GLOBAL_POSITION_INT:

    GCS_send_global_position();

    break;

    //--------------------------------------------------
    // VFR HUD
    // MSG ID : 74
    //--------------------------------------------------

  case MAVLINK_MSG_ID_VFR_HUD:

    GCS_send_vfr_hud();

    break;

    //--------------------------------------------------
    // BATTERY_STATUS
    // MSG ID : 147
    //--------------------------------------------------

#ifdef MAVLINK_MSG_ID_BATTERY_STATUS

  case MAVLINK_MSG_ID_BATTERY_STATUS:

    GCS_send_battery_status();

    break;

#endif

    //--------------------------------------------------
    // AUTOPILOT_VERSION
    // MSG ID : 148
    //--------------------------------------------------

#ifdef MAVLINK_MSG_ID_AUTOPILOT_VERSION

  case MAVLINK_MSG_ID_AUTOPILOT_VERSION:

    printf("AUTOPILOT_VERSION REQUEST\n");

    GCS_send_autopilot_version();

    break;

#endif

    //--------------------------------------------------
    // ESTIMATOR_STATUS
    //--------------------------------------------------

#ifdef MAVLINK_MSG_ID_ESTIMATOR_STATUS

  case MAVLINK_MSG_ID_ESTIMATOR_STATUS:

    GCS_send_ekf_status();

    break;

#endif

    //--------------------------------------------------
    // HOME_POSITION
    //--------------------------------------------------

#ifdef MAVLINK_MSG_ID_HOME_POSITION

  case MAVLINK_MSG_ID_HOME_POSITION:

    GCS_send_home_position();

    break;

#endif

    //--------------------------------------------------
    // EXTENDED_SYS_STATE #245
    //--------------------------------------------------

  case MAVLINK_MSG_ID_EXTENDED_SYS_STATE:

    GCS_send_extended_state();

    break;

    //--------------------------------------------------
    // CAMERA_INFORMATION
    // MSG ID : 269
    //--------------------------------------------------

#ifdef MAVLINK_MSG_ID_CAMERA_INFORMATION

  case MAVLINK_MSG_ID_CAMERA_INFORMATION:

    GCS_send_camera_information();

    break;

#endif

    //--------------------------------------------------
    // VIDEO STREAM INFORMATION
    //--------------------------------------------------

#ifdef MAVLINK_MSG_ID_VIDEO_STREAM_INFORMATION

  case MAVLINK_MSG_ID_VIDEO_STREAM_INFORMATION:

    printf("VIDEO STREAM ignored\n");

    break;

#endif

    //--------------------------------------------------
    // GIMBAL_MANAGER_INFORMATION
    // MSG ID : 280
    //--------------------------------------------------

#ifdef MAVLINK_MSG_ID_GIMBAL_MANAGER_INFORMATION

  case MAVLINK_MSG_ID_GIMBAL_MANAGER_INFORMATION:

    GCS_send_gimbal_information();

    break;

#endif

    //--------------------------------------------------
    // LOCAL_POSITION_NED
    // MSG ID : 32
    //--------------------------------------------------

#ifdef MAVLINK_MSG_ID_LOCAL_POSITION_NED

  case MAVLINK_MSG_ID_LOCAL_POSITION_NED:

    GCS_send_local_position();

    break;

#endif

    //--------------------------------------------------
    // RC_CHANNELS
    // MSG ID : 65
    //--------------------------------------------------

#ifdef MAVLINK_MSG_ID_RC_CHANNELS

  case MAVLINK_MSG_ID_RC_CHANNELS:

    GCS_send_rc_channels();

    break;

#endif

    //--------------------------------------------------
    // SERVO_OUTPUT_RAW
    // MSG ID : 36
    //--------------------------------------------------

#ifdef MAVLINK_MSG_ID_SERVO_OUTPUT_RAW

  case MAVLINK_MSG_ID_SERVO_OUTPUT_RAW:

    GCS_send_servo_output();

    break;

#endif

    //--------------------------------------------------
    // UNKNOWN REQUEST
    //--------------------------------------------------

  default:

    printf("REQUEST MESSAGE unsupported %u\n", msgid);

    break;
  }
}
