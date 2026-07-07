# AP_PID

Author: JANNE

## Overview
AP_PID is the PID controller module of MiniPilot.

It provides the basic feedback control algorithm used by higher level control systems.

PID controllers calculate correction output by comparing desired target values with current measured values.

## Files

AP_PID.c
- Contains PID calculation implementation
- Handles controller update logic
- Generates correction output

AP_PID.h
- Defines PID structures
- Provides PID APIs used by control modules

## Responsibilities
AP_PID manages:
- Proportional control
- Integral control
- Derivative control
- Error calculation
- Control output generation

## Input Data

AP_PID receives:

Target Value
- Desired system state

Feedback Value
- Current measured state

Configuration:
- P gain
- I gain
- D gain

## Output Data

AP_PID provides:
- Control correction value
- Controller output
- Error response

## Depends On

AP_Param
- Provides PID tuning values

AP_HAL
- Provides timing information if required

## Used By

AP_Control
- Uses PID output for control calculations

AP_PosControl
- Uses PID for position correction

AP_Motors
- Receives final control output

## Data Flow

Desired Target
       |
       v
    AP_PID
       ^
       |
Current Feedback

       |
       v

Control Output

## Control Loop Flow

Target Input
      |
      v
Calculate Error
      |
      v
Apply P/I/D Gains
      |
      v
Generate Output
      |
      v
Controller System

## Example Usage

Attitude Control:

Desired Angle
      |
      v
AP_PID
      ^
      |
Current Angle From AHRS

      |
      v
Motor Correction

## Runtime Flow

Scheduler Update
        |
        v
Controller Update
        |
        v
PID Calculation
        |
        v
Output Correction

## Future Expansion

AP_PID can support:
- Output limiting
- Integral protection
- Advanced filtering
- Feed forward control
- Dynamic tuning

## Design Goal

AP_PID only handles mathematical control calculation.

Vehicle logic and actuator handling remain in higher level modules.
