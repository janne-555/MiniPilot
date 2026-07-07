//------------------------------------------------------------------------------
// File    : GCS_Parser.c
// Purpose : MAVLink RX Parser
// Project : MiniPilot
//------------------------------------------------------------------------------

#include <stdio.h>

#include "GCS_MAVLink.h"
#include "GCS_Stream.h"
#include "../AP_HAL/AP_HAL.h"
#include "../AP_FlightMode/AP_FlightMode.h"
#include "../AP_Param/AP_Param.h"
#include "../AP_Mode/AP_Mode.h"
#include "../AP_Arming/AP_Arming.h"
#include "../AP_Home/AP_Home.h"
#include "../AP_Mission/AP_Mission.h"
#include "GCS_MAVLink.h"


static void handle_command_long(mavlink_message_t *msg)
{
	mavlink_command_long_t cmd;


	mavlink_msg_command_long_decode(
			msg,
			&cmd);


	printf(
			"\nCOMMAND_LONG\n"
			"CMD    : %u\n"
			"Param1 : %.2f\n",
			cmd.command,
			cmd.param1);


	switch(cmd.command)
	{


		//--------------------------------------------------
		// ARM / DISARM
		//--------------------------------------------------

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



			//--------------------------------------------------
			// SET HOME
			//--------------------------------------------------

		case MAV_CMD_DO_SET_HOME:


			printf("SET HOME COMMAND RECEIVED\n");


			if(AP_Home_SetCurrent())
			{
				GCS_send_statustext(
						"Home position set");


				/*
				 * Mission Planner expects
				 * HOME_POSITION after setting home
				 */

				GCS_send_home_position();
			}
			else
			{
				GCS_send_statustext(
						"Home set failed");
			}


			GCS_send_command_ack(
					cmd.command);


			break;
		//--------------------------------------------------
// GET HOME POSITION
//--------------------------------------------------

case MAV_CMD_GET_HOME_POSITION:


        printf("GET HOME POSITION\n");


        GCS_send_home_position();


        GCS_send_command_ack(
                cmd.command);


        break;


	case MAV_CMD_DO_SET_MODE:
{

        printf("DO_SET_MODE\n");


        AP_Mode_Set(
            (AP_Mode_t)cmd.param2);


        GCS_send_command_ack(
            cmd.command);


        break;
}

		case MAV_CMD_REQUEST_MESSAGE:
			{
				uint16_t request_id;


				request_id =
					(uint16_t)cmd.param1;


				printf(
						"REQUEST MESSAGE %u\n",
						request_id);


				GCS_handle_request_message(
						request_id);


				GCS_send_command_ack(
						cmd.command);


				break;
			}

			//--------------------------------------------------
			// SET MESSAGE INTERVAL
			//--------------------------------------------------

		case MAV_CMD_SET_MESSAGE_INTERVAL:
			{


				uint32_t msg_id;


				int32_t interval;



				msg_id =
					(uint32_t)cmd.param1;



				interval =
					(int32_t)cmd.param2;




				GCS_set_message_interval(
						msg_id,
						interval);



				GCS_send_command_ack(
						cmd.command);



				break;
			}
			//--------------------------------------------------
			// REQUEST PROTOCOL VERSION
			//--------------------------------------------------

		case MAV_CMD_REQUEST_PROTOCOL_VERSION:


			printf("PROTOCOL VERSION REQUEST\n");


			GCS_send_protocol_version();


			GCS_send_command_ack(
					cmd.command);


			break;


			//--------------------------------------------------
			// Other commands
			//--------------------------------------------------

		default:


			printf(
					"Unsupported CMD %u\n",
					cmd.command);


			GCS_send_command_ack(
					cmd.command);


			break;
	}
}





void GCS_update(void)
{

	uint8_t rxbuf[512];


	int n =
		hal_comm_read(
				rxbuf,
				sizeof(rxbuf));


	if(n <= 0)
	{
		return;
	}



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


					printf(
							"PARAM_REQUEST_LIST\n");


					for(uint16_t i=0;
							i<g_param_count;
							i++)
					{

						GCS_send_param(i);

					}


					break;


				case MAVLINK_MSG_ID_PARAM_REQUEST_READ:


					printf(
							"PARAM_REQUEST_READ\n");


					break;




				case MAVLINK_MSG_ID_PARAM_SET:
					 GCS_Handle_Param_Set(&msg);

					break;




				case MAVLINK_MSG_ID_SET_MODE:
					{
						mavlink_set_mode_t mode;


						mavlink_msg_set_mode_decode(
								&msg,
								&mode);


						AP_FlightMode_SetMode(
								(AP_FlightMode_t)mode.custom_mode,
								MODE_REASON_USER);


						printf(
								"MODE SET %u\n",
								mode.custom_mode);


						break;
					}




				case MAVLINK_MSG_ID_COMMAND_LONG:


					handle_command_long(
							&msg);


					break;




				case MAVLINK_MSG_ID_REQUEST_DATA_STREAM:
					{
						mavlink_request_data_stream_t req;


						mavlink_msg_request_data_stream_decode(
								&msg,
								&req);


						printf(
								"REQUEST_DATA_STREAM\n"
								"stream_id=%u\n"
								"rate=%u\n"
								"start_stop=%u\n",

								req.req_stream_id,
								req.req_message_rate,
								req.start_stop);

						GCS_stream_set_rate(
								req.req_stream_id,
								req.req_message_rate);



						break;
					}

				//--------------------------------------------------
// TIMESYNC #111
//--------------------------------------------------

case MAVLINK_MSG_ID_TIMESYNC:


        GCS_handle_timesync(
                &msg);


        break;

case MAVLINK_MSG_ID_MISSION_COUNT:

        GCS_handle_mission_count(&msg);

        break;



case MAVLINK_MSG_ID_MISSION_ITEM_INT:

        GCS_handle_mission_item(&msg);

        break;



case MAVLINK_MSG_ID_MISSION_REQUEST_LIST:

        GCS_handle_mission_request_list();

        break;



case MAVLINK_MSG_ID_MISSION_CLEAR_ALL:

        AP_Mission_Clear();

        GCS_send_mission_ack();

        break;

case MAVLINK_MSG_ID_MISSION_ITEM:

        GCS_handle_mission_item_float(&msg);

        break;
case MAVLINK_MSG_ID_MISSION_REQUEST:
{
        printf("MISSION_REQUEST\n");

        GCS_handle_mission_request(&msg);

        break;
}


case MAVLINK_MSG_ID_MISSION_REQUEST_INT:
{
        printf("MISSION_REQUEST_INT\n");

        GCS_handle_mission_request(&msg);

        break;
}

				default:


					printf(
							"OTHER MESSAGE\n");


					break;
			}
		}
	}
}
