# AP_Control

Author: JANNE

## Overview
AP_Control is the main control processing module of MiniPilot.

It converts desired vehicle commands into control outputs using feedback from estimation modules.

AP_Control works between navigation/vehicle logic and actuator output modules.

## Files

AP_Control.c
- Contains control system implementation
- Processes control updates
- Generates actuator control requests

AP_Control.h
- Defines control interfaces
- Provides APIs used by MiniPilot modules

## Responsibilities
AP_Control manages:
- Attitude control processing
- Control error calculation
- Controller execution
- Output command generation
- Connection between estimation and actuators

## Input Data

AP_Control receives:

AP_AHRS
- Current vehicle attitude
- Roll/Pitch/Yaw information

AP_EKF
- Estimated vehicle state

AP_Nav
- Navigation targets

AP_Mode
- Current mode commands

AP_RC
- Pilot input commands

## Output Data

AP_Control provides:
- Roll control output
- Pitch control output
- Yaw control output
- Throttle/control requests
- Actuator commands

## Depends On

AP_PID
- Provides control calculations

AP_AHRS
- Provides attitude feedback

AP_EKF
- Provides vehicle state

AP_Param
- Provides control tuning values

## Used By

AP_Vehicle
- Runs vehicle control logic

AP_Motors
- Converts control output into motor signals

AP_Mode
- Sends desired control targets

## Data Flow

Pilot / Mission Input
          |
          v
       AP_Mode
          |
          v
     AP_Control
          ^
          |
     AHRS / EKF

          |
          v

     AP_Motors

## Control Loop Flow

Desired State
       |
       v
Compare With Feedback
       |
       v
AP_PID Calculation
       |
       v
Control Output
       |
       v
Motor System

## Runtime Flow

Scheduler Update
        |
        v
AP_Control Update
        |
        v
Read Vehicle State
        |
        v
Calculate Correction
        |
        v
Send Output Command

## Future Expansion

AP_Control can support:
- Advanced controllers
- Multiple vehicle types
- Adaptive control
- Feed forward control
- Autonomous control modes

## Design Goal

AP_Control handles control decisions only.

Sensor estimation stays in AHRS/EKF and hardware output remains inside actuator modules.
