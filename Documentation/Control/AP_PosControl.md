# AP_PosControl

Author: JANNE

## Overview
AP_PosControl is the position control module of MiniPilot.

It converts navigation position targets into control requests required to move the vehicle.

AP_PosControl works between navigation logic and lower level control systems.

## Files

AP_PosControl.c
- Contains position control implementation
- Handles position error calculation
- Generates movement control requests

AP_PosControl.h
- Defines position control interfaces
- Provides APIs used by other modules

## Responsibilities
AP_PosControl manages:
- Position target tracking
- Position error calculation
- Velocity control interface
- Movement command generation

## Input Data

AP_PosControl receives:

AP_Nav
- Desired navigation targets
- Position commands

AP_InertialNav
- Current position
- Current velocity

AP_EKF
- Estimated vehicle state

## Output Data

AP_PosControl provides:
- Position correction output
- Velocity requests
- Movement control commands

## Depends On

AP_PID
- Provides feedback control calculations

AP_InertialNav
- Provides current navigation state

AP_EKF
- Provides estimated position

AP_Param
- Provides controller configuration

## Used By

AP_Control
- Uses position controller output

AP_Vehicle
- Executes vehicle movement logic

AP_Mode
- Provides mode based movement commands

## Data Flow

Mission / Mode Target
          |
          v
       AP_Nav
          |
          v
   AP_PosControl
          ^
          |
   AP_InertialNav
          |
          v
     AP_Control

## Control Flow

Target Position
        |
        v
Calculate Position Error
        |
        v
Generate Correction
        |
        v
Attitude/Control Request

## Runtime Flow

Scheduler Update
        |
        v
AP_PosControl Update
        |
        v
Read Position State
        |
        v
Calculate Movement Output
        |
        v
Send Control Request

## Future Expansion

AP_PosControl can support:
- Advanced position controllers
- Velocity control
- Acceleration control
- Autonomous movement logic
- Path following improvements

## Design Goal

AP_PosControl manages position based movement decisions.

Low level stabilization remains inside AP_Control.
