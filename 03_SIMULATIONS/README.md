# Kriti26 — `my_robot_description`

A ROS 2 robot description package for simulating a robotic mechanism in **Gazebo (Ignition/Harmonic)** with support for RViz2 visualization.

---

## Repository Structure

```
src/
└── my_robot_description/
        ├── CMakeLists.txt
        ├── package.xml
        ├── LICENSE
        ├── launch/
        │   ├── sim.launch.py
        │   ├── display.launch
        │   ├── gazebo.launch
        │   ├── controller.launch
        │   ├── controller.yaml
        │   └── urdf.rviz
        ├── meshes/
        │   └── base_link.stl
        ├── scripts/
        │   └── spawn_ball.py
        └── urdf/
            ├── my_robot.xacro
            ├── my_robot.trans
            ├── my_robot.gazebo
            └── materials.xacro
```

---

## Key Files

- **`sim.launch.py`** — Main entry point. Launches Gazebo and spawns the robot into the simulation.
- **`display.launch`** — Launches RViz2 for visualizing the robot model.
- **`my_robot.xacro`** — The robot's primary URDF description file.
- **`spawn_ball.py`** — Spawns seed balls into the running Gazebo simulation.
- **`base_link.stl`** — 3D mesh asset for the robot's base structure.
- **`controller.yaml`** — Configuration for joint controllers.

---

## Prerequisites

- **ROS 2** (Humble or later recommended)
- **Gazebo Ignition / Harmonic** with `ros_gz_sim`
- The following ROS 2 packages:
  - `robot_state_publisher`
  - `joint_state_publisher_gui`
  - `xacro`
  - `rviz2`
  - `ros_gz_sim`

---

## Building the Package

```bash
cd ~/ros2_ws

rosdep install --from-paths src --ignore-src -r -y

colcon build --packages-select my_robot_description

source install/setup.bash
```

---

## Usage

```bash
# Launch full simulation
ros2 launch my_robot_description sim.launch.py

# Visualize in RViz2
ros2 launch my_robot_description display.launch

# Spawn seed balls (while simulation is running)
ros2 run my_robot_description spawn_ball.py
```

---

## Future Work / Roadmap

- [ ] Add Gazebo plugins (sensors, actuators) to `my_robot.gazebo`
- [ ] Integrate joint controllers via `controller.launch` and `controller.yaml`
- [ ] Add sorting or manipulation behaviour for the seed balls
- [ ] Improve the robot URDF with additional links and joints
- [ ] Add a proper world file with hopper geometry instead of an empty world
- [ ] Write automated tests for the launch files and spawn script
- [ ] Add ROS 2 parameter support to `spawn_ball.py` for runtime configuration
