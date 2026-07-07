# MiniPilot Startup Flow

Author: JANNE

## Overview
This document explains the MiniPilot startup sequence.

Startup flow defines how the system initializes hardware, loads configuration, prepares modules and enters the main autopilot loop.

The startup process is designed so platform-specific initialization stays inside AP_HAL while core logic remains portable.

## High Level Startup

System Start
      |
      v
Application Entry
      |
      v
AP_HAL Init
      |
      v
Core Modules Init
      |
      v
Vehicle Init
      |
      v
Scheduler Start
      |
      v
Autopilot Runtime Loop

## Step 1: System Entry

The entry point starts the MiniPilot system.

Responsibilities:
- Prepare runtime environment
- Start initialization sequence
- Transfer control to autopilot framework

Flow:

main()
  |
  v
MiniPilot Initialization

## Step 2: HAL Initialization

AP_HAL starts before other modules.

Purpose:
- Prepare hardware interfaces
- Initialize platform layer
- Provide system services

Flow:

System
  |
  v
AP_HAL
  |
  +-- Timer
  +-- Communication
  +-- GPIO
  +-- Sensor Interface
  +-- Output Interface

## Step 3: Parameter Initialization

AP_Param prepares system configuration.

Flow:

AP_Param Init
       |
       v
Load Configuration
       |
       v
Provide Settings

Used for:
- Sensor settings
- Control tuning
- Vehicle configuration

## Step 4: Vehicle Initialization

AP_Vehicle connects all autopilot subsystems.

Flow:

AP_Vehicle Init
       |
       +-- Sensors Init
       |
       +-- Estimation Init
       |
       +-- Control Init
       |
       +-- Communication Init

## Step 5: Sensor Startup

Sensor modules prepare data sources.

Initialization:

AP_IMU
AP_GPS
AP_Baro
AP_Compass

       |
       v

Sensor System Ready

## Step 6: Estimation Startup

After sensors are ready:

AP_AHRS
    |
    v
AP_EKF

Estimation modules prepare vehicle state calculation.

## Step 7: Control Startup

Control modules initialize.

Flow:

AP_PID
   |
AP_Control
   |
AP_Mixer
   |
AP_Motors

Controllers wait for valid system state.

## Step 8: Communication Startup

GCS_MAVLink starts communication services.

Responsible for:
- System status
- Parameters
- Mission data
- Telemetry messages

## Step 9: Scheduler Start

After initialization:

AP_Scheduler takes control.

Runtime:

while(system_running)
{
    Scheduler Update
}

## Runtime Execution Order

AP_Scheduler
      |
      +-- Update Sensors
      |
      +-- Update AHRS/EKF
      |
      +-- Update Navigation
      |
      +-- Update Control
      |
      +-- Update Communication

## Startup Dependency

Correct initialization order:

AP_HAL
  |
AP_Param
  |
AP_Vehicle
  |
Sensors
  |
Estimation
  |
Navigation
  |
Control
  |
Communication
  |
Scheduler Loop

## Platform Independence

Only AP_HAL changes between:

Linux
STM32
Future Hardware

All MiniPilot core modules follow the same startup process.

## Design Goal

Startup flow should remain clean and predictable.

Every module initializes its own responsibility and the scheduler controls runtime execution.
