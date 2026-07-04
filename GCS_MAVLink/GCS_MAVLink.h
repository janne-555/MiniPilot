#ifndef GCS_MAVLINK_H
#define GCS_MAVLINK_H

#include <stdint.h>

void GCS_send_heartbeat(void);

void GCS_send_statustext(const char *text);

void GCS_send_param(uint16_t index);

void GCS_send_command_ack(uint16_t command);

void GCS_send_sys_status(void);

void GCS_send_attitude(void);

void GCS_send_gps_raw_int(void);

void GCS_send_vfr_hud(void);

void GCS_update(void);

void GCS_send_global_position(void);


#endif
