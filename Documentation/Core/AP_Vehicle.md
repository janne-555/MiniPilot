# AP_Vehicle

Author: JANNE

## Overview
AP_Vehicle is the main vehicle management layer of MiniPilot.

It connects the complete autopilot system including sensors, estimation, navigation, control, communication and safety modules.

AP_Vehicle acts as the central coordinator between high level vehicle logic and individual subsystem modules.

## Files

AP_Vehicle.c
- Contains vehicle management implementation
- Handles vehicle initialization
- Coordinates subsystem updates

AP_Vehicle.h
- Defines vehicle interfaces
- Provides vehicle APIs and structures

## Responsibilities
AP_Vehicle manages:
- Vehicle initialization sequence
- System state management
- Module coordination
- Flight mode execution
- Sensor/control connection
- Vehicle level decisions

## Input Data

AP_Vehicle receives:
- Sensor state information
- Navigation information
- User commands
- Mission commands
- System status

Examples:
- Attitude from AP_AHRS
- Position from AP_EKF
- Pilot input from AP_RC
- Commands from GCS_MAVLink

## Output Data

AP_Vehicle provides:
- Vehicle state
- Mode decisions
- Control requests
- System status information

## Depends On

AP_HAL
- Hardware interface

AP_Scheduler
- Runtime execution control

AP_Param
- Vehicle configuration

AP_Mode / AP_FlightMode
- Current operating mode

## Used By

AP_Scheduler
- Calls vehicle update functions

GCS_MAVLink
- Reads vehicle status
- Sends commands

AP_Failsafe
- Checks vehicle condition

## Connected Modules

Sensor Layer:
- AP_IMU
- AP_GPS
- AP_Baro
- AP_Compass

Estimation Layer:
- AP_AHRS
- AP_EKF
- AP_InertialNav

Control Layer:
- AP_Control
- AP_PID
- AP_PosControl
- AP_Motors

Communication:
- GCS_MAVLink

## Data Flow

Sensors
   |
   v
AHRS / EKF
   |
   v
AP_Vehicle
   |
+--+-------------+
|                |
Modes        Controllers
                 |
                 v
              Motors


## Startup Flow

System Start
      |
      v
AP_HAL Init
      |
      v
AP_Vehicle Init
      |
      v
Initialize Modules
      |
      v
Scheduler Execution


## Runtime Flow

AP_Scheduler
      |
      v
AP_Vehicle Update
      |
      +-- Check vehicle state
      |
      +-- Process flight mode
      |
      +-- Update navigation
      |
      +-- Run controllers
      |
      +-- Update outputs


## Vehicle Expansion

Future vehicle support can be added:
- Multirotor
- Plane
- Rover
- Other autonomous systems

Common modules can be reused.

## Future Expansion

AP_Vehicle can support:
- Advanced mode management
- Multiple vehicle types
- Autonomous decision logic
- Advanced safety handling

## Design Goal

AP_Vehicle provides the high level brain of MiniPilot.

Subsystems perform individual tasks while AP_Vehicle coordinates the complete autopilot behavior.
