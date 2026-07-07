# AP_AHRS

Author: JANNE

## Overview
AP_AHRS (Attitude Heading Reference System) is the attitude estimation module of MiniPilot.

It processes sensor information and provides vehicle orientation data required for flight control and navigation.

AHRS works between raw sensors and higher level control systems.

## Files

AP_AHRS.c
- Contains attitude calculation implementation
- Updates vehicle orientation information
- Provides attitude data interface

AP_AHRS.h
- Defines AHRS data structures
- Provides attitude APIs used by other modules

## Responsibilities
AP_AHRS manages:
- Vehicle attitude estimation
- Roll calculation
- Pitch calculation
- Yaw/heading calculation
- Sensor data processing interface
- Orientation status

## Input Data

AP_AHRS receives sensor information from:
- AP_IMU
- AP_Compass
- AP_GPS
- AP_Baro

Input examples:
- Gyroscope data
- Acceleration data
- Magnetic heading
- Navigation references

## Output Data

AP_AHRS provides:
- Roll angle
- Pitch angle
- Yaw angle
- Vehicle attitude state
- Orientation information

## Depends On

AP_IMU
- Provides acceleration and gyro data

AP_Compass
- Provides heading reference

AP_Param
- Provides AHRS configuration

## Used By

AP_EKF
- Uses attitude information for estimation

AP_Control
- Uses attitude feedback for controllers

AP_Motors
- Receives control output based on attitude

AP_Vehicle
- Monitors vehicle orientation

GCS_MAVLink
- Sends attitude telemetry data

## Data Flow

AP_IMU
   |
   |
AP_Compass
   |
   v
AP_AHRS
   |
+--+----------+
|             |
v             v
AP_EKF    AP_Control

## Startup Flow

System Start
      |
      v
Sensor Init
      |
      v
AP_AHRS Init
      |
      v
Attitude System Ready

## Runtime Flow

Scheduler Update
        |
        v
AP_AHRS Update
        |
        v
Read Sensor Data
        |
        v
Calculate Attitude
        |
        v
Provide Roll/Pitch/Yaw

## Control Usage

Control system compares:

Desired Attitude
        |
        v
Controller
        |
        +
        |
Current Attitude
from AP_AHRS

Controller output is generated from attitude error.

## Future Expansion

AP_AHRS can support:
- Advanced attitude filters
- Multiple sensor sources
- Better heading estimation
- Sensor fault detection
- EKF integration improvements

## Design Goal

AP_AHRS converts sensor measurements into vehicle orientation.

Low level sensors remain separate and control modules use only processed attitude information.
