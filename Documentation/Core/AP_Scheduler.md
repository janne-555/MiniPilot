# AP_Scheduler

Author: JANNE

## Overview
AP_Scheduler is the execution management system of MiniPilot.

It controls when autopilot modules run and maintains the correct execution sequence.

Instead of modules running independently, AP_Scheduler provides a controlled periodic update system.

## Files

AP_Scheduler.c
- Contains scheduler implementation
- Executes registered system tasks
- Controls module update timing

AP_Scheduler.h
- Defines scheduler APIs
- Provides scheduler interface to other modules

## Responsibilities
AP_Scheduler manages:
- Main autopilot loop execution
- Periodic task handling
- Module update order
- Timing control
- CPU load organization

## Input Data

AP_Scheduler receives:
- System time from AP_HAL
- Task execution requests
- Module update functions

Examples:
- IMU update task
- Control update task
- MAVLink update task

## Output Data

AP_Scheduler provides:
- Controlled task execution
- Fixed timing updates
- Ordered module processing

## Depends On

AP_HAL
- Provides timing functions
- Provides system tick information

## Used By

AP_Vehicle
- Runs vehicle update process

AP_IMU
- Scheduled sensor updates

AP_AHRS
- Scheduled attitude calculation

AP_EKF
- Scheduled state estimation

AP_Control
- Scheduled controller execution

AP_Motors
- Scheduled output updates

GCS_MAVLink
- Scheduled communication handling

AP_Logger
- Scheduled log processing

## Data Flow

System Timer
     |
     v
  AP_HAL
     |
     v
AP_Scheduler
     |
+----+----------+----------+
|               |          |
Sensors     Controllers   Communication


## Startup Flow

System Start
      |
      v
AP_HAL Init
      |
      v
AP_Scheduler Init
      |
      v
Register Tasks
      |
      v
Start Main Loop

## Runtime Flow

while running

      |
      v

AP_Scheduler Update

      |
      +-- AP_IMU Update
      |
      +-- AP_AHRS Update
      |
      +-- AP_EKF Update
      |
      +-- AP_Control Update
      |
      +-- GCS_MAVLink Update


## Task Frequency Concept

Fast Tasks:
- IMU reading
- Attitude estimation
- Control loop

Medium Tasks:
- GPS processing
- Mission handling
- Communication

Slow Tasks:
- Logging
- Parameter updates
- Health monitoring

## Future Expansion

AP_Scheduler can support:
- Dynamic task registration
- Priority based scheduling
- CPU load monitoring
- RTOS task mapping

## Design Goal

AP_Scheduler keeps MiniPilot execution predictable.

Modules handle their own logic while scheduler controls when they execute.
