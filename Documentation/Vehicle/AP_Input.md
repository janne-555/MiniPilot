# AP_Input

Author: JANNE

## Overview
AP_Input is the input abstraction module of MiniPilot.

It manages external input sources and provides a common interface for vehicle control commands.

AP_Input separates input sources from the main vehicle logic.

## Files

AP_Input.c
- Contains input processing implementation
- Handles input update logic
- Provides input data to vehicle modules

AP_Input.h
- Defines input interfaces
- Provides APIs used by MiniPilot modules

## Responsibilities
AP_Input manages:
- Input source handling
- Input data processing
- Command abstraction
- Input status tracking

## Input Data

AP_Input receives data from:

AP_RC
- Pilot control commands

GCS_MAVLink
- External control commands

Future Sources:
- Companion computer commands
- Autonomous systems

## Output Data

AP_Input provides:
- Vehicle command requests
- Processed input values
- Input source status

## Depends On

AP_HAL
- Provides hardware input interfaces

AP_RC
- Provides receiver data

AP_Param
- Provides input configuration

## Used By

AP_Vehicle
- Uses input state

AP_Mode
- Selects behavior based on input

AP_Control
- Receives control targets

AP_Arming
- Receives user commands

## Data Flow

External Input
       |
       v
   AP_Input
       |
+------+------+
|             |
v             v
AP_Mode   AP_Control

## Startup Flow

System Start
      |
      v
AP_Input Init
      |
      v
Configure Sources
      |
      v
Ready For Commands

## Runtime Flow

Scheduler Update
        |
        v
AP_Input Update
        |
        v
Read Input Sources
        |
        v
Process Commands
        |
        v
Update Vehicle Request

## Input Concept

Different command sources should use the same interface.

Example:

RC Controller
      |
Ground Station
      |
Companion Computer
      |
      v
AP_Input
      |
      v
Vehicle Logic

## Future Expansion

AP_Input can support:
- Multiple input sources
- Input priority handling
- External APIs
- Autonomous commands
- Safety filtering

## Design Goal

AP_Input isolates command sources from vehicle logic.

New input methods can be added without changing control modules.
