#include <stdio.h>

#include "GCS_MAVLink.h"
#include "../AP_HAL/AP_HAL.h"
#include "../AP_Param/AP_Param.h"
#include "../AP_Mode/AP_Mode.h"
#include "../AP_Arming/AP_Arming.h"

#include "../libraries/generated/include/mavlink/v2.0/common/mavlink.h"

void GCS_update(void)
{
	uint8_t rxbuf[512];

	int n = hal_comm_read(rxbuf,sizeof(rxbuf));

	if(n <= 0)
	{
		return;
	}

	printf("RX %d bytes\n",n);

	mavlink_message_t msg;
	mavlink_status_t status;

	for(int i=0;i<n;i++)
	{
		if(mavlink_parse_char(
					MAVLINK_COMM_0,
					rxbuf[i],
					&msg,
					&status))
		{
			printf(
					"\nMAVLINK MSG\n"
					"ID   : %u\n"
					"SYS  : %u\n"
					"COMP : %u\n",
					msg.msgid,
					msg.sysid,
					msg.compid);

			switch(msg.msgid)
			{
				case MAVLINK_MSG_ID_HEARTBEAT:
					printf("HEARTBEAT\n");
					break;

				case MAVLINK_MSG_ID_PARAM_REQUEST_LIST:
					{
						printf("PARAM_REQUEST_LIST\n");
						for(uint16_t i=0;i<g_param_count;i++)
						{
							GCS_send_param(i);
						}

						break;
					}

				case MAVLINK_MSG_ID_PARAM_REQUEST_READ:
					printf("PARAM_REQUEST_READ\n");
					break;

				case MAVLINK_MSG_ID_PARAM_SET:
					printf("PARAM_SET\n");
					break;

				case MAVLINK_MSG_ID_SET_MODE:
					{
						mavlink_set_mode_t mode;

						mavlink_msg_set_mode_decode(
								&msg,
								&mode);

						AP_Mode_Set(
								(AP_Mode_t)mode.custom_mode);

						printf(
								"Mode=%u\n",
								mode.custom_mode);

						break;
					}

				case MAVLINK_MSG_ID_COMMAND_LONG:
					{
						mavlink_command_long_t cmd;

						mavlink_msg_command_long_decode(
								&msg,
								&cmd);

						switch(cmd.command)
						{
							case MAV_CMD_COMPONENT_ARM_DISARM:

								if(cmd.param1 == 1)
								{
									AP_Arming_Arm();

									GCS_send_statustext(
											"Vehicle Armed");
								}
								else
								{
									AP_Arming_Disarm();

									GCS_send_statustext(
											"Vehicle Disarmed");
								}

								GCS_send_command_ack(
										cmd.command);

								break;

							default:

								GCS_send_command_ack(
										cmd.command);

								break;
						}
						break;}


				case MAVLINK_MSG_ID_REQUEST_DATA_STREAM:
					{
						mavlink_request_data_stream_t req;
						mavlink_msg_request_data_stream_decode( &msg, &req);

						printf("REQUEST_DATA_STREAM\n"
								"stream_id=%u\n"
								"rate=%u\n"
								"start_stop=%u\n", 
								req.req_stream_id, 
								req.req_message_rate,
								req.start_stop); 
						break;
					}

				default:
					printf("OTHER MESSAGE\n");
					break;
			}
		}
	}
}
