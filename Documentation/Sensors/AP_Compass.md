# AP_Compass

Author: JANNE

## Overview
AP_Compass is the magnetic sensor management module of MiniPilot.

It provides heading information by processing magnetometer data and supplies direction reference data for attitude and navigation systems.

## Files

AP_Compass.c
- Contains compass processing implementation
- Handles magnetic field data updates
- Maintains compass sensor information

AP_Compass.h
- Defines compass data structures
- Provides compass APIs used by other modules

## Responsibilities
AP_Compass manages:
- Magnetometer data processing
- Heading reference information
- Compass sensor status
- Magnetic field measurements

## Input Data

AP_Compass receives:
- Magnetic field measurements
- Sensor status information
- Calibration values

Data source:
- Compass hardware through AP_HAL

## Output Data

AP_Compass provides:
- Magnetic field data
- Heading information
- Compass health status

## Depends On

AP_HAL
- Provides sensor communication
- Handles hardware access

AP_Param
- Stores compass configuration
- Stores calibration values

## Used By

AP_AHRS
- Uses compass data for attitude heading reference

AP_EKF
- Uses magnetic measurements for state estimation

AP_Nav
- Uses heading information for navigation

GCS_MAVLink
- Sends compass status information

## Data Flow

Compass Sensor
        |
        v
     AP_HAL
        |
        v
  AP_Compass
        |
+-------+-------+
|               |
v               v
AP_AHRS       AP_EKF

## Startup Flow

System Start
      |
      v
AP_HAL Init
      |
      v
AP_Compass Init
      |
      v
Load Calibration
      |
      v
Ready For Updates

## Runtime Flow

Scheduler Update
        |
        v
AP_Compass Update
        |
        v
Read Magnetic Data
        |
        v
Process Heading Data
        |
        v
Provide Data To AHRS/EKF

## Calibration Concept

Compass calibration removes sensor errors.

Calibration handles:
- Magnetic offsets
- Sensor alignment
- External interference correction

## Future Expansion

AP_Compass can support:
- Multiple compass sensors
- Automatic compass selection
- Magnetic interference detection
- Advanced calibration

## Design Goal

AP_Compass manages magnetic sensor information only.

Attitude calculation and sensor fusion are handled by AP_AHRS and AP_EKF.
