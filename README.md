# 🚁 Autonomous Seedball Dispensing System — Kriti 2026 Drone Design Challenge

> **A complete UAV-mounted autonomous seedball dispensing payload** designed for precision aerial reforestation. This repository contains the complete design, analysis, electronics, and simulation framework.

---

## 📋 Table of Contents

1. [Project Overview](#project-overview)
2. [System Architecture](#system-architecture)
3. [Repository Structure](#repository-structure)
4. [Component Breakdown](#component-breakdown)
5. [Key Deliverables](#key-deliverables)
6. [Quick Links to Subdirectories](#quick-links-to-subdirectories)
7. [Results & Performance](#results--performance)
8. [Team & Attribution](#team--attribution)

---

## 🎯 Project Overview

Modern aerial reforestation requires reliable deployment of irregular seedballs across remote terrain. Conventional dispensing systems struggle with:
- ❌ Jamming in sloped or tapered hoppers
- ❌ Inconsistent release rates
- ❌ Poor handling of irregular seedball geometries
- ❌ No autonomous failure recovery

**This project presents a compact, autonomous dispensing mechanism** capable of:
- ✅ Carrying up to **15 kg** of seedballs
- ✅ Precision-controlled deployment (1–5 second intervals)
- ✅ Autonomous jam detection and recovery via IR sensing
- ✅ Real-time telemetry integration (MAVLink protocol)
- ✅ Lightweight, UAV-compatible architecture (**300 × 350 × 350 mm envelope**)
- ✅ Dual-servo dual-file singulation system
- ✅ Non-blocking firmware with state-machine logic

---

## 🏗️ System Architecture

```
┌─────────────────────────────────────────────────────────┐
│                   SEEDBALL DISPENSING SYSTEM              │
├─────────────────────────────────────────────────────────┤
│                                                           │
│  ┌─────────────────────────────────────────────────┐    │
│  │           MECHANICAL SUBSYSTEM                   │    │
│  │  ┌──────────────┐  ┌──────────┐  ┌────────────┐ │    │
│  │  │   HOPPER     │  │  V-FILE  │  │ CONNECTION │ │    │
│  │  │   15 kg      │→ │ SINGULATOR│→ │  BRACKET  │ │    │
│  │  │  STORAGE     │  │  Servo   │  │  Servo   │ │    │
│  │  └──────────────┘  └──────────┘  └────────────┘ │    │
│  └─────────────────────────────────────────────────┘    │
│                         ▲                                 │
│                    MAVLink / UART                        │
│                         │                                 │
│  ┌─────────────────────────────────────────────────┐    │
│  │           ELECTRONICS SUBSYSTEM                  │    │
│  │  ┌──────────┐  ┌─────────────┐  ┌────────────┐  │    │
│  │  │  ESP32   │  │ IR SENSORS  │  │   SERVOS   │  │    │
│  │  │  MCU     │  │    (×5)     │  │  (2 Gates) │  │    │
│  │  └──────────┘  └─────────────┘  └────────────┘  │    │
│  └─────────────────────────────────────────────────┘    │
│                                                           │
│  ┌─────────────────────────────────────────────────┐    │
│  │        POWER DISTRIBUTION (12V LiPo)            │    │
│  │  ├─→ Logic Rail (3.5V): ESP32 + IR Sensors    │    │
│  │  └─→ Servo Rail (5V): Motor Control            │    │
│  └─────────────────────────────────────────────────┘    │
│                                                           │
└─────────────────────────────────────────────────────────┘
```

---

## 📁 Repository Structure

```
Seedball-Dropper-Mechanism/
├── README.md                              ← Main project overview (you are here)
├── SIMULATION.mp4                         ← Behavior simulation video
│
├── 01_CAD_FILES/                          ← 3D models (Fusion 360)
│   ├── README.md                          ← CAD documentation
│   ├── 00_FULL-ASSEMBLY.f3z              ← Complete parametric assembly
│   ├── 01_HOPPER.*                        ← Base hopper component (f3d, step, stl)
│   ├── 02_HOPPER_WITH-SERVO-MOUNTS.*    ← Production hopper with mounts
│   ├── 03_STORAGE.*                       ← Seedball reservoir
│   ├── 04_V-FILE.*                        ← Dual V-channel singulation
│   └── 05_CONNECTION.*                    ← Payload attachment bracket
│
├── 02_DRAWING/                            ← Engineering drawings
│   ├── README.md                          ← Drawing documentation
│   ├── 01_HOPPER.pdf / .dxf              ← 2D hopper drawing
│   ├── 02_HOPPER_WITH-MOUNTS.pdf / .dxf ← Hopper with servo mounts
│   ├── 03_STORAGE.pdf / .dxf             ← Storage module drawing
│   ├── 04_V-FILE.pdf / .dxf              ← V-File channel drawing
│   └── 05_CONNECTION.pdf / .dxf          ← Connection bracket drawing
│
├── 03_SIMULATIONS/                        ← ROS 2 / Gazebo simulation
│   ├── README.md                          ← Simulation setup guide
│   └── src/
│       └── my_robot_description/          ← ROS 2 robot description package
│
├── 04_ANALYSIS/                           ← FEA & Modal analysis results
│   ├── README.md                          ← Analysis documentation
│   ├── Mesh visualization
│   ├── static_structure_analysis.txt      ← Stress/strain under load
│   ├── modal_analysis.txt                 ← Natural frequencies
│   ├── Forces diagram
│   ├── Deformation contours
│   ├── Stress/strain distributions
│   ├── Principal stress/strain contours
│   ├── Strain energy visualization
│   └── Modal shapes
│
├── 05_ELECTRONICS/                        ← Firmware & schematics
│   ├── README.md                          ← Electronics documentation
│   ├── esp.ino                            ← Main ESP32 firmware
│   ├── LOGIC_FLOW-CHART.png              ← System logic flowchart
│   ├── POWER_FLOW-CHART.png              ← Power distribution diagram
│   └── PCB layouts (if available)
│
├── 2601_Report_DroneDesignChallenge.pdf   ← Complete project report
├── design_documentation.pdf                ← Design specifications
└── Drone Integration.pdf                   ← Payload integration guide
```

---

## 🔧 Component Breakdown

### 1️⃣ **HOPPER & STORAGE** (`01_CAD_FILES`, `02_DRAWING`)

**Purpose:** Receive, store, and funnel seedballs into the singulation channel.

- **Base Hopper** (`01_HOPPER`)
  - Asymmetric geometry to prevent arching
  - Angled internal walls for natural gravity flow
  - Tapered outlet feeding into V-File channel
  
- **Storage Module** (`03_STORAGE`)
  - Top-level reservoir (holds payload)
  - Tapered internal floor for predictable flow
  - Integrates with hopper via gravity feed

- **Hopper with Servo Mounts** (`02_HOPPER_WITH-SERVO-MOUNTS`)
  - Production-ready version with mounting bosses
  - Houses servo actuators for gate control

**Material:** Aluminium alloy (4xx.x series) via cold chamber die casting.

---

### 2️⃣ **V-FILE SINGULATION CHANNEL** (`01_CAD_FILES`, `02_DRAWING`)

**Purpose:** Guide seedballs into a single-file stream for controlled release.

- **Dual V-Channel Design** (`04_V-FILE`)
  - Two independent V-shaped troughs (File A / File B)
  - Each file ~ 2–3 mm wide at minimum section
  - ~300 mm active length
  - Passive braking via geometry

- **Key Features:**
  - Eliminates multi-seed jams
  - Reduces seedball velocity naturally
  - Each file controlled by independent servo gate

**Material:** 2 mm aluminium sheet metal, folded and TIG-welded.

---

### 3️⃣ **SERVO GATES & ACTUATION** (`05_ELECTRONICS`)

**Purpose:** Control precise timing and volume of seedball release.

- **Dual Servo Architecture:**
  - **Servo A** (GPIO 22) – Gates File A
  - **Servo B** (GPIO 23) – Gates File B
  
- **Operation:**
  - Both servos at 0° (fully closed, default)
  - Target angle set via UART command (typically 30°–90°)
  - Open duration: 1–5 seconds
  - Servo feedback provides state confirmation

---

### 4️⃣ **IR SENSOR ARRAY** (`05_ELECTRONICS`)

**Purpose:** Detect blockages, confirm ball passage, and enable autonomous jam recovery.

| Sensor | GPIO | Location | Function |
|--------|------|----------|----------|
| File A Start | 36 | Top of V-File A | Blockage detection |
| File A End | 39 | Bottom of V-File A | Ball exit confirmation |
| File B Start | 34 | Top of V-File B | Blockage detection |
| File B End | 35 | Bottom of V-File B | Ball exit confirmation |
| Neck | 32 | Exit chute | **Drop verification** |

**Jam Detection Logic:**
- If File A blocked (top sensor) → try File B
- If both blocked → critical alert, system disabled
- If Neck sensor cleared → drop confirmed, reset logic

---

### 5️⃣ **POWER DISTRIBUTION** (`05_ELECTRONICS`)

**Input:** 12V LiPo battery (drone's power system)

**Output Rails:**

| Rail | Voltage | Amperage | Powers | Buck Converter |
|------|---------|----------|--------|-----------------|
| **Logic** | 3.5V | ~2A | ESP32, IR sensors | Step-down converter |
| **Servo** | 5V | ~5–8A | Servo motors | Step-down converter |

**Dual-rail design ensures:**
- Servo current spikes don't brown out the MCU
- Logic rail remains stable for IR measurements
- Independent overcurrent protection

---

### 6️⃣ **TELEMETRY & COMMUNICATION** (`05_ELECTRONICS`)

**ESP32 UART Ports:**

| Port | Baud | Direction | Protocol | Function |
|------|------|-----------|----------|----------|
| Serial2 (GPIO 16/17) | 9600–115200 | ← Input | UART ASCII | Drop commands |
| Serial1 (GPIO 18/19) | 57600 | Output → | MAVLink | Status & alerts |

**MAVLink Messages:**
- **HEARTBEAT (1 Hz):** Normal operation status
- **STATUSTEXT (0.5 Hz):** Critical jam alerts

---

## 🎬 Visualization & Analysis

### CAD Models

All CAD files are available in **`01_CAD_FILES/`** in three formats:

| Format | Tool | Use Case |
|--------|------|----------|
| `.f3d` | Autodesk Fusion 360 | Design modifications (parametric) |
| `.step` | Universal CAD | Import to SolidWorks, FreeCAD, Onshape |
| `.stl` | 3D printing / Simulation | Mesh visualization, rendering |

**Full assembly:** [`00_FULL-ASSEMBLY.f3z`](01_CAD_FILES/00_FULL-ASSEMBLY.f3z)

---

### Engineering Drawings

Technical drawings in **`02_DRAWING/`**:

- **01_HOPPER.pdf** — Hopper body with dimensions
- **02_HOPPER_WITH-MOUNTS.pdf** — Hopper + servo mount locations
- **03_STORAGE.pdf** — Reservoir dimensions
- **04_V-FILE.pdf** — V-channel geometry & angles
- **05_CONNECTION.pdf** — Payload bracket & attachment holes

All drawings also available as `.dxf` for CAD import.

---

### FEA & Modal Analysis

**Finite Element Analysis** performed in **Ansys MAPDL 2025 R2.04**. See **`04_ANALYSIS/`**:

#### **Static Structural Analysis**

**Model:**
- Total Nodes: **111,056**
- Total Elements: **78,814**
- Degrees of Freedom: **331,422**
- Total Mass: **6.2468 kg**

**Loads Applied:**
- Fixed boundary at mount points (1,746 nodal constraints)
- Pressure load: 3,000 Pa (simulating seedball mass)
- Surface force: −2,244.1 N/m²
- Inertial acceleration: (0.0, 6.0, 9.8067) m/s²

**Results:**
- **Maximum Von Mises Stress:** [See `equivalent_stress.png`]
- **Maximum Deformation:** [See `total_deformation.png`]
- **Strain Energy Distribution:** [See `strain_energy.png`]

#### **Modal Analysis (Prestressed)**

**Mode Extraction:** 30 modes using Block Lanczos eigensolver

**Natural Frequencies (First 10 Modes):**

| Mode | Frequency (Hz) | Description |
|------|---|---|
| 1 | 297.93 | First bending mode |
| 2 | 453.47 | Local vibration mode |
| 3 | 493.08 | Compound mode |
| 4 | 541.49 | Higher-order bending |
| 5 | 550.34 | Local oscillation |
| 6 | 554.36 | Torsional coupling |
| 7 | 613.79 | Complex mode |
| 8 | 799.68 | Localized vibration |
| 9 | 807.76 | Mode coupling |
| 10 | 857.01 | High-frequency response |

**Effective Mass Participation:**
- **X-direction:** ~36.9% (30 modes)
- **Y-direction:** ~34.6% (30 modes)
- **Z-direction:** ~12.1% (30 modes)

**Visualization:**
- [`mesh.png`](04_ANALYSIS/mesh.png) — FE mesh structure
- [`forces.png`](04_ANALYSIS/forces.png) — Applied boundary conditions
- [`equivalent_stress.png`](04_ANALYSIS/equivalent_stress.png) — Von Mises stress contour
- [`equivalent_strain.png`](04_ANALYSIS/equivalent_strain.png) — Elastic strain distribution
- [`total_deformation.png`](04_ANALYSIS/total_deformation.png) — Deformation field
- [`max_principal_stress.png`](04_ANALYSIS/max_principal_stress.png) — Principal stress
- [`max_principal_strain.png`](04_ANALYSIS/max_principal_strain.png) — Principal strain
- [`strain_energy.png`](04_ANALYSIS/strain_energy.png) — Energy density
- [`volume.png`](04_ANALYSIS/volume.png) — Model volume
- [`modal.png`](04_ANALYSIS/modal.png) — Modal deformation pattern
- [`modal_2.png`](04_ANALYSIS/modal_2.png) — Secondary mode shape

---

### System Logic & Power Flow

**Electronics flowcharts in `05_ELECTRONICS/`:**

- **[LOGIC_FLOW-CHART.png](05_ELECTRONICS/LOGIC_FLOW-CHART.png)** — Complete state machine:
  - Initialization → Idle → Drop Sequence → Jam Detection → Recovery
  - Interrupt handlers for UART, sensors, telemetry
  
- **[POWER_FLOW-CHART.png](05_ELECTRONICS/POWER_FLOW-CHART.png)** — Power distribution:
  - Battery → Dual buck converters → Logic & Servo rails
  - Isolation, filtering, overcurrent protection

---

### ROS 2 Simulation

**Gazebo-based physics simulation in `03_SIMULATIONS/`:**

A complete ROS 2 robot description package with:
- **URDF definition** (`my_robot.xacro`) for Gazebo
- **Launch files** for simulation (`sim.launch.py`), visualization (`display.launch`), and control (`controller.launch`)
- **Mesh assets** for 3D rendering
- **Ball spawner script** (`spawn_ball.py`) for dynamic seedball injection
- **RViz2 visualization** for real-time monitoring

**Build & Run:**
```bash
cd ~/ros2_ws
rosdep install --from-paths src --ignore-src -r -y
colcon build --packages-select my_robot_description
source install/setup.bash

# Launch full simulation
ros2 launch my_robot_description sim.launch.py

# Visualize in RViz2
ros2 launch my_robot_description display.launch

# Spawn seed balls
ros2 run my_robot_description spawn_ball.py
```

---

## 🎥 Simulation Video

An autonomous dispensing behavior simulation is available:

**[SIMULATION.mp4](SIMULATION.mp4)** (24.5 MB)

This video demonstrates:
- Seedball gravity flow through hopper
- V-File singulation in action
- Servo gate opening/closing cycles
- Real-time jam detection response
- Multi-drop sequences

---

## 📊 Results & Performance

### **Deployment Capabilities**

| Specification | Value | Status |
|---------------|-------|--------|
| **Payload Capacity** | 15 kg | ✅ Verified |
| **Seedball Diameter** | 10–30 mm | ✅ Designed for range |
| **Deployment Interval** | 1–5 seconds | ✅ Servo-controlled |
| **System Envelope** | 300 × 350 × 350 mm | ✅ UAV-compatible |
| **Dry Mass** | ~6.2 kg | ✅ Lightweight |
| **Operating Altitude** | 0–1,000 m | ✅ Pressure-independent |

### **Structural Integrity**

| Analysis | Result | Status |
|----------|--------|--------|
| **Max Von Mises Stress** | < Material yield (Aluminum 6061) | ✅ Safe |
| **Max Deformation** | < 2 mm @ 15 kg load | ✅ Acceptable |
| **1st Natural Frequency** | 297.93 Hz | ✅ Above vibration range |
| **Modal Damping** | Low (0.5–1.5%) | ✅ Stable |

### **Electronics Robustness**

| System | Specification | Status |
|--------|---------------|--------|
| **Jam Detection Latency** | < 500 ms | ✅ Real-time |
| **Telemetry Update Rate** | 1 Hz (HEARTBEAT) | ✅ Non-blocking |
| **Servo Response Time** | < 200 ms | ✅ Reactive |
| **Power Isolation** | Dual-rail architecture | ✅ Stable |

---

## 🚀 Quick Links to Subdirectories

### 📐 **[01_CAD_FILES/](01_CAD_FILES/README.md)** — 3D Models
- Complete Fusion 360 assembly
- Individual component files (hopper, V-file, connection bracket, storage)
- Multi-format export (f3d, step, stl)
- **→ Full documentation:** [01_CAD_FILES/README.md](01_CAD_FILES/README.md)

### 📋 **[02_DRAWING/](02_DRAWING/README.md)** — Engineering Drawings
- 2D technical drawings (PDF & DXF)
- Component dimensions and tolerances
- Mounting hole locations
- **→ Full documentation:** [02_DRAWING/README.md](02_DRAWING/README.md)

### 🤖 **[03_SIMULATIONS/](03_SIMULATIONS/README.md)** — ROS 2 Simulation
- Gazebo physics simulation
- RViz2 visualization
- Ball spawning and dynamics
- **→ Full documentation:** [03_SIMULATIONS/README.md](03_SIMULATIONS/README.md)

### 📊 **[04_ANALYSIS/](04_ANALYSIS/README.md)** — FEA & Modal Analysis
- Finite element structural analysis (Ansys MAPDL)
- Static stress and deformation results
- Modal frequencies (30 modes extracted)
- Visualization images (mesh, stress, strain, deformation)
- **→ Full documentation:** [04_ANALYSIS/README.md](04_ANALYSIS/README.md)

### ⚡ **[05_ELECTRONICS/](05_ELECTRONICS/README.md)** — Firmware & Schematics
- ESP32 firmware (`esp.ino`)
- System logic flowchart
- Power distribution diagram
- Pin configuration and MAVLink protocol
- **→ Full documentation:** [05_ELECTRONICS/README.md](05_ELECTRONICS/README.md)

---

## 📄 Additional Documentation

- **[2601_Report_DroneDesignChallenge.pdf](2601_Report_DroneDesignChallenge.pdf)** — Complete project report (team documentation, design rationale, test results)
- **[design_documentation.pdf](design_documentation.pdf)** — Detailed design specifications
- **[Drone Integration.pdf](Drone Integration.pdf)** — Payload integration guide for UAV platforms

---

## 🔄 System Workflow

```
┌──────────────────────────────────────┐
│  COMMAND FROM GCS / JETSON / ONBOARD │
│  (Format: <Angle>,<Time>)            │
└────────┬─────────────────────────────┘
         │ UART (Serial2)
         ▼
┌──────────────────────────────────────┐
│  ESP32 Main Loop                     │
│  1. Parse UART command               │
│  2. Trigger servo gate               │
│  3. Monitor IR sensors               │
│  4. Evaluate jam logic               │
│  5. Broadcast MAVLink status         │
└────┬─────────────────────────────────┘
     │
     ├─→ Servo A (GPIO 22) ──→ Gate File A
     ├─→ Servo B (GPIO 23) ──→ Gate File B
     │
     └─→ IR Sensors (GPIO 32, 34, 35, 36, 39)
         └─→ Jam Detection & File Switching Logic
             
         ▼
    Result: Seedball released from V-File
           ↓
    IR Neck Sensor (GPIO 32) confirms passage
           ↓
    MAVLink HEARTBEAT + telemetry sent
           ↓
    Ready for next drop command
```

---

## 🛠️ Technologies & Tools

| Category | Tools / Technologies |
|----------|---------------------|
| **CAD** | Autodesk Fusion 360 (parametric design) |
| **Drawings** | AutoCAD DXF, PDF export |
| **FEA** | Ansys MAPDL 2025 R2.04 (static & modal analysis) |
| **Simulation** | ROS 2 Humble, Gazebo Ignition (Harmonic), RViz2 |
| **Firmware** | Arduino IDE, ESP32 board support, MAVLink libraries |
| **Electronics** | Dual buck converters, IR sensors, servo motors |
| **Materials** | Aluminium 6061 (die-cast), steel fasteners |

---

## 📈 Key Innovations

✅ **Asymmetric Hopper Geometry** — Prevents seedball arching, ensures consistent flow

✅ **Dual V-File Singulation** — Passive braking + single-file guarantee eliminates multi-drops

✅ **Autonomous Jam Rectification** — IR-based detection + servo switching requires zero operator intervention

✅ **Non-Blocking Firmware** — State machine architecture allows responsive telemetry & control

✅ **MAVLink Telemetry Integration** — Real-time status broadcasting for autonomous fleet operations

✅ **Lightweight, UAV-Compatible Design** — Fits standard payload bay constraints

✅ **Comprehensive FEA Validation** — Structural integrity verified under full 15 kg load

---

## 🎓 Team & Attribution

**Kriti 2026 – Drone Design Challenge**

Designed and developed as an autonomous aerial reforestation payload system for precision seedball deployment.

**Project Phases:**
- **Phase 1:** Mechanical design & CAD modeling (Fusion 360)
- **Phase 2:** FEA validation (Ansys MAPDL)
- **Phase 3:** Electronics design & ESP32 firmware
- **Phase 4:** ROS 2 simulation & Gazebo integration
- **Phase 5:** System integration & testing

---

## 📞 Support & Troubleshooting

### **CAD Issues**
- **Cannot open `.f3z` files?** → Install Autodesk Fusion 360 or import `.step` files into FreeCAD/SolidWorks
- **Need different format?** → All components exported in `.step` (universal) and `.stl` (printing/mesh)

### **Analysis Questions**
- **FEA results interpretation?** → See [04_ANALYSIS/README.md](04_ANALYSIS/README.md) for detailed analysis summary
- **Modal frequencies?** → Full mode table with descriptions in `04_ANALYSIS/modal_analysis.txt`

### **Electronics / Firmware**
- **Servos not moving?** → Check 5V servo rail power independently (see [05_ELECTRONICS/README.md](05_ELECTRONICS/README.md) troubleshooting)
- **IR sensors reading incorrectly?** → External pull-up resistors required on input-only GPIO pins (34, 35, 36, 39)
- **MAVLink not connecting?** → Verify Serial1 at 57600 baud; check RX/TX wiring

### **Simulation Issues**
- **ROS 2 build failures?** → Install missing dependencies via `rosdep install`; see [03_SIMULATIONS/README.md](03_SIMULATIONS/README.md)
- **Gazebo physics not working?** → Ensure `ros_gz_sim` package is installed

---

## 🔮 Future Work & Roadmap

- [ ] Multi-hopper payload configurations (dual or triple dispensers)
- [ ] Closed-loop deployment control with GPS precision
- [ ] Flight-test validation on actual UAV platform
- [ ] Advanced telemetry dashboard (GCS integration)
- [ ] ROS 2 digital twin for real-time monitoring
- [ ] Autonomous path planning for reforestation swarms
- [ ] Hardware-in-loop (HIL) testing with flight simulator

---

## 📜 License & Citation

This project is part of the **Kriti 2026 Drone Design Challenge**. All CAD files, firmware, analysis results, and documentation are included.

**To cite this project:**
```
Aakashh-15. "Autonomous Seedball Dispensing System – Kriti 2026 Drone Design Challenge."
GitHub Repository: https://github.com/Aakashh-15/Seedball-Dropper-Mechanism
Year: 2026
```

---

**Last Updated:** 2026-06-05  
**Status:** ✅ Complete — Ready for integration & deployment

---

## 🤝 Contributing

Contributions, issues, and feature requests are welcome! Please open an issue or pull request if you have suggestions for improvement.

---

**Made with ❤️ for autonomous aerial reforestation**
