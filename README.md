# Software Defined Vehicle (SDV) Cockpit Safety System using QNX Neutrino RTOS

## Overview

The Software Defined Vehicle (SDV) Cockpit Safety System is a real-time embedded application developed using QNX Neutrino RTOS and Raspberry Pi. The project demonstrates how safety-critical cockpit functions can continue to operate reliably even when non-critical multimedia applications consume significant CPU resources.

The system uses real-time scheduling, CPU isolation, watchdog monitoring, and inter-process communication (IPC) to ensure deterministic execution of critical vehicle functions.

---

## Problem Statement

In modern Software Defined Vehicles (SDVs), infotainment and safety-critical applications often run on the same hardware platform. Heavy CPU utilization or application failures in the infotainment domain can negatively impact critical functions such as brake alerts and instrument cluster updates.

This project addresses this challenge by implementing a mixed-criticality architecture that guarantees uninterrupted operation of safety-critical services.

---

## Features

* Real-time Brake Alert Monitoring
* Instrument Cluster Updates
* Multimedia Load Simulation
* Watchdog-Based Fault Recovery
* QNX Pulse IPC Communication
* CPU Affinity and Resource Isolation
* Mixed-Criticality Scheduling
* Deterministic System Execution

---

## Technologies Used

* QNX Neutrino RTOS
* Raspberry Pi
* POSIX Threads
* QNX Pulse IPC
* Real-Time Scheduling (SCHED_FIFO)
* CPU Affinity

---

## System Architecture

### Safety-Critical Modules

* Brake Module
* Instrument Cluster Module
* Watchdog Monitoring Service

### Non-Critical Modules

* Multimedia Module

### Common Components

* IPC Communication
* CPU Management
* GPIO Control
* Priority Configuration

---

## Project Structure

```text
software-defined-vehicle-cockpit-safety/

├── brake/
├── cluster/
├── common/
├── media/
├── watchdog/
├── Makefile
└── README.md
```

## Real-Time Scheduling

| Module             | Scheduling Policy | Priority     |
| ------------------ | ----------------- | ------------ |
| Brake Alert        | SCHED_FIFO        | 63           |
| Instrument Cluster | SCHED_FIFO        | 60           |
| Watchdog           | SCHED_FIFO        | 58           |
| Media Player       | SCHED_OTHER       | Low Priority |

---

## Key Objectives

* Ensure deterministic execution of safety-critical tasks.
* Prevent CPU starvation caused by multimedia workloads.
* Demonstrate fault isolation using QNX microkernel architecture.
* Achieve reliable watchdog-based recovery.
* Maintain real-time responsiveness under stress conditions.

---

## Results

* Continuous brake alert operation during CPU overload.
* Stable instrument cluster updates.
* Reliable watchdog monitoring and recovery.
* Deterministic execution of critical services.
* Successful mixed-criticality task management.

---

## Skills Demonstrated

* Real-Time Operating Systems (RTOS)
* Embedded C Programming
* Inter-Process Communication (IPC)
* Priority-Based Scheduling
* CPU Isolation and Affinity
* Watchdog Recovery Mechanisms
* Software Architecture Design
* Safety-Critical System Development

  ---

## Future Scope

* Integration with ADAS systems.
* AUTOSAR compatibility.
* AI-based sensor processing.
* Automotive ECU deployment.
* Enhanced cockpit visualization.

---

## Author

**Bhargavi Kanakapudi**

B.Tech Student | Embedded Systems and Software Development Enthusiast

GitHub: [@BhargaviKanakapudi](https://github.com/BhargaviKanakapudi)

LinkedIn: [Bhargavi Kanakapudi](https://www.linkedin.com/in/bhargavikanakapudi)
