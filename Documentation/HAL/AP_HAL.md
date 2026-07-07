# AP_HAL

Author: JANNE

## Overview
AP_HAL (Hardware Abstraction Layer) is the hardware interface layer of MiniPilot.

It separates autopilot core logic from platform-specific implementation.

Core modules do not access hardware directly. All hardware communication happens through AP_HAL interfaces.

## Files

AP_HAL.c
- Contains HAL implementation layer
- Handles platform interface functions
- Provides hardware services to MiniPilot modules

AP_HAL.h
- Defines HAL APIs
- Provides common hardware interface definitions

## Responsibilities
AP_HAL manages:
- System initialization
- Timing services
- Communication interfaces
- Sensor hardware access
- Output interfaces
- Platform abstraction

## Input Data

AP_HAL receives requests from upper layers.

Examples:
- Send data request from GCS_MAVLink
- Sensor read request from AP_IMU
- Motor output request from AP_Motors
- Timing request from AP_Scheduler

## Output Data

AP_HAL provides:
- Sensor raw data
- Communication data
- System timing information
- Hardware status
- Output signal generation

## Depends On

Platform Drivers

Examples:
- Linux drivers
- STM32 HAL drivers
- Future hardware drivers

AP_HAL is the lowest MiniPilot layer.

It should not depend on flight modules.

## Used By

AP_Scheduler
- Gets timing information

AP_IMU
- Gets sensor communication access

AP_GPS
- Gets GPS communication data

AP_Baro
- Gets pressure sensor data

AP_Compass
- Gets compass sensor data

AP_Motors
- Sends motor output commands

GCS_MAVLink
- Sends and receives communication data

## Data Flow

Sensors / Hardware
        |
        v
Platform Driver
        |
        v
AP_HAL
        |
        +------------+
        |            |
        v            v
Sensor Modules   Communication
        |
        v
 Autopilot Core

## Startup Flow

System Start
      |
      v
AP_HAL Init
      |
      v
Hardware Setup
      |
      v
MiniPilot Modules Start

## Runtime Flow

MiniPilot Module
        |
        v
AP_HAL API
        |
        v
Hardware Operation

## Porting Design

For new hardware support:

Add:
- New driver layer
- New HAL implementation

Do not modify:
- Navigation
- Control
- Communication
- Vehicle logic

## Future Expansion

AP_HAL can support:
- Multiple MCU targets
- RTOS platforms
- Additional communication buses
- New sensor drivers

## Design Goal

Hardware changes remain inside AP_HAL.

MiniPilot core remains platform independent.
