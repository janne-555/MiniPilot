# MiniPilot Sensor To Control Flow

Author: JANNE

## Overview
This document explains how sensor information moves through MiniPilot and finally becomes vehicle control output.

This is the main autopilot processing pipeline.

The flow starts from physical sensors and ends at actuator commands.

## Complete Flow

Physical World
      |
      v
Sensor Hardware
      |
      v
AP_HAL
      |
      v
Sensor Modules
      |
      v
State Estimation
      |
      v
Navigation / Control
      |
      v
Motor Output


## Sensor Layer

Sensor modules collect information about the vehicle.

Modules:

AP_IMU
- Acceleration
- Angular velocity

AP_GPS
- Position
- Velocity

AP_Baro
- Altitude information

AP_Compass
- Heading reference


Flow:

Hardware Sensor
        |
        v
     AP_HAL
        |
        v
 Sensor Module


## Attitude Estimation Flow

Raw sensor data is processed into vehicle orientation.

Flow:

AP_IMU
   |
   +------+
          |
          v
       AP_AHRS
          |
          v
Roll / Pitch / Yaw


AP_AHRS provides attitude information required for stabilization.


## State Estimation Flow

Multiple sensor sources are combined.

Flow:

AP_IMU
AP_GPS
AP_Baro
AP_Compass

    |
    v

 AP_EKF

    |
    v

Vehicle State


EKF output:
- Position
- Velocity
- Attitude state
- Navigation information


## Navigation Flow

Estimated vehicle state is used for movement decisions.

Flow:

AP_EKF
   |
   v
AP_InertialNav
   |
   v
AP_Nav
   |
   v
AP_PosControl


Navigation decides where the vehicle needs to move.


## Control Flow

Control modules calculate required corrections.

Flow:

Target Command

       |

       v

AP_Control

       ^

       |

Current State From AHRS/EKF


       |

       v

Control Output


## PID Processing

Controller compares:

Desired State
       |
       v
    AP_PID
       ^
       |
Current State

       |
       v

Correction Output


## Motor Output Flow

Controller output is converted into hardware commands.

Flow:

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


## Full Runtime Chain

AP_IMU
  |
  v
AP_AHRS
  |
  v
AP_EKF
  |
  v
AP_InertialNav
  |
  v
AP_Nav
  |
  v
AP_PosControl
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


## Data Direction Rule

Sensor data moves upward:

Hardware -> Estimation -> Decision


Commands move downward:

Decision -> Control -> Hardware


## Future Expansion

This pipeline can support:
- Additional sensors
- Advanced estimation
- New controllers
- Different vehicle types
- Different output systems

## Design Goal

Each layer performs only one responsibility.

Sensor modules collect data.

Estimation modules calculate vehicle state.

Control modules calculate corrections.

Output modules control hardware.
