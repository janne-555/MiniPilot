# MiniPilot MAVLink Flow

Author: JANNE

## Overview
This document explains the MAVLink communication flow inside MiniPilot.

MAVLink connects MiniPilot with external systems like Ground Control Stations, simulators and companion computers.

GCS_MAVLink handles protocol processing while AP_HAL handles the physical communication interface.

## MAVLink Layer Position

External System
       |
       v
Communication Transport
       |
       v
AP_HAL
       |
       v
GCS_MAVLink
       |
       v
MiniPilot Core


## Main Components

GCS_MAVLink.c
- Main MAVLink manager
- Runs communication update logic

GCS_Parser.c
- Receives MAVLink bytes
- Decodes packets
- Processes message IDs
- Calls required handlers

GCS_Stream.c
- Manages telemetry streams
- Controls periodic message sending

Message Files:
- GCS_Heartbeat
- GCS_Attitude
- GCS_GPS
- GCS_EKF
- GCS_Params
- GCS_Mission
- GCS_Commands
- Other MAVLink messages


## Receive Data Flow

Ground Station
       |
       v
UDP / UART
       |
       v
AP_HAL Communication
       |
       v
GCS_MAVLink
       |
       v
GCS_Parser
       |
       v
Decode MAVLink Message
       |
       v
Execute Message Handler
       |
       v
MiniPilot Module


## Transmit Data Flow

MiniPilot Module
        |
        v
Message Generator
        |
        v
MAVLink Encode
        |
        v
GCS_Stream
        |
        v
AP_HAL Communication
        |
        v
Ground Station


## Heartbeat Flow

AP_Vehicle
      |
      v
Vehicle State
      |
      v
GCS_Heartbeat
      |
      v
MAVLink HEARTBEAT
      |
      v
GCS_Stream
      |
      v
AP_HAL


## Attitude Flow

AP_IMU
   |
   v
AP_AHRS
   |
   v
Vehicle Attitude
   |
   v
GCS_Attitude
   |
   v
Ground Station


## GPS Position Flow

AP_GPS
   |
   v
GCS_GPS
   |
   v
GPS MAVLink Message


Global position:

AP_EKF
   |
   v
GCS_GlobalPosition
   |
   v
MAVLink Position Message


## EKF Status Flow

Sensors
   |
   v
AP_EKF
   |
   v
GCS_EKFStatus
   |
   v
Estimator Status Message


## Parameter Flow

Ground Station
        |
        v
PARAM Request
        |
        v
GCS_Parser
        |
        v
GCS_Params
        |
        v
AP_Param


## Mission Flow

Mission Upload
       |
       v
GCS_Parser
       |
       v
GCS_Mission
       |
       v
AP_Mission
       |
       v
AP_Nav


## Command Flow

COMMAND_LONG
      |
      v
GCS_Parser
      |
      v
GCS_Commands
      |
      v
Vehicle Module


## Stream System

Telemetry messages are not sent directly.

Flow:

Module Data
      |
      v
GCS Message Function
      |
      v
GCS_Stream
      |
      v
Scheduled Output


## Current Transport

Current MiniPilot testing:

Mission Planner
       |
       v
UDP Network
       |
       v
HAL_Linux
       |
       v
MiniPilot


## Future STM32 Transport

Ground Station
       |
       v
Telemetry UART
       |
       v
STM32 HAL
       |
       v
Same GCS_MAVLink Code


## Hardware Independence

Only AP_HAL changes.

MAVLink message handling remains same.

Linux:
UDP Socket

STM32:
UART Driver


## Runtime Flow

AP_Scheduler
      |
      v
GCS_MAVLink Update
      |
      +-- Read incoming data
      |
      +-- Parse messages
      |
      +-- Execute commands
      |
      +-- Send telemetry


## Design Goal

GCS_MAVLink only manages communication.

Flight modules provide information.

Communication transport stays inside AP_HAL.
