# AP_Mode

Author: JANNE

## Overview
AP_Mode is the vehicle mode management module of MiniPilot.

It controls how the vehicle behaves in different operating states.

Flight behavior changes depending on the currently selected mode.

## Files

AP_Mode.c
- Contains mode handling implementation
- Manages mode update execution
- Controls mode switching logic

AP_Mode.h
- Defines mode interfaces
- Provides APIs used by vehicle modules

## Responsibilities
AP_Mode manages:
- Current vehicle mode
- Mode switching
- Mode execution flow
- Mode state handling

## Input Data

AP_Mode receives:

AP_RC
- Pilot input commands

GCS_MAVLink
- External mode change requests

AP_Vehicle
- Vehicle state information

AP_Mission
- Autonomous commands

## Output Data

AP_Mode provides:
- Current active mode
- Control targets
- Vehicle behavior commands

## Depends On

AP_Vehicle
- Vehicle state

AP_Control
- Sends control requests

AP_Param
- Mode configuration

## Used By

AP_Vehicle
- Executes selected vehicle behavior

AP_FlightMode
- Handles flight specific mode operation

GCS_MAVLink
- Reads and changes mode status

## Data Flow

Pilot / Ground Station
          |
          v
       AP_Mode
          |
          v
    AP_Control
          |
          v
     AP_Motors

## Mode Change Flow

Mode Request
      |
      v
Check Conditions
      |
      v
Change Mode
      |
      v
Execute New Behavior

## Runtime Flow

Scheduler Update
        |
        v
AP_Mode Update
        |
        v
Process Active Mode
        |
        v
Generate Control Request

## Safety Connection

Mode changes depend on:
- Arming state
- Sensor status
- Vehicle condition

Unsafe mode changes should be rejected.

## Future Expansion

AP_Mode can support:
- Manual modes
- Stabilized modes
- Autonomous modes
- Custom vehicle modes

## Design Goal

AP_Mode separates vehicle behavior logic from sensors, controllers and hardware.

New modes can be added without changing the complete autopilot system.
