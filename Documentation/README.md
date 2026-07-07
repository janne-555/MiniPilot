# MiniPilot Autopilot Firmware

Author: JANNE

## Overview

MiniPilot is a generic modular autopilot firmware.

The goal of MiniPilot is to create a portable flight control
architecture which can run on different hardware platforms.

The core autopilot logic is separated from hardware using
AP_HAL (Hardware Abstraction Layer).

Supported targets:
- Linux
- STM32
- Future embedded platforms

## High Level Architecture

                    MiniPilot
                        |
                   AP_Vehicle
                        |
                  AP_Scheduler
                        |
        +---------------+---------------+
        |               |               |
     Sensors         Control     Communication
        |               |               |
     AHRS/EKF       Motors       GCS_MAVLink
                        |
                     AP_HAL
                        |
              Linux / STM32 / Future


## Documentation Structure

### Architecture

System level design.

Files:
- System_Architecture.md
- Startup_Flow.md
- Scheduler_Flow.md
- Data_Flow.md


### Core Modules

#### AP_Vehicle
Main vehicle management layer.

#### AP_Scheduler
Controls periodic task execution.

#### AP_Param
Parameter storage and configuration.

#### AP_Config
Project configuration handling.

#### AP_Debug
Debug support system.


### HAL Layer

#### AP_HAL

Hardware abstraction layer.

Responsibilities:
- UART
- SPI
- I2C
- GPIO
- Timer
- PWM
- Storage


### Sensor Modules

#### AP_IMU
Inertial measurement processing.

#### AP_GPS
GPS position information.

#### AP_Baro
Altitude pressure sensor.

#### AP_Compass
Magnetic heading sensor.

#### AP_Battery
Power monitoring.


### Estimation Modules

#### AP_AHRS
Vehicle attitude calculation.

#### AP_EKF
Sensor fusion and state estimation.

#### AP_InertialNav
Navigation estimation.


### Navigation

#### AP_Nav
Navigation calculations.

#### AP_Mission
Mission command handling.

#### AP_Home
Home position management.


### Control System

#### AP_Control
Main control algorithms.

#### AP_PID
PID controller.

#### AP_PosControl
Position controller.

#### AP_Motors
Motor output handling.

#### AP_Mixer
Output mixing.


### Vehicle Management

#### AP_Mode
Vehicle mode handling.

#### AP_FlightMode
Flight state management.

#### AP_Arming
Safety arming logic.

#### AP_RC
Remote control processing.

#### AP_Input
Input abstraction.

#### AP_Failsafe
Failure protection system.


### Communication

#### GCS_MAVLink
MAVLink communication interface.


### Simulation

#### AP_Sim
Testing and simulation support.


## Development Goal

MiniPilot architecture allows adding:
- New hardware platforms
- New sensors
- New communication interfaces
- New vehicle types

without redesigning the complete system.
