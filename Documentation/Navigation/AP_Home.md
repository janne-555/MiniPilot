# AP_Home

Author: JANNE

## Overview
AP_Home is the home position management module of MiniPilot.

It maintains the vehicle home location reference used by navigation, mission and safety systems.

Home position acts as the reference point for autonomous operations.

## Files

AP_Home.c
- Contains home position management implementation
- Handles home location update logic
- Provides home data interface

AP_Home.h
- Defines home position structures
- Provides APIs used by other modules

## Responsibilities
AP_Home manages:
- Home location storage
- Home position updates
- Home status information
- Reference position handling

## Input Data

AP_Home receives:

AP_GPS
- Current GPS location

AP_EKF
- Valid estimated position

AP_Vehicle
- Vehicle state information

## Output Data

AP_Home provides:
- Home latitude
- Home longitude
- Home altitude reference
- Home status

## Depends On

AP_GPS
- Provides position data

AP_EKF
- Provides validated position estimate

AP_Param
- Home configuration values

## Used By

AP_Nav
- Uses home reference for navigation

AP_Mission
- Uses home position in mission operation

AP_Failsafe
- Uses home location for recovery actions

GCS_MAVLink
- Sends home position information

## Data Flow

AP_GPS
   |
   v
AP_EKF
   |
   v
AP_Home
   |
+--+----------+
|             |
v             v
AP_Nav   AP_Failsafe

## Startup Flow

System Start
      |
      v
AP_Home Init
      |
      v
Wait For Position
      |
      v
Set Home Location

## Runtime Flow

Position Available
        |
        v
Check Home Status
        |
        v
Update Home Data
        |
        v
Provide Reference Position

## Usage Concept

Home position is used as a fixed reference point.

Examples:
- Distance calculation
- Return operations
- Mission reference
- Safety actions

## Future Expansion

AP_Home can support:
- Automatic home update
- Moving home location
- Multiple reference points
- Advanced return logic

## Design Goal

AP_Home only manages home reference data.

Navigation and safety modules decide how the home information is used.
