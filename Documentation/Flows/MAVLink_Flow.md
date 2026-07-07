# MiniPilot MAVLink Flow

Author: JANNE

## Overview
This document explains how MAVLink communication works inside MiniPilot.

GCS_MAVLink acts as the bridge between external systems and internal autopilot modules.

It converts MiniPilot data into MAVLink messages and converts received MAVLink commands into internal actions.

## Communication Position

External System
       |
       v
Communication Interface
       |
       v
GCS_MAVLink
       |
       v
MiniPilot Modules


## Main Components

GCS_MAVLink.c
- Main communication handling

GCS_Heartbeat.c
- System alive message
- Vehicle status

GCS_Params.c
- Parameter communication

GCS_Mission.c
- Mission communication

GCS_GPS.c
- GPS telemetry

GCS_EKF.c
- Estimation status

GCS_SystemTime.c
- Time synchronization


## Receive Flow

External Message
        |
        v
Communication Driver
        |
        v
AP_HAL
        |
        v
GCS_MAVLink
        |
        v
Decode MAVLink Packet
        |
        v
Find Message Handler
        |
        v
Update MiniPilot Module


## Command Flow

Ground Station Command
          |
          v
     MAVLink Message
          |
          v
     GCS_MAVLink
          |
 +--------+---------+
 |        |         |
 v        v         v
Param  Mission   Vehicle


## Parameter Flow

Read/Write Request
          |
          v
GCS_MAVLink Params
          |
          v
      AP_Param
          |
          v
System Configuration


## Mission Flow

Mission Upload
        |
        v
GCS_MAVLink Mission
        |
        v
AP_Mission
        |
        v
AP_Nav


## Telemetry Flow

MiniPilot Modules
        |
        v
Collect Data
        |
        v
GCS_MAVLink
        |
        v
Encode MAVLink Message
        |
        v
Send To External System


## Heartbeat Flow

AP_Vehicle
      |
      v
System State
      |
      v
GCS_Heartbeat
      |
      v
MAVLink Heartbeat Message


Purpose:
- Identify vehicle
- Show system alive
- Send vehicle status


## Sensor Telemetry Flow

AP_GPS
   |
   v
GCS_GPS
   |
   v
GPS MAVLink Message


AP_EKF
   |
   v
GCS_EKF
   |
   v
EKF Status Message


## Module Dependency

GCS_MAVLink receives data from:

- AP_Vehicle
- AP_Param
- AP_Mission
- AP_GPS
- AP_AHRS
- AP_EKF

GCS_MAVLink uses:

AP_HAL
- For communication interface


## Hardware Independence

Communication transport is separated.

Examples:

MiniPilot Core
       |
       v
GCS_MAVLink
       |
       v
AP_HAL Communication
       |
 +-----+------+
 |            |
UART        Network


## Runtime Execution

AP_Scheduler
      |
      v
GCS_MAVLink Update
      |
      +-- Check Received Messages
      |
      +-- Process Commands
      |
      +-- Send Telemetry


## Future Expansion

GCS_MAVLink can support:
- More MAVLink messages
- Multiple telemetry ports
- Companion computers
- Advanced mission handling
- External control systems

## Design Goal

MAVLink protocol handling remains inside GCS_MAVLink.

Autopilot modules provide data but do not directly manage communication protocols.
