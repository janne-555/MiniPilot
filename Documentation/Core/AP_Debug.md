# AP_Debug

Author: JANNE

## Overview
AP_Debug is the debugging support module of MiniPilot.

It provides debugging interfaces used to observe system behavior during development, testing and troubleshooting.

Debug functionality helps verify module operation without affecting core autopilot logic.

## Files

AP_Debug.c
- Contains debug implementation
- Handles debug message processing
- Provides system debugging support

AP_Debug.h
- Defines debug interfaces
- Provides APIs used by MiniPilot modules

## Responsibilities
AP_Debug manages:
- Debug message handling
- System information output
- Runtime verification support
- Development diagnostics

## Input Data

AP_Debug receives:

System Modules
- Status information
- Debug messages
- Error information
- Runtime values

Examples:
- Sensor values
- Control states
- Communication status
- System events

## Output Data

AP_Debug provides:
- Debug messages
- Diagnostic information
- Runtime visibility
- Error reports

## Depends On

AP_HAL
- Provides output interface

Examples:
- Console output
- UART output
- Future debug interfaces

## Used By

AP_Vehicle
- Vehicle state debugging

Sensor Modules
- Sensor data verification

Control Modules
- Control output checking

GCS_MAVLink
- Communication debugging

AP_Scheduler
- Task execution monitoring

## Data Flow

MiniPilot Modules
        |
        v
    AP_Debug
        |
        v
 Debug Interface

## Startup Flow

System Start
      |
      v
AP_Debug Init
      |
      v
Debug Interface Ready

## Runtime Flow

Module Event
      |
      v
Debug Request
      |
      v
AP_Debug Process
      |
      v
Output Debug Data

## Usage Concept

Debug system should observe module behavior.

It should not control vehicle operation.

## Future Expansion

AP_Debug can support:
- Different debug levels
- Log filtering
- Runtime analysis
- Performance monitoring
- Hardware debug interfaces

## Design Goal

AP_Debug keeps debugging functionality separated from flight logic.

Debug features can be enabled or disabled without affecting autopilot operation.
