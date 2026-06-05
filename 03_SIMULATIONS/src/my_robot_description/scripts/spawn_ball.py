#!/usr/bin/env python3

import sys
import rclpy
from rclpy.node import Node
import subprocess
import time
import math
import random

class LayeredBallSpawner(Node):
    def __init__(self):
        super().__init__('ball_spawner')
        
        # --- PARAMETERS ---
        self.total_balls = 36     
        
        # Diameter Range in meters
        self.min_dia = 0.015       # 15mm (Your smallest ball)
        self.max_dia = 0.030       # 30mm (Your largest ball)
        
        # Physics Reference (Density in kg/m^3)
        # 1500 kg/m^3 gives realistic weight variation
        self.base_density = 1500   
        
        # Grid Settings
        self.grid_spacing = 0.05   
        self.layer_height = 0.05   
        self.start_z = 0.8         
        
        # Hopper Limits
        self.max_cols = 3          
        self.max_rows = 4          
        # ------------------

        self.spawn_balls()

    def get_color_from_size(self, diameter):
        """Generates a color based on size: 15mm=Green, 35mm=Red"""
        # Normalize the diameter (0.0 = small, 1.0 = large)
        ratio = (diameter - self.min_dia) / (self.max_dia - self.min_dia)
        
        # Green (0,1,0) to Red (1,0,0) gradient
        r = ratio
        g = 1.0 - ratio
        b = 0.0
        return f"{r:.2f} {g:.2f} {b:.2f} 1"

    def spawn_balls(self):
        batch_id = int(time.time() % 10000)
        self.get_logger().info(f'Spawning {self.total_balls} balls with uniform size variation...')
        
        count = 0
        layer = 0
        
        while count < self.total_balls:
            for row in range(self.max_rows):
                for col in range(self.max_cols):
                    
                    if count >= self.total_balls:
                        break

                    # Calculate Grid Position (Centered)
                    x_offset = (self.max_cols - 1) * self.grid_spacing / 2 
                    y_offset = (self.max_rows - 1) * self.grid_spacing / 2
                    
                    x = (col * self.grid_spacing) - x_offset
                    y = (row * self.grid_spacing) - y_offset - 0.2
                    z = self.start_z + (layer * self.layer_height)

                    # Uniform Size Variation
                    # Every ball gets a random diameter between 15mm and 30mm
                    chosen_dia = random.uniform(self.min_dia, self.max_dia)
                    chosen_radius = chosen_dia / 2.0
                    
                    # Dynamic Physics (Mass & Inertia)
                    volume = (4.0/3.0) * math.pi * (chosen_radius**3)
                    mass = self.base_density * volume
                    inertia = (2.0/5.0) * mass * (chosen_radius**2)

                    # Color Assignment
                    color_rgba = self.get_color_from_size(chosen_dia)

                    # pawn Command
                    name = f"seedball_{batch_id}_{count}"
                    self.spawn_single_ball(name, x, y, z, chosen_radius, mass, inertia, color_rgba)
                    
                    count += 1
                    time.sleep(0.05) 
            
            layer += 1
            self.get_logger().info(f"Layer {layer} complete.")

    def spawn_single_ball(self, name, x, y, z, radius, mass, i_val, color):
        sdf_xml = f"""
        <?xml version="1.0" ?>
        <sdf version="1.6">
            <model name="{name}">
                <pose>{x} {y} {z} 0 0 0</pose>
                <link name="link">
                    <inertial>
                        <mass>{mass}</mass>
                        <inertia>
                            <ixx>{i_val}</ixx><ixy>0</ixy><ixz>0</ixz>
                            <iyy>{i_val}</iyy><iyz>0</iyz>
                            <izz>{i_val}</izz>
                        </inertia>
                    </inertial>
                    <visual name="visual">
                        <geometry><sphere><radius>{radius}</radius></sphere></geometry>
                        <material>
                            <ambient>{color}</ambient>
                            <diffuse>{color}</diffuse>
                        </material>
                    </visual>
                    <collision name="collision">
                        <geometry><sphere><radius>{radius}</radius></sphere></geometry>
                        <max_contacts>30</max_contacts>
                        <surface>
                            <friction>
                                <ode><mu>0.7</mu><mu2>0.7</mu2></ode>
                            </friction>
                            <contact>
                                <ode><kp>100000.0</kp><kd>1.0</kd><min_depth>0.001</min_depth><max_vel>10.0</max_vel></ode>
                            </contact>
                        </surface>
                    </collision>
                </link>
            </model>
        </sdf>
        """
        cmd = [
            'ros2', 'run', 'ros_gz_sim', 'create',
            '-string', sdf_xml,
            '-name', name,
            '-x', str(x), '-y', str(y), '-z', str(z)
        ]
        subprocess.Popen(cmd)

def main(args=None):
    rclpy.init(args=args)
    node = LayeredBallSpawner()
    rclpy.shutdown()

if __name__ == '__main__':
    main()