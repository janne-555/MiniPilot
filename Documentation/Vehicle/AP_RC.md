# AP_RC

Author: JANNE

## Overview
AP_RC is the remote control input processing module of MiniPilot.

It manages pilot control inputs and converts receiver data into usable commands for vehicle control.

AP_RC acts as the interface between user input and flight control logic.

## Files

AP_RC.c
- Contains RC input handling implementation
- Processes receiver channel data
- Updates pilot input values

AP_RC.h
- Defines RC data structures
- Provides RC input APIs used by other modules

## Responsibilities
AP_RC manages:
- Receiver input processing
- Channel value handling
- Pilot command generation
- RC status monitoring
- Input validation

## Input Data

AP_RC receives:

AP_HAL
- Hardware receiver data
- Communication interface data

Receiver Inputs:
- Roll channel
- Pitch channel
- Throttle channel
- Yaw channel
- Auxiliary channels

## Output Data

AP_RC provides:
- Pilot commands
- Normalized control inputs
- Mode switch requests
- RC connection status

## Depends On

AP_HAL
- Provides receiver interface

AP_Param
- Stores RC configuration
- Stores calibration values

## Used By

AP_Mode
- Uses mode selection inputs

AP_FlightMode
- Uses pilot commands

AP_Control
- Converts pilot request into control output

AP_Arming
- Uses arming commands

AP_Vehicle
- Monitors pilot input state

## Data Flow

RC Receiver
      |
      v
   AP_HAL
      |
      v
    AP_RC
      |
+-----+----------+
|                |
v                v
AP_Mode     AP_Control

## Startup Flow

System Start
      |
      v
AP_RC Init
      |
      v
Load Calibration
      |
      v
Ready For Input

## Runtime Flow

Scheduler Update
        |
        v
AP_RC Update
        |
        v
Read Input Channels
        |
        v
Process Commands
        |
        v
Send To Vehicle Logic

## Control Concept

Pilot input is not sent directly to motors.

Flow:

Pilot Input
     |
     v
AP_RC
     |
     v
Flight Mode
     |
     v
Controller
     |
     v
Motor Output

## Future Expansion

AP_RC can support:
- Multiple receiver protocols
- Channel mapping
- Input filtering
- Failsafe detection
- Custom controls

## Design Goal

AP_RC only manages input processing.

Flight decisions remain in mode and vehicle modules.
