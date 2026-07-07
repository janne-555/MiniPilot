# AP_GPS

Author: JANNE

## Overview
AP_GPS is the GPS management module of MiniPilot.

It handles global positioning information required for navigation, missions and vehicle location tracking.

GPS information is processed by MiniPilot and shared with navigation, estimation and communication modules.

## Files

AP_GPS.c
- Contains GPS module implementation
- Handles GPS data update process
- Maintains current GPS information

AP_GPS.h
- Defines GPS data structures
- Provides GPS APIs for other modules

## Responsibilities
AP_GPS manages:
- GPS position information
- Location updates
- GPS status handling
- Navigation data availability
- GPS data interface

## Input Data

AP_GPS receives:
- GPS sensor data
- Position information
- Time information
- Fix status

Data source:
- GPS hardware through AP_HAL

## Output Data

AP_GPS provides:
- Latitude
- Longitude
- Altitude
- Ground speed
- GPS status
- Position validity

## Depends On

AP_HAL
- Provides communication interface
- Handles hardware specific GPS connection

AP_Param
- GPS configuration parameters

## Used By

AP_EKF
- Uses GPS measurements for position estimation

AP_InertialNav
- Uses GPS position correction

AP_Nav
- Uses location for navigation calculations

AP_Mission
- Uses GPS position for waypoint execution

GCS_MAVLink
- Sends GPS telemetry data

## Data Flow

GPS Hardware
      |
      v
   AP_HAL
      |
      v
   AP_GPS
      |
+-----+---------+
|               |
v               v
AP_EKF       AP_Nav

## Startup Flow

System Start
      |
      v
AP_HAL Init
      |
      v
AP_GPS Init
      |
      v
GPS Ready

## Runtime Flow

Scheduler Update
        |
        v
AP_GPS Update
        |
        v
Read GPS Data
        |
        v
Update Position
        |
        v
Provide Navigation Data

## GPS Usage Flow

Position Data
      |
      v
AP_EKF
      |
      v
Navigation State
      |
      v
Control System

## Future Expansion

AP_GPS can support:
- Multiple GPS receivers
- GPS failover
- RTK GPS
- GPS health checking
- Advanced filtering

## Design Goal

AP_GPS manages only positioning information.

Navigation decisions and sensor fusion are handled by higher level modules.
