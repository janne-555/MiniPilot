# AP_Arming

Author: JANNE

## Overview
AP_Arming is the safety management module responsible for controlling vehicle arming and disarming.

It verifies system conditions before allowing motor outputs or active vehicle operation.

## Files

AP_Arming.c
- Contains arming logic implementation
- Handles arm/disarm state changes
- Performs safety checks

AP_Arming.h
- Defines arming interfaces
- Provides arming status access

## Responsibilities
AP_Arming manages:
- Vehicle arm state
- Disarm state
- Safety verification
- Pre-operation checks
- Arming permission control

## Input Data

AP_Arming receives:

AP_Vehicle
- Vehicle status information

AP_IMU
- Sensor readiness

AP_GPS
- Position availability

AP_Battery
- Power status

AP_RC
- User arming commands

GCS_MAVLink
- Remote arm/disarm requests

## Output Data

AP_Arming provides:
- Armed status
- Safety status
- Arming result
- System readiness information

## Depends On

AP_Vehicle
- Overall system state

AP_Failsafe
- Safety condition checking

AP_Param
- Arming configuration

## Used By

AP_Motors
- Enables or disables actuator output

AP_Control
- Checks control permission

AP_Vehicle
- Tracks operational state

GCS_MAVLink
- Reports arming status

## Data Flow

User Command
      |
      v
AP_Arming
      |
      v
Safety Checks
      |
      +---- Sensors
      |
      +---- Battery
      |
      +---- System State
      |
      v
Allow Vehicle Operation

## Startup Flow

System Start
      |
      v
AP_Arming Init
      |
      v
Vehicle Starts Disarmed
      |
      v
Wait For Arm Request

## Runtime Flow

Arm Request
      |
      v
Check System Status
      |
      v
Validate Conditions
      |
      v
Update Arm State

## Safety Concept

Before arming, system checks can include:
- Sensor health
- Communication status
- Battery condition
- Vehicle configuration

## Future Expansion

AP_Arming can support:
- Advanced pre-arm checks
- Hardware safety switch
- Custom safety rules
- Multiple vehicle requirements

## Design Goal

AP_Arming protects vehicle operation.

Motors and control outputs should only become active after required safety conditions pass.
