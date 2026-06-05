# 🚁 Drone Design Challenge – Autonomous Seedball Dispensing System

> UAV-mounted autonomous seedball dispensing payload designed for precision aerial reforestation.

---

## Demo

### 🎥 Simulation Video

Place `SIMULATION.mp4` in the repository root and uncomment the block below.

```html
<video src="SIMULATION.mp4" controls width="900"></video>
```

---

## Project Overview

Modern aerial reforestation requires reliable deployment of irregular seedballs across remote terrain. Conventional dispensing systems struggle with jamming, inconsistent release rates, and poor handling of non-uniform payloads.

This project presents a compact autonomous dispensing mechanism capable of:

- Carrying up to **15 kg** of seedballs
- Precision-controlled deployment
- Autonomous jam detection and recovery
- Real-time telemetry integration
- UAV-compatible lightweight architecture

---

## System Architecture

```text
                    ┌──────────────────┐
                    │ Flight Controller│
                    └────────┬─────────┘
                             │ MAVLink
                             │
                    ┌────────▼─────────┐
                    │      ESP32       │
                    └───┬─────────┬────┘
                        │         │
                     UART       PWM
                        │         │
              ┌─────────▼─┐   ┌──▼──┐
              │ IR Sensors│   │Servo│
              └───────────┘   └──┬──┘
                                 │
                                 ▼
                       Seedball Dispensing
```

---

## Mechanical Design

### Hopper Architecture

- Custom asymmetric hopper geometry
- Slot-outlet flow architecture
- Optimized for irregular seedballs
- Compact drone-compatible packaging

### V-File Singulation Mechanism

- Aligns seedballs into a single-file stream
- Provides passive velocity reduction
- Eliminates multi-seed release events
- Improves dispensing consistency

### Active Anti-Jamming

- IR-based blockage detection
- Autonomous servo-actuated recovery
- Low-frequency shock rectification
- No operator intervention required

---

## Electronics Architecture

### Controller
- ESP32

### Sensors
- Multi-node IR sensing array

### Communication
- UART
- MAVLink telemetry

### Actuation
- Dual servo dispensing gates
- PWM control

### Power System
- Dual-rail buck converter architecture
- Isolated logic and actuator rails

---

## Software Stack

### Embedded Firmware

- Non-blocking state machine
- Autonomous dispensing logic
- Jam recovery routines
- Telemetry broadcasting

### Simulation Framework

- Dynamic payload generation
- Flow diagnostics
- Jam prediction analysis
- Physics-based validation

---

## Engineering Analysis

### Structural Validation

- Static FEA
- Equivalent stress analysis
- Principal stress evaluation
- Deformation analysis

### Dynamic Validation

- Modal analysis
- Flow kinematics
- Servo dynamics
- V-file braking analysis

---

## Key Innovations

✅ Asymmetric hopper geometry

✅ Slot-outlet anti-arching mechanism

✅ Dual V-file seed singulation

✅ Autonomous jam rectification

✅ ESP32-based intelligent control

✅ MAVLink telemetry integration

---

## Repository Structure

```text
.
├── CAD/
├── Electronics/
├── Firmware/
├── Simulation/
├── Analysis/
├── Documentation/
├── SIMULATION.mp4
└── README.md
```

---

## Results

| Metric | Value |
|----------|----------|
| Payload Capacity | 15 kg |
| Deployment Interval | 1–5 s |
| UAV Envelope | 300 × 350 × 350 mm |
| Controller | ESP32 |
| Telemetry | MAVLink |
| Jam Detection | IR-Based |

---

## Future Work

- Closed-loop deployment control
- Multi-payload dispensing modes
- Flight-test validation
- Advanced telemetry dashboard
- ROS 2 digital twin integration

---

## Team

Kriti 2026 – Drone Design Challenge

Designed and developed as an autonomous aerial reforestation payload system.
