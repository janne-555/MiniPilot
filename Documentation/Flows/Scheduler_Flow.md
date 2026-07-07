# MiniPilot Scheduler Flow

Author: JANNE

## Overview
AP_Scheduler controls the runtime execution of MiniPilot.

After system initialization is completed, the scheduler becomes responsible for running all autopilot modules in a controlled order.

The scheduler ensures sensors, estimation, control and communication systems execute at the required time.

## Scheduler Position

MiniPilot Runtime

        |
        v

  AP_Scheduler

        |
+-------+-------+-------+
|       |       |       |
Sensors Control MAVLink


## Why Scheduler Required

Autopilot systems contain many tasks.

Examples:
- IMU requires fast updates
- Control loop requires stable timing
- GPS updates slower
- Communication runs periodically
- Logging runs in background

Scheduler manages these tasks without each module creating its own loop.

## Main Runtime Flow

System Startup
       |
       v
Initialization Complete
       |
       v
AP_Scheduler Start
       |
       v
Main Loop Running


## Main Loop Concept

while running:

    AP_Scheduler Update

            |
            +-- Execute Sensor Tasks

            +-- Execute Estimation Tasks

            +-- Execute Control Tasks

            +-- Execute Communication Tasks


## Fast Loop Tasks

Fast loop contains time critical operations.

Flow:

AP_Scheduler
      |
      v
AP_IMU Update
      |
      v
AP_AHRS Update
      |
      v
AP_EKF Update
      |
      v
AP_Control Update
      |
      v
AP_Motors Update


Purpose:
- Read motion sensors
- Estimate attitude
- Calculate control
- Update outputs


## Medium Loop Tasks

Medium speed tasks:

AP_Scheduler
      |
      +-- AP_GPS Update
      |
      +-- AP_Mission Update
      |
      +-- GCS_MAVLink Update


Purpose:
- Position updates
- Mission processing
- Communication


## Slow Loop Tasks

Slow background tasks:

AP_Scheduler
      |
      +-- AP_Battery Check
      |
      +-- AP_Logger Update
      |
      +-- Health Monitoring


Purpose:
- System monitoring
- Logging
- Safety checks


## Data Execution Order

Sensors First:

Sensors
   |
   v
Estimation
   |
   v
Navigation
   |
   v
Control
   |
   v
Output


Correct order is important because every layer depends on updated data from previous layers.


## Module Relationship

AP_Scheduler calls modules.

Modules should not control scheduler.

Example:

Correct:

Scheduler
    |
    v
 AP_IMU


Wrong:

AP_IMU
  |
  v
Scheduler


## Timing Source

Timing information comes through AP_HAL.

Flow:

Hardware Timer
       |
       v
    AP_HAL
       |
       v
AP_Scheduler


This keeps timing independent from hardware platforms.


## Future Expansion

AP_Scheduler can support:
- Task priority
- Dynamic task registration
- RTOS integration
- CPU usage monitoring
- Performance statistics

## Design Goal

AP_Scheduler provides predictable execution timing.

Each MiniPilot module focuses on its own work while scheduler controls when it runs.
