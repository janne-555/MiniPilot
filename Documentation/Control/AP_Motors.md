# AP_Motors

Author: JANNE

## Overview
AP_Motors is the actuator output management module of MiniPilot.

It converts control commands into motor output signals required by the vehicle hardware.

AP_Motors is the final control stage before commands are sent to the hardware layer.

## Files

AP_Motors.c
- Contains motor output implementation
- Handles actuator command processing
- Updates motor outputs

AP_Motors.h
- Defines motor interfaces
- Provides APIs used by control modules

## Responsibilities
AP_Motors manages:
- Motor output generation
- Actuator command handling
- Output limiting
- Motor state management
- Connection between controllers and hardware

## Input Data

AP_Motors receives:

AP_Control
- Roll output
- Pitch output
- Yaw output
- Throttle commands

AP_Mixer
- Mixed actuator values

AP_Arming
- Motor enable/disable state

## Output Data

AP_Motors provides:
- Final motor commands
- Actuator output values
- Motor status information

## Depends On

AP_HAL
- Provides hardware output interface
- Sends signals to physical actuators

AP_Mixer
- Provides output mixing logic

AP_Param
- Provides motor configuration

## Used By

AP_Control
- Sends control output

AP_Vehicle
- Manages vehicle output state

AP_Failsafe
- Controls emergency output behavior

## Data Flow

AP_Control
     |
     v
AP_Motors
     |
     v
AP_HAL
     |
     v
Motor Hardware

## Output Flow

Control Commands
        |
        v
Process Motor Output
        |
        v
Apply Limits/Safety
        |
        v
Send Through HAL

## Runtime Flow

Scheduler Update
        |
        v
AP_Motors Update
        |
        v
Receive Control Values
        |
        v
Generate Output
        |
        v
Hardware Signal

## Safety Connection

Motor output depends on:
- Arming state
- Failsafe state
- Vehicle condition

Unsafe conditions should prevent unwanted outputs.

## Future Expansion

AP_Motors can support:
- Multiple vehicle motor layouts
- ESC protocols
- Servo outputs
- Output testing
- Advanced motor mixing

## Design Goal

AP_Motors manages actuator outputs only.

Control calculations stay in AP_Control and hardware access stays inside AP_HAL.
