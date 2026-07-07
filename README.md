# MiniPilot

Author: JANNE

## Overview
MiniPilot is a generic modular autopilot firmware project.

The goal of MiniPilot is to build a portable autopilot architecture where the core flight logic is independent from hardware platforms.

MiniPilot is designed with separated modules for:
- Hardware abstraction
- Sensors
- State estimation
- Navigation
- Control
- Communication
- Vehicle management

The same core architecture is intended to support:
- Linux
- STM32
- Future embedded platforms


## System Architecture

                    MiniPilot Core

                          |
                          v

                     AP_Vehicle

                          |
                          v

                    AP_Scheduler

                          |
        +-----------------+----------------+
        |                 |                |
        v                 v                v

     Sensors          Control       Communication

        |                 |                |

     AHRS/EKF         Motors        GCS_MAVLink

                          |
                          v

                       AP_HAL

                          |
             +------------+------------+
             |            |            |
           Linux        STM32       Future


## Main Modules

### Core
- AP_Vehicle
- AP_Scheduler
- AP_Param
- AP_Config

### Hardware Layer
- AP_HAL

### Sensors
- AP_IMU
- AP_GPS
- AP_Baro
- AP_Compass
- AP_Battery

### Estimation
- AP_AHRS
- AP_EKF
- AP_InertialNav

### Navigation
- AP_Nav
- AP_Mission
- AP_Home

### Control
- AP_Control
- AP_PID
- AP_PosControl
- AP_Mixer
- AP_Motors

### Vehicle
- AP_Mode
- AP_FlightMode
- AP_Arming
- AP_RC
- AP_Input
- AP_Failsafe

### Communication
- GCS_MAVLink


## Documentation

Complete project documentation is available inside:

Documentation/

Recommended reading order:

1. Architecture/MiniPilot_Architecture.md

2. Flows/Complete_System_Flow.md

3. Flows/Startup_Flow.md

4. Flows/Scheduler_Flow.md

5. Flows/Sensor_To_Control_Flow.md

6. Flows/MAVLink_Flow.md

7. Individual module documentation


## Design Goals

MiniPilot focuses on:

- Modular architecture
- Hardware independence
- Clean interfaces
- Easy expansion
- Portable autopilot core


## Development Direction

Future improvements:
- Additional hardware support
- Advanced sensors
- Improved estimation
- Vehicle specific features
- More communication support


## Project Rule

Hardware dependent code belongs in AP_HAL.

Autopilot logic remains independent and reusable.
