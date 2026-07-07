# AP_FlightMode

Author: JANNE

## Overview
AP_FlightMode manages flight specific operating modes inside MiniPilot.

It defines how the vehicle should react during different flight states and connects mode decisions with control systems.

## Files

AP_FlightMode.c
- Contains flight mode implementation
- Handles flight mode execution logic
- Updates active flight behavior

AP_FlightMode.h
- Defines flight mode interfaces
- Provides APIs used by vehicle modules

## Responsibilities
AP_FlightMode manages:
- Flight state handling
- Mode execution
- Flight behavior control
- Mode specific logic

## Input Data

AP_FlightMode receives:

AP_Mode
- Current selected mode

AP_RC
- Pilot control inputs

AP_Mission
- Autonomous mission requests

AP_Vehicle
- Vehicle status

## Output Data

AP_FlightMode provides:
- Flight control requests
- Mode status
- Vehicle behavior commands

## Depends On

AP_Mode
- Provides selected operating mode

AP_Control
- Executes flight control requests

AP_Nav
- Provides navigation information

AP_Param
- Flight mode configuration

## Used By

AP_Vehicle
- Runs flight behavior logic

AP_Scheduler
- Executes periodic updates

GCS_MAVLink
- Reports current flight state

## Data Flow

Pilot / Mission
        |
        v
    AP_Mode
        |
        v
 AP_FlightMode
        |
        v
   AP_Control
        |
        v
   AP_Motors

## Startup Flow

System Start
      |
      v
Load Default Mode
      |
      v
Initialize Flight Mode
      |
      v
Ready For Execution

## Runtime Flow

Scheduler Update
        |
        v
Flight Mode Update
        |
        v
Process Mode Logic
        |
        v
Generate Control Target

## Mode Concept

Different flight modes can have different behavior.

Examples:
- Manual control
- Stabilized control
- Autonomous control
- Future custom modes

Each mode decides what command should be sent to the control layer.

## Safety Connection

Flight mode operation depends on:
- Arming state
- Sensor health
- Failsafe status

## Future Expansion

AP_FlightMode can support:
- Multiple vehicle types
- Advanced autonomous modes
- Custom flight behaviors
- Mode specific parameters

## Design Goal

AP_FlightMode keeps flight behavior separate from low level controllers.

New flight modes can be added without changing sensor or hardware layers.
