//------------------------------------------------------------------------------
// File    : GCS_MAVLink.h
// Purpose : MAVLink Interface
// Project : MiniPilot
//------------------------------------------------------------------------------

#ifndef GCS_MAVLINK_H
#define GCS_MAVLINK_H

#include <stdint.h>

#include "../libraries/generated/include/mavlink/v2.0/common/mavlink.h"


/*-------------------------------------------------------
  MAVLink RX
-------------------------------------------------------*/

void GCS_update(void);



/*-------------------------------------------------------
  Basic Messages
-------------------------------------------------------*/

void GCS_send_heartbeat(void);

void GCS_send_sys_status(void);

void GCS_send_statustext(const char *text);



/*-------------------------------------------------------
  Vehicle State Messages
-------------------------------------------------------*/

void GCS_send_attitude(void);

void GCS_send_gps_raw_int(void);

void GCS_send_global_position(void);

void GCS_send_vfr_hud(void);



/*-------------------------------------------------------
  Navigation Messages
-------------------------------------------------------*/

void GCS_send_home_position(void);

void GCS_send_ekf_status(void);



/*-------------------------------------------------------
  Parameters
-------------------------------------------------------*/

void GCS_send_param(uint16_t index);



/*-------------------------------------------------------
  Commands
-------------------------------------------------------*/

void GCS_send_command_ack(uint16_t command);
void GCS_handle_request_message(uint16_t id);
//////////////////////////////////////////////


void GCS_handle_request_message(uint16_t msg_id);
void GCS_handle_request_message(uint16_t id);

void GCS_send_home_position(void);

void GCS_send_autopilot_version(void);

void GCS_send_protocol_version(void);

void GCS_MessageInterval_Init(void);


void GCS_set_message_interval(uint32_t msg_id,
                              int32_t interval_us);


int32_t GCS_get_message_interval(uint32_t msg_id);

void GCS_send_camera_information(void);

void GCS_send_gimbal_information(void);

void GCS_send_battery_status(void);

void GCS_send_local_position(void);

void GCS_send_local_position(void);

void GCS_send_rc_channels(void);
void GCS_send_servo_output(void);
void GCS_send_system_time(void);
void GCS_send_extended_state(void);

void GCS_handle_timesync(mavlink_message_t *msg);

void GCS_handle_mission_count(mavlink_message_t *msg);

void GCS_handle_mission_item(mavlink_message_t *msg);

void GCS_handle_mission_request_list(void);


void GCS_send_mission_ack(void);

void GCS_send_mission_count(void);

void GCS_send_mission_request(uint16_t seq);

void GCS_Handle_Param_Set(mavlink_message_t *msg);


void GCS_handle_mission_item_float(mavlink_message_t *msg);















#endif
