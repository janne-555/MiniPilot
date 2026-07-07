# GCS_MAVLink

Author: JANNE

## Overview
GCS_MAVLink is the communication layer of MiniPilot.

It handles MAVLink protocol communication between MiniPilot and external systems.

Examples:
- Ground Control Station
- Mission Planner
- Companion computer
- External applications

GCS_MAVLink converts internal MiniPilot data into MAVLink messages and converts received MAVLink commands into autopilot actions.

## Core Files

GCS_MAVLink.c
- Main MAVLink management
- Controls send and receive processing

GCS_MAVLink.h
- Common MAVLink interface
- Includes generated MAVLink library

GCS_Parser.c
- Decodes received MAVLink packets
- Finds message type
- Calls required handlers

GCS_Stream.c
- Controls periodic telemetry sending
- Manages message streaming

## System Message Files

GCS_Heartbeat.c
- Sends vehicle alive status
- Reports autopilot state

GCS_SysStatus.c
- Sends system health information

GCS_AutopilotVersion.c
- Reports firmware/system information

GCS_SystemTime.c
- Handles system time messages

GCS_Timesync.c
- Handles MAVLink time synchronization

GCS_ProtocolVersion.c
- Provides MAVLink protocol version


## Vehicle Telemetry Files

GCS_Attitude.c
- Sends roll, pitch and yaw information

GCS_GPS.c
- Sends GPS data

GCS_GlobalPosition.c
- Sends global vehicle position

GCS_LocalPosition.c
- Sends local position information

GCS_VFR_HUD.c
- Sends flight display information


## Estimation Messages

GCS_EKF.c
- Sends EKF information

GCS_EKFStatus.c
- Sends estimator health status


## Mission System

GCS_Mission.c
- Handles mission upload/download communication

GCS_Home.c
- Handles home position messages


## Control Messages

GCS_Commands.c
- Handles MAVLink command requests

GCS_RC.c
- Handles RC related MAVLink messages

GCS_Servo.c
- Sends actuator/output information


## Parameter System

GCS_Params.c
- Handles parameter requests
- Reads and writes AP_Param values


## Status Messages

GCS_BatteryStatus.c
- Sends battery information

GCS_ExtendedState.c
- Sends vehicle extended state

GCS_Statustext.c
- Sends text/status messages


## Camera Support

GCS_Camera.c
- Handles camera related MAVLink messages


## Receive Flow

Ground Station
       |
       v
Communication Interface
       |
       v
AP_HAL
       |
       v
GCS_Parser
       |
       v
Message Handler
       |
       v
MiniPilot Module


## Send Flow

MiniPilot Module
        |
        v
GCS Message File
        |
        v
MAVLink Encoder
        |
        v
AP_HAL
        |
        v
External System


## Example Heartbeat Flow

AP_Vehicle
      |
      v
GCS_Heartbeat
      |
      v
MAVLink HEARTBEAT
      |
      v
Ground Station


## Example Parameter Flow

Ground Station Request
          |
          v
GCS_Parser
          |
          v
GCS_Params
          |
          v
AP_Param


## Example Mission Flow

Mission Upload
       |
       v
GCS_Mission
       |
       v
AP_Mission
       |
       v
AP_Nav


## Depends On

AP_HAL
- Communication transport

AP_Param
- Parameter storage

Vehicle Modules
- Status information

Sensor/Estimation Modules
- Telemetry data


## Uses Generated Library

MAVLink headers:

libraries/generated/include/mavlink/

Generated files provide:
- Message definitions
- Encode functions
- Decode functions


## Hardware Independence

MAVLink layer does not directly access hardware.

Transport path:

GCS_MAVLink
      |
      v
AP_HAL
      |
+-----+-----+
|           |
UART       UDP


## Current Implementation

Current testing:

MiniPilot
    |
    v
Linux HAL
    |
    v
UDP MAVLink


Future:

MiniPilot
    |
    v
STM32 HAL
    |
    v
UART Telemetry


## Future Expansion

GCS_MAVLink can support:
- More MAVLink messages
- Multiple communication ports
- Companion computer control
- Advanced mission handling
- Log download
- Parameter management


## Design Goal

Keep MAVLink protocol separated from flight logic.

Vehicle modules provide data.

GCS_MAVLink manages communication.
