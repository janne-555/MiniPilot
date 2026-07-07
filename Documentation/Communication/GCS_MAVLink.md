# GCS_MAVLink

Author: JANNE

## Overview
GCS_MAVLink is the communication layer of MiniPilot.

It manages data exchange between MiniPilot and external systems using the MAVLink protocol.

This module converts internal autopilot data into MAVLink messages and converts received MAVLink commands into MiniPilot actions.

## Files

GCS_MAVLink.c
- Main MAVLink handling implementation
- Manages message processing
- Connects MAVLink system with MiniPilot modules

GCS_MAVLink.h
- Defines MAVLink interfaces
- Provides APIs for communication handling

GCS_Heartbeat.c
- Handles heartbeat messages
- Provides system alive/status information

GCS_Params.c
- Handles parameter communication
- Connects MAVLink parameter messages with AP_Param

GCS_Mission.c
- Handles mission communication
- Provides mission upload/download support

GCS_GPS.c
- Sends GPS related information

GCS_EKF.c
- Sends estimation and navigation status

GCS_SystemTime.c
- Handles system time synchronization

## Responsibilities
GCS_MAVLink manages:
- MAVLink message encoding
- MAVLink message decoding
- Telemetry transmission
- Command reception
- Parameter communication
- Mission communication
- Vehicle status reporting

## Input Data

GCS_MAVLink receives data from MiniPilot modules.

Examples:
- Vehicle status from AP_Vehicle
- Parameters from AP_Param
- GPS data from AP_GPS
- Attitude from AP_AHRS
- EKF status from AP_EKF
- Mission data from AP_Mission

External input:
- Ground station commands
- Parameter changes
- Mission uploads

## Output Data

GCS_MAVLink provides:
- Telemetry messages
- Vehicle status messages
- Sensor information
- Mission responses
- Command requests to modules

## Depends On

AP_HAL
- Provides communication interface

AP_Param
- Parameter access

AP_Vehicle
- Vehicle status

AP_Mission
- Mission handling

## Used By

Ground Control Systems:
- Telemetry monitoring
- Parameter configuration
- Mission control

MiniPilot Modules:
- Receive external commands
- Send system information

## Data Flow

Ground Station
       |
       v
Communication Interface
       |
       v
GCS_MAVLink
       |
+------+------+------+
|      |      |      |
Param Mission Status
|      |      |
v      v      v
AP_Param AP_Mission AP_Vehicle

## Receive Flow

MAVLink Packet
       |
       v
Decode Message
       |
       v
Identify Message ID
       |
       v
Execute Handler
       |
       v
Update MiniPilot Module

## Transmit Flow

MiniPilot Module
        |
        v
Collect Data
        |
        v
Create MAVLink Message
        |
        v
Send Through AP_HAL

## Message Groups

System:
- Heartbeat
- System status
- Time

Navigation:
- GPS information
- EKF information
- Position data

Configuration:
- Parameters

Mission:
- Mission upload
- Mission download
- Mission status

## Future Expansion

GCS_MAVLink can support:
- Additional MAVLink messages
- Multiple communication ports
- Telemetry radios
- Companion computers
- Advanced command handling

## Design Goal

Communication protocol handling stays inside GCS_MAVLink.

Flight modules should only provide data and should not handle MAVLink encoding directly.
