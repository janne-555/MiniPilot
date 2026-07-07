# AP_Mission

Author: JANNE

## Overview
AP_Mission is the autonomous mission management module of MiniPilot.

It handles mission commands, mission state and provides navigation targets required for autonomous operation.

AP_Mission works with navigation and communication modules to execute stored mission data.

## Files

AP_Mission.c
- Contains mission handling implementation
- Manages mission command processing
- Updates mission execution state

AP_Mission.h
- Defines mission structures
- Provides mission APIs used by other modules

## Responsibilities
AP_Mission manages:
- Mission command storage
- Mission execution flow
- Waypoint handling
- Mission state tracking
- Mission communication interface

## Input Data

AP_Mission receives:

GCS_MAVLink
- Mission upload commands
- Mission control requests

AP_Vehicle
- Current vehicle state

AP_Nav
- Navigation progress information

## Output Data

AP_Mission provides:
- Current mission command
- Navigation targets
- Mission status
- Mission progress information

## Depends On

AP_Nav
- Navigation execution

AP_Param
- Mission configuration

AP_HAL
- Future mission storage support

## Used By

AP_Nav
- Receives mission targets

AP_Vehicle
- Controls mission execution

GCS_MAVLink
- Uploads/downloads mission information

AP_Logger
- Records mission events

## Data Flow

Ground Station
       |
       v
GCS_MAVLink
       |
       v
AP_Mission
       |
       v
AP_Nav
       |
       v
Control System

## Startup Flow

System Start
      |
      v
AP_Mission Init
      |
      v
Load Mission Data
      |
      v
Mission System Ready

## Runtime Flow

Scheduler Update
        |
        v
AP_Mission Update
        |
        v
Check Current Command
        |
        v
Send Target To Navigation

## Mission Execution Flow

Mission List
      |
      v
Current Command
      |
      v
Navigation Target
      |
      v
Vehicle Movement
      |
      v
Next Command

## MAVLink Connection

Mission communication flow:

Mission Planner
        |
        v
MAVLink Messages
        |
        v
GCS_MAVLink
        |
        v
AP_Mission

## Future Expansion

AP_Mission can support:
- Complete waypoint missions
- Mission storage
- Resume mission
- Advanced commands
- Conditional commands
- Geofence integration

## Design Goal

AP_Mission only manages mission logic.

Navigation decides path execution and controllers handle vehicle movement.
