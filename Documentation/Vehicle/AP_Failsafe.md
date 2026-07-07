# AP_Failsafe

Author: JANNE

## Overview
AP_Failsafe is the safety monitoring module of MiniPilot.

It detects abnormal conditions and provides protection actions to maintain vehicle safety.

Failsafe works continuously during system operation.

## Files

AP_Failsafe.c
- Contains failsafe checking implementation
- Monitors system failure conditions
- Updates failsafe status

AP_Failsafe.h
- Defines failsafe interfaces
- Provides safety status APIs

## Responsibilities
AP_Failsafe manages:
- System health monitoring
- Failure detection
- Safety state handling
- Emergency condition processing

## Input Data

AP_Failsafe receives:

AP_Battery
- Battery voltage/status

AP_RC
- Input connection status

AP_GPS
- Position availability

AP_EKF
- Estimation health

AP_Vehicle
- Vehicle operating state

## Output Data

AP_Failsafe provides:
- Failsafe status
- Warning information
- Safety action requests

## Depends On

AP_Vehicle
- Current vehicle state

AP_Param
- Safety configuration values

Sensor Modules
- Health information

## Used By

AP_Arming
- Prevents unsafe arming

AP_Motors
- Controls output safety

AP_Mode
- Changes behavior during failures

GCS_MAVLink
- Reports failsafe status

## Data Flow

System Modules
       |
       v
 AP_Failsafe
       |
+------+------+
|             |
v             v
Arming     Vehicle Action

## Startup Flow

System Start
      |
      v
AP_Failsafe Init
      |
      v
Start Monitoring
      |
      v
Ready

## Runtime Flow

Scheduler Update
        |
        v
Check System Status
        |
        v
Detect Problems
        |
        v
Update Safety State

## Safety Checks

Possible checks:
- Sensor failure
- Low battery
- Communication loss
- Invalid vehicle state
- Navigation failure

## Future Expansion

AP_Failsafe can support:
- Multiple failsafe levels
- Return actions
- Emergency landing logic
- Advanced health monitoring
- Custom safety rules

## Design Goal

AP_Failsafe only detects and reports unsafe conditions.

Vehicle modules decide the correct recovery action based on failsafe status.
