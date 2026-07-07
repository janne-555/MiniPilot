# AP_Baro

Author: JANNE

## Overview
AP_Baro is the barometer sensor module of MiniPilot.

It handles air pressure based altitude information and provides height measurements required for estimation and navigation.

## Files

AP_Baro.c
- Contains barometer processing implementation
- Updates pressure and altitude information
- Provides altitude data interface

AP_Baro.h
- Defines barometer structures
- Provides APIs used by other modules

## Responsibilities
AP_Baro manages:
- Pressure sensor data
- Altitude calculation data
- Barometer status
- Sensor update handling

## Input Data

AP_Baro receives:
- Raw pressure data
- Temperature data
- Sensor status

Data source:
- Barometer hardware through AP_HAL

## Output Data

AP_Baro provides:
- Pressure information
- Altitude information
- Barometer health status

## Depends On

AP_HAL
- Sensor communication interface
- Hardware access layer

AP_Param
- Sensor configuration values

## Used By

AP_EKF
- Uses altitude measurement for state estimation

AP_AHRS
- Uses altitude related information

AP_InertialNav
- Uses height estimation

AP_Nav
- Uses altitude for navigation

GCS_MAVLink
- Sends altitude telemetry information

## Data Flow

Barometer Sensor
        |
        v
     AP_HAL
        |
        v
    AP_Baro
        |
        v
     AP_EKF
        |
        v
Altitude Estimate

## Startup Flow

System Start
      |
      v
AP_HAL Init
      |
      v
AP_Baro Init
      |
      v
Sensor Ready

## Runtime Flow

Scheduler Update
        |
        v
AP_Baro Update
        |
        v
Read Pressure Data
        |
        v
Update Altitude Data

## Future Expansion

AP_Baro can support:
- Multiple barometers
- Sensor redundancy
- Temperature correction
- Advanced filtering
- Failure detection

## Design Goal

AP_Baro manages pressure based height information.

Sensor fusion and final altitude estimation are handled by navigation and EKF modules.
