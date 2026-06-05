# Ansys FEA Analysis – Hopper Structural Study

## Project Overview

This project contains the results of a **Finite Element Analysis (FEA)** performed on a hopper component using **Ansys Mechanical Enterprise Academic Student (MAPDL 2025 R2.04)**. Two analysis types were conducted:

1. **Static Structural Analysis** – to evaluate stress, strain, and deformation under applied loads
2. **Prestressed Modal Analysis** – to extract natural frequencies and mode shapes under the same loading conditions

The analyses were run on **February 15, 2026** using a distributed parallel solver across 4 CPU cores.

---

## File Contents

| File | Description |
|------|-------------|
| `static_structure_analysis.txt` | Full MAPDL solver output for the static structural analysis |
| `modal_analysis.txt` | Full MAPDL solver output for the prestressed modal analysis |
| `mesh.png` | FE mesh visualization |
| `forces.png` | Applied forces and boundary conditions |
| `total_deformation.png` | Total deformation result contour |
| `equivalent_stress.png` | Von Mises (equivalent) stress distribution |
| `equivalent_strain.png` | Equivalent elastic strain distribution |
| `max_principal_stress.png` | Maximum principal stress contour |
| `max_principal_strain.png` | Maximum principal strain contour |
| `strain_energy.png` | Strain energy density distribution |
| `volume.png` | Model volume visualization |
| `modal.png` | Modal analysis result (mode shapes) |
| `modal_2.png` | Additional modal result visualization |

---

## Model Details

| Parameter | Value |
|-----------|-------|
| Total Nodes | 111,056 |
| Total Elements | 78,814 |
| Solid Elements (SOLID187) | 56,558 |
| Surface Effect Elements (SURF154) | 22,256 (pressure face) + 17,548 (force face) |
| Degrees of Freedom | 331,422 |
| Total Mass | 6.2468 kg |
| Center of Mass (X, Y, Z) | ≈ (0.000, −0.177, 0.159) m |

---

## Boundary Conditions & Loads

- **Fixed Supports:** Applied at selected nodes (1,746 nodal constraints)
- **Pressure Load:** 3,000 Pa applied to one surface region
- **Surface Force:** −2,244.1 N/m² applied to another surface region
- **Inertial Load (Acceleration):** `ACEL = (0.0, 6.0, 9.8067)` m/s² in X, Y, Z directions
- **Units:** MKS (meters, kilograms, seconds, Newtons, Pascals)

---

## Static Structural Analysis Summary

- **Analysis Type:** Linear Static (Steady-State)
- **Solver:** Distributed Sparse Matrix (in-core mode, symmetric)
- **Solver Rate:** ~33.4 GFlops
- **Total Solve Time:** ~42 seconds elapsed (24 s solver time)
- **Memory Used:** ~2,345 MB across 4 MPI processes
- **Result:** Converged with **0 errors** and **2 warnings**
  - Warning: element shape checking inactive
  - Warning: material number 2 has no MP/TB command

---

## Modal Analysis Summary

- **Analysis Type:** Prestressed Modal (Linear Perturbation from Static result)
- **Eigensolver:** Block Lanczos
- **Number of Modes Extracted:** 30
- **Solver Rate:** ~45.9 GFlops
- **Total Solve Time:** ~53 seconds elapsed
- **Result:** All 30 modes converged with **0 errors** and **3 warnings**

### Natural Frequencies (First 10 Modes)

| Mode | Frequency (Hz) |
|------|---------------|
| 1 | 297.93 |
| 2 | 453.47 |
| 3 | 493.08 |
| 4 | 541.49 |
| 5 | 550.34 |
| 6 | 554.36 |
| 7 | 613.79 |
| 8 | 799.68 |
| 9 | 807.76 |
| 10 | 857.01 |

> Full frequency list up to Mode 30 (1,558.60 Hz) is available in `modal_analysis.txt`.

### Modal Effective Mass Summary (Top Contributors)

| Direction | Cumulative Effective Mass Ratio (30 modes) |
|-----------|------------------------------------------|
| X | ~36.9% |
| Y | ~34.6% |
| Z | ~12.1% |

---

## Hardware & Software Environment

| Item | Details |
|------|---------|
| Software | Ansys MAPDL 2025 R2.04 (Academic Student) |
| OS | Windows 11 (Build 26100) |
| Processor | Intel Core i7-14650HX |
| Physical Cores Available | 16 (24 logical) |
| Cores Used | 4 (Distributed Memory Parallel, MPI) |
| MPI | Intel MPI Library 2021.14 |
| RAM (Physical) | 16 GB |

---

## Notes

- The modal analysis is **prestressed** — it uses the stiffness state from the static structural solution (load step 1, substep 1) as its base, capturing the effect of preload on natural frequencies.
- Mode shapes are **mass-normalized**.
- Stress stiffening is enabled in the modal perturbation step.
- Paths in the solver logs reference the original workstation; replace `<your_name>` with the actual username if re-running.
