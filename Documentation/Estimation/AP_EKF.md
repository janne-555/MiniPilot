# AP_EKF

Author: JANNE

## Overview
AP_EKF (Extended Kalman Filter) is the state estimation module of MiniPilot.

It combines information from multiple sensors and provides a reliable estimate of the vehicle state.

EKF acts as the main sensor fusion layer between sensors and navigation/control systems.

## Files

AP_EKF.c
- Contains EKF processing implementation
- Handles estimation update logic
- Maintains vehicle state information

AP_EKF.h
- Defines EKF interfaces
- Provides estimation data access for other modules

## Responsibilities
AP_EKF manages:
- Sensor fusion
- State estimation
- Position estimation
- Velocity estimation
- Navigation state calculation
- Estimation health monitoring

## Input Data

AP_EKF receives data from:

AP_IMU
- Acceleration
- Angular rate

AP_GPS
- Position
- Velocity

AP_Baro
- Altitude reference

AP_Compass
- Heading reference

AP_AHRS
- Attitude information

## Output Data

AP_EKF provides:
- Estimated position
- Estimated velocity
- Vehicle state
- Navigation information
- EKF health/status

## Depends On

AP_IMU
- Motion measurements

AP_GPS
- Global position updates

AP_Baro
- Height measurements

AP_Compass
- Direction reference

AP_Param
- EKF configuration

## Used By

AP_InertialNav
- Navigation calculations

AP_Nav
- Position based navigation

AP_PosControl
- Position control feedback

AP_Vehicle
- Vehicle state monitoring

GCS_MAVLink
- Sends EKF status telemetry

## Data Flow

Sensors
   |
   +-- AP_IMU
   |
   +-- AP_GPS
   |
   +-- AP_Baro
   |
   +-- AP_Compass
            |
            v
          AP_EKF
            |
     +------+------+
     |             |
     v             v
Navigation     Control

## Startup Flow

System Start
      |
      v
Sensor Init
      |
      v
AP_EKF Init
      |
      v
Initialize State
      |
      v
Ready For Estimation

## Runtime Flow

Scheduler Update
        |
        v
AP_EKF Update
        |
        v
Collect Sensor Data
        |
        v
Fuse Measurements
        |
        v
Update Vehicle State

## Estimation Concept

Individual sensors contain errors.

Examples:
- IMU drift
- GPS delay
- Compass noise
- Barometer variation

EKF combines sensors to create a more reliable vehicle estimate.

## Future Expansion

AP_EKF can support:
- Advanced prediction models
- Multiple EKF instances
- Sensor fault detection
- GPS failure handling
- External navigation sources

## Design Goal

AP_EKF provides a trusted vehicle state.

Control and navigation modules use EKF output instead of directly depending on raw sensors.
