# MiniPilot Complete System Flow

Author: JANNE

## Overview
This document explains the complete MiniPilot runtime architecture.

MiniPilot is designed as a modular autopilot system where each module has a specific responsibility.

The system is separated into:
- Hardware layer
- Core management layer
- Sensor layer
- Estimation layer
- Navigation layer
- Control layer
- Communication layer

## Complete Architecture

                  MiniPilot

                     |
                     v

                 AP_Vehicle

                     |
                     v

                AP_Scheduler

                     |
     +---------------+---------------+
     |               |               |
     v               v               v

  Sensors        Controllers     Communication

     |               |               |

 AP_IMU          AP_Control    GCS_MAVLink
 AP_GPS              |
 AP_Baro             |
 AP_Compass          v
                 AP_Motors

     |
     v

  AP_AHRS

     |
     v

   AP_EKF

     |
     v

Navigation System

     |
     v

Position Control


                     |
                     v

                  AP_HAL

                     |
        +------------+------------+
        |            |            |
      Linux        STM32       Future


## System Startup Order

System Power ON
        |
        v
Entry Point
        |
        v
AP_HAL Initialization
        |
        v
AP_Param Load Configuration
        |
        v
AP_Vehicle Initialization
        |
        v
Initialize Modules
        |
        v
Start AP_Scheduler
        |
        v
Runtime Loop


## Runtime Execution

MiniPilot runtime is controlled by AP_Scheduler.

AP_Scheduler calls modules periodically.

Flow:

AP_Scheduler
      |
      +-- Sensor Update
      |
      +-- Estimation Update
      |
      +-- Navigation Update
      |
      +-- Control Update
      |
      +-- Communication Update


## Sensor Data Flow

Physical Sensors
        |
        v
     AP_HAL
        |
        v
Sensor Modules

        |
+-------+-------+-------+
|       |       |       |
IMU    GPS    Baro   Compass

        |
        v

     AP_AHRS

        |
        v

      AP_EKF

        |
        v

 Vehicle State


## Navigation Flow

Estimated State
       |
       v
AP_InertialNav
       |
       v
AP_Nav
       |
       v
AP_PosControl


## Control Flow

Input Source
      |
      v
AP_Mode / AP_FlightMode
      |
      v
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
Hardware Output


## Communication Flow

External System
        |
        v
Communication Driver
        |
        v
GCS_MAVLink
        |
+-------+-------+-------+
|       |       |       |
Param Mission Status


## Module Dependency Direction

Higher layers depend on lower layers.

Example:

Vehicle
   |
Control
   |
Sensors
   |
HAL

Lower layers should not depend on higher layers.

AP_HAL should never depend on AP_Vehicle.

## Hardware Porting Flow

For new hardware:

Create Hardware Support
          |
          v
Implement AP_HAL
          |
          v
Run Existing MiniPilot Core

No changes required in:
- AHRS
- EKF
- Controllers
- Navigation
- MAVLink

## Development Rule

Each module should:
- Have one responsibility
- Provide clear interfaces
- Avoid direct hardware access
- Communicate through defined layers

## Final Goal

MiniPilot core should remain portable.

Same autopilot logic should run on:
- Simulation
- Linux
- STM32
- Future embedded systems
