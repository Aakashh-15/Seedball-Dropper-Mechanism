# Drone Design Challenge – Autonomous Seedball Dispensing System

## Overview

An autonomous UAV-mounted seedball dispensing mechanism developed for Kriti 2026. The system is designed for aerial reforestation missions and can reliably dispense irregular seedballs while detecting and rectifying jams autonomously.

### Key Features
- Supports up to **15 kg** payload of non-uniform seedballs
- ESP32-based autonomous control architecture
- IR-sensor-based jam detection and seedball counting
- Dual V-File singulation mechanism
- Servo-actuated precision dispensing
- MAVLink telemetry integration
- UAV-compatible lightweight modular design

---

## Simulation Video

Place `SIMULATION.mp4` in the repository root.

```md
https://github.com/user-attachments/assets/VIDEO_PLACEHOLDER
```

Or embed directly:

```html
<video src="SIMULATION.mp4" controls width="800"></video>
```

---

## System Architecture

### Mechanical System
- Asymmetric hopper geometry optimized for mass flow
- Dual V-File alignment and singulation mechanism
- Servo-controlled dispensing gates
- Active anti-jamming mechanism

### Electronics System
- ESP32 microcontroller
- Dual-rail power architecture
- UART communication
- PWM servo control
- MAVLink telemetry

### Software System
- Non-blocking state machine
- Autonomous dispensing logic
- Jam detection and recovery
- Telemetry broadcasting
- Simulation framework

---

## Design Highlights

### Hopper Design
- Iterative evolution from pyramidal and conical geometries
- Cubic-spline-inspired flow optimization
- Slot outlet architecture for reduced arching and jamming

### V-File Mechanism
- Single-file seedball alignment
- Passive velocity reduction
- Improved dispensing consistency

### Autonomous Jam Recovery
- IR-based obstruction detection
- Servo-driven shake sequence
- Low-frequency rectification without IMU interference

---

## Technologies Used

- ESP32
- Arduino Framework
- MAVLink
- UART Communication
- PWM Servo Control
- CAD Modelling
- FEA Analysis
- UAV Payload Integration

---

## Repository Structure

```text
.
├── CAD/
├── Electronics/
├── Firmware/
├── Simulation/
├── Documentation/
├── SIMULATION.mp4
└── README.md
```

## Authors

Kriti 2026 Drone Design Challenge Team
