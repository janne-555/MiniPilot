# AP_Input

Author: JANNE

## Overview
AP_Input manages external user input sources for MiniPilot.

The input layer converts different input methods into common vehicle commands.

Currently MiniPilot uses keyboard based input for Linux simulation.

Future hardware targets can add RC receivers, joystick or other input sources without changing vehicle logic.

## Files

AP_Keyboard.c
- Handles Linux keyboard input
- Reads user commands during simulation
- Converts keyboard actions into control requests

AP_Keyboard.h
- Defines keyboard input interface
- Provides input functions

## Responsibilities

AP_Input manages:
- User input collection
- Input abstraction
- Command processing
- Simulation control input

## Current Implementation

Current flow:

Keyboard
    |
    v
AP_Keyboard
    |
    v
MiniPilot Input System


## Input Data

AP_Input receives:

Linux Keyboard:
- Manual commands
- Test inputs
- Simulation controls

Future:
- RC receiver
- Joystick
- Companion computer


## Output Data

Provides:
- Processed commands
- User requests
- Control inputs


## Depends On

Operating system input interface

For Linux:
- Terminal input APIs


## Used By

AP_RC
- Uses keyboard input for simulation

AP_Control
- Receives processed control requests

AP_Mode
- Uses command selection

AP_Vehicle
- Uses vehicle input state


## Real Current Flow

AP_Keyboard
      |
      v
AP_RC
      |
      v
AP_FlightMode
      |
      v
AP_Control


## Future Hardware Flow

RC Receiver
      |
      v
AP_HAL
      |
      v
Input Layer
      |
      v
Vehicle Logic


## Future Expansion

AP_Input can support:
- RC protocols
- Joystick input
- External commands
- Autonomous input sources


## Design Goal

Input sources remain separated from vehicle logic.

Only input drivers change when moving from Linux simulation to STM32 hardware.
