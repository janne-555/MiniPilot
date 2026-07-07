# AP_Logger

Author: JANNE

## Overview
AP_Logger is the logging system of MiniPilot.

It records important runtime information from autopilot modules for debugging, analysis and system monitoring.

Logging helps understand vehicle behavior after or during operation.

## Files

AP_Logger.c
- Contains logging implementation
- Handles log data collection
- Manages log update process

AP_Logger.h
- Defines logger interfaces
- Provides logging APIs used by modules

## Responsibilities
AP_Logger manages:
- Runtime data recording
- System event logging
- Module status logging
- Debug information storage

## Input Data

AP_Logger receives:

Sensor Modules:
- IMU data
- GPS information
- Barometer data
- Compass data

Estimation Modules:
- AHRS attitude
- EKF state

Control Modules:
- Controller outputs
- Motor commands

System Modules:
- Errors
- Events
- Status information

## Output Data

AP_Logger provides:
- Flight logs
- Debug information
- System history
- Recorded telemetry data

## Depends On

AP_HAL
- Provides storage interface
- Provides timing information

AP_Param
- Provides logging configuration

## Used By

AP_Vehicle
- Logs vehicle state

AP_Scheduler
- Logs task information

AP_Failsafe
- Logs safety events

GCS_MAVLink
- Provides log access support

## Data Flow

MiniPilot Modules
        |
        v
    AP_Logger
        |
        v
   AP_HAL Storage

## Startup Flow

System Start
      |
      v
AP_Logger Init
      |
      v
Prepare Storage
      |
      v
Ready For Logging

## Runtime Flow

Scheduler Update
        |
        v
Collect Module Data
        |
        v
Create Log Entry
        |
        v
Store Information

## Logging Concept

Modules should not directly access storage.

Flow:

Module Data
     |
     v
AP_Logger
     |
     v
AP_HAL
     |
     v
Storage Device

## Future Expansion

AP_Logger can support:
- SD card logging
- Flash logging
- Binary log format
- Real-time log streaming
- Performance monitoring

## Design Goal

AP_Logger separates data recording from autopilot logic.

Modules generate information while logger manages storage and history.
