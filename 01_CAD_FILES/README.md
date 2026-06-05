# 01_CAD_FILES — Seedball Dispenser Module

CAD files for the Kriti26 drone-deployed seedball dispensing mechanism, designed in **Autodesk Fusion 360**. The assembly consists of five sub-components, each exported in three formats alongside a full assembly archive.

---

## File Structure

```
01_CAD_FILES/
├── 00_FULL-ASSEMBLY.f3z
├── 01_HOPPER.f3d / .step / .stl
├── 02_HOPPER_WITH-SERVO-MOUNTS.f3d / .step / .stl
├── 03_STORAGE.f3d / .step / .stl
├── 04_V-FILE.f3d / .step / .stl
└── 05_CONNECTION.f3d / .step / .stl
```

---

## Components

**00 — Full Assembly** (`00_FULL-ASSEMBLY.f3z`)
Complete assembly with all five sub-components, joints, and constraints. Single source of truth for the full mechanism.

**01 — Hopper** (`01_HOPPER`)
Base hopper body that receives seedballs from the Storage Module and funnels them into the dual V-file channel via angled internal walls. The Hopper with Servo Mounts (02) is the production-ready iteration of this same part.

**02 — Hopper with Servo Mounts** (`02_HOPPER_WITH-SERVO-MOUNTS`)
Production-ready version of the Hopper with integrated mounting bosses for Servo A and Servo B. Same core geometry as `01_HOPPER` with servo mounting detail added. **This is the version used in the final assembly.**

**03 — Storage Module** (`03_STORAGE`)
Top-level seedball reservoir that sits above the hopper and feeds balls downward under gravity through a tapered internal floor.

**04 — V-File Channel** (`04_V-FILE`)
Dual V-shaped singulation channel that guides seedballs to the exit point. Each trough corresponds to one servo gate (File A / File B). Manufactured from 2 mm aluminium sheet via bending and welded to the hopper.

**05 — Connection Bracket** (`05_CONNECTION`)
Structural bracket that attaches the dispenser module to the drone's payload frame and acts as the bottom closure of the V-File assembly.

---

## File Formats

| Format | Extension | Use Case |
|--------|-----------|----------|
| Fusion 360 Native | `.f3d` | Design modifications — retains full parametric history |
| Fusion 360 Archive | `.f3z` | Full assembly with all components and history in one file |
| STEP (AP214) | `.step` | Import into any CAD tool — SolidWorks, FreeCAD, Onshape, CATIA |
| STL (Binary) | `.stl` | Simulation, slicing, mesh inspection, or rendering |

---

## Material & Fabrication

All structural components are designed for **Cold Chamber Die Casting** using **Aluminium Alloy 4xx.x Series**, except the V-File Channel which is fabricated via **sheet metal bending** and welded to the hopper. Total assembly mass: **2.85 kg**.

---

## CAD Tool

**Autodesk Fusion 360** — All `.f3d` and `.f3z` files require Fusion 360 to open natively. For cross-platform use, import the `.step` files into your preferred CAD environment.
