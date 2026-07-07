# AP_Config

Author: JANNE

## Overview
AP_Config is the configuration management module of MiniPilot.

It maintains compile-time and system level configuration settings used across the autopilot firmware.

AP_Config provides a common location for project configuration.

## Files

AP_Config.h
- Defines system configuration values
- Provides configuration macros/settings used by modules

AP_Config.c
- Contains configuration related implementation if required

## Responsibilities
AP_Config manages:
- System configuration
- Feature enable/disable settings
- Build configuration
- Common definitions

## Input Data

AP_Config receives:
- Developer defined settings
- Build configuration values
- Platform configuration

Examples:
- Enabled modules
- Hardware options
- Feature selection

## Output Data

AP_Config provides:
- Configuration values
- Feature states
- System settings

## Depends On

No high level modules.

AP_Config should remain independent.

## Used By

AP_Vehicle
- Reads vehicle configuration

AP_HAL
- Uses platform settings

Sensor Modules
- Uses enabled feature settings

Control Modules
- Uses system configuration

GCS_MAVLink
- Uses communication settings

## Data Flow

Configuration File
        |
        v
    AP_Config
        |
+-------+-------+
|               |
Core        Modules

## Startup Flow

Build/System Start
        |
        v
Load Configuration
        |
        v
Compile/Initialize Modules

## Usage Concept

Configuration separates project settings from source logic.

Instead of changing module code:

Change Configuration
        |
        v
System Behavior Changes

## Future Expansion

AP_Config can support:
- Multiple board configurations
- Vehicle profiles
- Feature selection
- Hardware profiles

## Design Goal

AP_Config keeps MiniPilot configurable without modifying core module logic.
