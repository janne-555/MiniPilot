# AP_IMU

Author: JANNE

## Overview
AP_IMU is the Inertial Measurement Unit processing module of MiniPilot.

It manages motion sensor data required for attitude estimation and vehicle stabilization.

IMU data is one of the primary inputs for the autopilot control system.

## Files

AP_IMU.c
- Contains IMU processing implementation
- Handles sensor data updates
- Provides motion information to other modules

AP_IMU.h
- Defines IMU data structures
- Provides IMU interfaces for MiniPilot modules

## Responsibilities
AP_IMU manages:
- Accelerometer data processing
- Gyroscope data processing
- Sensor update handling
- Raw sensor conversion
- Motion information output

## Input Data

AP_IMU receives raw sensor data from hardware through AP_HAL.

Examples:
- Acceleration values
- Angular velocity values
- Sensor timestamps

Sensor examples:
- Accelerometer
- Gyroscope

## Output Data

AP_IMU provides processed motion data.

Outputs:
- Linear acceleration
- Angular rates
- IMU health status
- Sensor update status

This data is used for attitude and navigation estimation.

## Depends On

AP_HAL
- Sensor communication
- SPI/I2C interface
- Timing information

AP_Param
- Sensor configuration
- Calibration values

## Used By

AP_AHRS
- Uses IMU data to calculate vehicle attitude

AP_EKF
- Uses IMU measurements for state estimation

AP_InertialNav
- Uses motion data for navigation calculation

AP_Control
- Uses attitude information generated from IMU processing

GCS_MAVLink
- Sends IMU related telemetry information

## Data Flow

Physical IMU Sensor
        |
        v
     AP_HAL
        |
        v
     AP_IMU
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
AP_IMU Init
      |
      v
Sensor Configuration
      |
      v
Ready For Updates

## Runtime Flow

Scheduler Update
        |
        v
AP_IMU Update
        |
        v
Read Sensor Data
        |
        v
Process Measurements
        |
        v
Provide Data To AHRS/EKF

## Calibration Concept

IMU calibration is required to correct sensor errors.

Calibration can include:
- Gyroscope offset correction
- Accelerometer offset correction
- Sensor alignment

## Future Expansion

AP_IMU can support:
- Multiple IMU sensors
- Sensor redundancy
- Temperature compensation
- Advanced filtering
- Failure detection

## Design Goal

AP_IMU only manages inertial sensor processing.

Higher level attitude and navigation calculations are handled by AHRS and EKF modules.
