# MiniPilot Architecture

Author: JANNE

## Overview
MiniPilot is a modular autopilot firmware architecture.

The project is designed around independent modules where each system has a clear responsibility.

The main goal is to keep flight logic independent from hardware so the same autopilot core can run on different platforms.

Supported design targets:
- Linux
- STM32
- Future embedded systems

## Architecture Principle

MiniPilot follows layered design.

Higher layers perform vehicle decisions.

Lower layers provide services.

Flow:

Application Logic
        |
        v
Vehicle Layer
        |
        v
Core Services
        |
        v
Hardware Abstraction


## Complete Layer View

                AP_Vehicle

                     |
                     v

              AP_Scheduler

                     |
    +----------------+----------------+
    |                |                |
    v                v                v

 Sensors        Navigation        Control

    |                |                |

 AP_IMU          AP_Nav        AP_Control
 AP_GPS       AP_Mission       AP_PID
 AP_Baro          |            AP_Motors
 AP_Compass       |                |
                  |                |
                  +-------+--------+
                          |
                          v
                       AP_HAL

                          |
             +------------+------------+
             |            |            |
           Linux        STM32       Future


## Core Layer

Core modules control the complete system.

Modules:
- AP_Vehicle
- AP_Scheduler
- AP_Param
- AP_Config
- AP_Debug

Responsibilities:
- System management
- Runtime execution
- Configuration handling
- Module coordination


## Hardware Layer

Module:
- AP_HAL

Purpose:
Separate hardware from autopilot logic.

Provides:
- Communication
- Timing
- Sensors
- Outputs
- Platform services

Only HAL changes when porting hardware.


## Sensor Layer

Modules:
- AP_IMU
- AP_GPS
- AP_Baro
- AP_Compass
- AP_Battery

Purpose:
Collect physical world information.

Sensor modules only provide data.

They do not make vehicle decisions.


## Estimation Layer

Modules:
- AP_AHRS
- AP_EKF
- AP_InertialNav

Purpose:
Convert sensor information into vehicle state.

Provides:
- Attitude
- Position
- Velocity
- Navigation state


## Navigation Layer

Modules:
- AP_Nav
- AP_Mission
- AP_Home

Purpose:
Decide where the vehicle needs to move.

Navigation provides targets to controllers.


## Control Layer

Modules:
- AP_Control
- AP_PID
- AP_PosControl
- AP_Mixer
- AP_Motors

Purpose:
Convert desired movement into actuator commands.


## Vehicle Layer

Modules:
- AP_Mode
- AP_FlightMode
- AP_Arming
- AP_RC
- AP_Input
- AP_Failsafe

Purpose:
Manage vehicle behavior and safety.


## Communication Layer

Module:
- GCS_MAVLink

Purpose:
Connect MiniPilot with external systems.

Handles:
- Telemetry
- Commands
- Parameters
- Missions


## Runtime Data Direction

Input direction:

Hardware
   |
   v
Sensors
   |
   v
Estimation
   |
   v
Navigation


Output direction:

Navigation
    |
    v
Control
    |
    v
Motors
    |
    v
Hardware


## Dependency Rule

Modules should communicate through interfaces.

Correct:

AP_Control
     |
     v
AP_Motors
     |
     v
AP_HAL


Avoid:

High level modules directly accessing hardware.


## Porting Architecture

New Platform
      |
      v
Implement HAL
      |
      v
Run MiniPilot Core


No changes required for:
- Controllers
- Navigation
- Estimation
- MAVLink


## Future Development

MiniPilot architecture supports adding:
- New sensors
- New vehicles
- New processors
- New communication systems
- Advanced algorithms


## Design Goal

Build a scalable autopilot framework where every module can improve independently without breaking the complete system.
