# AP_InertialNav

Author: JANNE

## Overview
AP_InertialNav is the inertial navigation module of MiniPilot.

It provides navigation related calculations using estimated vehicle motion and state information.

It works above sensor fusion and provides navigation data required by position control and mission systems.

## Files

AP_InertialNav.c
- Contains inertial navigation implementation
- Processes navigation state updates
- Provides position and movement information

AP_InertialNav.h
- Defines navigation interfaces
- Provides APIs used by other modules

## Responsibilities
AP_InertialNav manages:
- Position information handling
- Velocity information handling
- Movement estimation
- Navigation data interface

## Input Data

AP_InertialNav receives:

AP_EKF
- Estimated position
- Estimated velocity
- Vehicle state

AP_IMU
- Motion information

AP_GPS
- Position reference

## Output Data

AP_InertialNav provides:
- Navigation position
- Velocity information
- Movement state
- Data for position control

## Depends On

AP_EKF
- Main estimated vehicle state

AP_IMU
- Motion updates

AP_GPS
- Position reference

AP_Param
- Navigation configuration

## Used By

AP_Nav
- Uses position information for navigation

AP_PosControl
- Uses position feedback

AP_Mission
- Uses navigation state for mission execution

AP_Vehicle
- Uses navigation information

GCS_MAVLink
- Sends navigation telemetry

## Data Flow

Sensors
   |
   v
AP_EKF
   |
   v
AP_InertialNav
   |
+--+------------+
|               |
v               v
AP_Nav     AP_PosControl

## Startup Flow

System Start
      |
      v
Sensor Init
      |
      v
EKF Init
      |
      v
AP_InertialNav Init
      |
      v
Navigation Ready

## Runtime Flow

Scheduler Update
        |
        v
AP_InertialNav Update
        |
        v
Read Estimated State
        |
        v
Update Navigation Data
        |
        v
Provide Position Information

## Navigation Concept

Raw sensor data is not directly used for navigation.

Flow:
Sensors
  |
  v
State Estimation
  |
  v
Inertial Navigation
  |
  v
Position Control

## Future Expansion

AP_InertialNav can support:
- Advanced navigation filtering
- Dead reckoning
- GPS loss handling
- External position sources
- Improved motion prediction

## Design Goal

AP_InertialNav separates navigation calculations from raw sensors and control logic.

It provides a clean navigation interface for higher level autopilot modules.
