# AP_Battery

Author: JANNE

## Overview
AP_Battery is the power monitoring module of MiniPilot.

It manages battery related information and provides power status data required for vehicle monitoring and safety decisions.

## Files

AP_Battery.c
- Contains battery monitoring implementation
- Updates voltage and current information
- Maintains battery status

AP_Battery.h
- Defines battery data structures
- Provides battery APIs used by other modules

## Responsibilities
AP_Battery manages:
- Battery voltage monitoring
- Current monitoring
- Power status tracking
- Battery health information
- Low power detection support

## Input Data

AP_Battery receives:
- Voltage measurements
- Current measurements
- Battery sensor information

Data source:
- Battery monitoring hardware through AP_HAL

## Output Data

AP_Battery provides:
- Battery voltage
- Current usage
- Remaining power information
- Battery health status
- Warning status

## Depends On

AP_HAL
- Provides hardware measurement interface
- Provides ADC/sensor access

AP_Param
- Battery configuration
- Calibration values

## Used By

AP_Vehicle
- Uses battery status for vehicle monitoring

AP_Failsafe
- Uses battery information for safety decisions

GCS_MAVLink
- Sends battery telemetry information

AP_Logger
- Records battery data

## Data Flow

Battery Sensor
       |
       v
    AP_HAL
       |
       v
  AP_Battery
       |
+------+------+
|             |
v             v
Failsafe   Telemetry

## Startup Flow

System Start
      |
      v
AP_HAL Init
      |
      v
AP_Battery Init
      |
      v
Load Battery Parameters
      |
      v
Battery Monitor Ready

## Runtime Flow

Scheduler Update
        |
        v
AP_Battery Update
        |
        v
Read Power Data
        |
        v
Update Battery State
        |
        v
Provide Status To System

## Safety Usage

Battery information is important for failsafe handling.

Examples:
- Low voltage warning
- Critical battery detection
- Power monitoring

## Future Expansion

AP_Battery can support:
- Multiple batteries
- Smart batteries
- Power consumption estimation
- Remaining flight time calculation
- Advanced battery failsafe

## Design Goal

AP_Battery only manages power monitoring.

Vehicle level decisions are handled by AP_Vehicle and AP_Failsafe.
