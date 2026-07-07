# AP_Nav

Author: JANNE

## Overview
AP_Nav is the navigation management module of MiniPilot.

It converts vehicle position information into navigation decisions required for autonomous movement.

AP_Nav works between estimation systems and control systems.

## Files

AP_Nav.c
- Contains navigation processing implementation
- Handles navigation update logic
- Provides navigation commands

AP_Nav.h
- Defines navigation interfaces
- Provides APIs used by other modules

## Responsibilities
AP_Nav manages:
- Navigation calculations
- Position target handling
- Movement planning interface
- Navigation state management

## Input Data

AP_Nav receives:

AP_InertialNav
- Current position
- Current velocity
- Movement state

AP_EKF
- Estimated vehicle state

AP_Mission
- Target waypoint information

AP_Home
- Home position reference

## Output Data

AP_Nav provides:
- Navigation targets
- Movement requests
- Position commands
- Direction information

## Depends On

AP_InertialNav
- Position feedback

AP_EKF
- Vehicle estimation

AP_Mission
- Mission targets

AP_Param
- Navigation settings

## Used By

AP_PosControl
- Converts navigation target into control request

AP_Control
- Uses navigation commands

AP_Vehicle
- Manages navigation operation

GCS_MAVLink
- Sends navigation status

## Data Flow

AP_Mission
     |
     v
  AP_Nav
     ^
     |
AP_InertialNav
     |
     v
AP_PosControl
     |
     v
AP_Control

## Startup Flow

System Start
      |
      v
Sensor System Ready
      |
      v
Navigation Init
      |
      v
Ready For Navigation

## Runtime Flow

Scheduler Update
        |
        v
AP_Nav Update
        |
        v
Read Vehicle Position
        |
        v
Calculate Navigation Target
        |
        v
Send Target To Controllers

## Mission Flow

Mission Command
        |
        v
AP_Mission
        |
        v
AP_Nav
        |
        v
Position Controller

## Future Expansion

AP_Nav can support:
- Advanced path planning
- Obstacle avoidance
- Different navigation modes
- Autonomous route control
- External navigation systems

## Design Goal

AP_Nav handles navigation decisions only.

Sensor estimation stays in EKF and physical movement control stays in controller modules.
