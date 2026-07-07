# AP_Mixer

Author: JANNE

## Overview
AP_Mixer is the actuator mixing module of MiniPilot.

It converts controller outputs into final actuator values based on vehicle configuration.

The mixer separates control logic from hardware output layout.

## Files

AP_Mixer.c
- Contains output mixing implementation
- Converts control inputs into actuator outputs

AP_Mixer.h
- Defines mixer interfaces
- Provides APIs used by motor/output modules

## Responsibilities
AP_Mixer manages:
- Control signal mixing
- Motor output calculation
- Vehicle output mapping
- Actuator distribution logic

## Input Data

AP_Mixer receives:

AP_Control
- Roll command
- Pitch command
- Yaw command
- Throttle command

Vehicle configuration:
- Motor layout
- Output type

## Output Data

AP_Mixer provides:
- Individual motor values
- Actuator commands
- Mixed control outputs

## Depends On

AP_Param
- Mixer configuration

AP_Control
- Control commands

## Used By

AP_Motors
- Uses mixed outputs for actuator control

AP_Vehicle
- Uses mixer through motor system

## Data Flow

AP_Control
     |
     v
AP_Mixer
     |
     v
AP_Motors
     |
     v
AP_HAL
     |
     v
Hardware

## Mixing Concept

Controller outputs describe vehicle movement.

Example:
- Roll
- Pitch
- Yaw
- Throttle

Mixer converts these commands into physical actuator values.

## Runtime Flow

Control Update
      |
      v
Receive Control Commands
      |
      v
Calculate Mixing
      |
      v
Generate Motor Outputs

## Future Expansion

AP_Mixer can support:
- Different frame types
- Multiple actuator layouts
- Servo mixing
- Custom vehicles
- Dynamic configuration

## Design Goal

AP_Mixer keeps vehicle layout logic separate.

Control algorithms remain independent from physical motor arrangement.
