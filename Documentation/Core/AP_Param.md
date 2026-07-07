# AP_Param

Author: JANNE

## Overview
AP_Param is the parameter management system of MiniPilot.

It provides a centralized interface for storing, accessing and updating configuration values used by different autopilot modules.

Parameters allow system behavior changes without modifying source code.

## Files

AP_Param.c
- Contains parameter management implementation
- Handles parameter operations
- Provides runtime parameter access

AP_Param.h
- Defines parameter structures
- Provides APIs used by other modules

## Responsibilities
AP_Param manages:
- Parameter registration
- Parameter storage interface
- Parameter lookup
- Runtime value updates
- Configuration sharing between modules

## Input Data

AP_Param receives:
- Default parameter values from modules
- Updated values from communication interfaces
- Stored values from memory systems

Examples:
- PID tuning values
- Sensor calibration data
- Vehicle configuration
- System settings

## Output Data

AP_Param provides:
- Current parameter values
- Configuration information
- Runtime settings

These values are used by autopilot modules during operation.

## Depends On

AP_HAL
- Provides storage interface for saving/loading parameters

Future storage options:
- Flash
- EEPROM
- SD card
- File system

## Used By

AP_Vehicle
- Vehicle configuration

AP_Control
- Controller settings

AP_PID
- Gain values

AP_AHRS
- Estimation configuration

AP_EKF
- Filter settings

AP_Mission
- Mission parameters

GCS_MAVLink
- Parameter read/write access

## Data Flow

Ground Station
      |
      v
GCS_MAVLink
      |
      v
AP_Param
      |
+-----+---------+
|               |
Control      Sensors


## Startup Flow

System Start
      |
      v
AP_Param Init
      |
      v
Load Parameters
      |
      v
Provide Configuration
      |
      v
Modules Initialize


## Runtime Flow

Module Request
       |
       v
AP_Param Lookup
       |
       v
Return Value


Parameter Update:

GCS Command
      |
      v
GCS_MAVLink
      |
      v
AP_Param Update
      |
      v
New Configuration Active


## Safety Concept

Parameter system should ensure:
- Valid value ranges
- Safe updates
- Reliable storage
- Default recovery

## Future Expansion

AP_Param can support:
- Persistent memory storage
- Parameter groups
- Metadata description
- MAVLink parameter protocol
- Backup and restore

## Design Goal

All configuration data should be managed from one place.

Modules should request settings from AP_Param instead of creating independent configuration systems.
