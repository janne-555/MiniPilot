# AP_Sim

Author: JANNE

## Overview
AP_Sim is the simulation support module of MiniPilot.

It provides a testing environment where autopilot logic can be executed without real vehicle hardware.

Simulation helps verify core modules before running on embedded targets.

## Files

AP_Sim.c
- Contains simulation implementation
- Provides simulated system updates
- Connects test environment with MiniPilot modules

AP_Sim.h
- Defines simulation interfaces
- Provides APIs used for testing

## Responsibilities
AP_Sim manages:
- Software based testing
- Simulated sensor inputs
- Runtime verification
- Development support

## Input Data

AP_Sim can receive:

Test Environment:
- Simulated sensor values
- Simulated vehicle state
- External test commands

MiniPilot Modules:
- Control outputs
- System requests

## Output Data

AP_Sim provides:
- Simulated sensor feedback
- Test responses
- Runtime validation data

## Depends On

MiniPilot Core:
- AP_Vehicle
- AP_Scheduler

Communication:
- GCS_MAVLink

## Used By

Development Environment
- Testing without hardware

AP_Vehicle
- Executes autopilot logic in simulation

GCS_MAVLink
- Provides external communication testing

## Data Flow

Simulation Environment
          |
          v
       AP_Sim
          |
          v
    MiniPilot Core
          |
          v
   Control Outputs

## Startup Flow

Program Start
       |
       v
AP_Sim Init
       |
       v
Initialize Test Environment
       |
       v
Run MiniPilot

## Runtime Flow

Simulation Loop
        |
        v
Generate Test Data
        |
        v
Run Autopilot Modules
        |
        v
Verify Outputs

## Usage Concept

Same autopilot code should run on:

Simulation
     |
Linux Test
     |
STM32 Hardware

Only hardware interface layers should change.

## Future Expansion

AP_Sim can support:
- Vehicle physics simulation
- Sensor models
- Failure testing
- Automated tests
- External simulator connection

## Design Goal

AP_Sim allows MiniPilot development and testing without depending on physical hardware.

Core autopilot behavior remains the same between simulation and real targets.
