cmake_minimum_required(VERSION 3.8)
project(my_robot_description)

# Find the build tool
find_package(ament_cmake REQUIRED)

# Install the directories so ROS 2 can see your meshes and urdf
install(
  DIRECTORY launch meshes urdf
  DESTINATION share/${PROJECT_NAME}
)

# Install the python script so 'ros2 run' can find it
install(PROGRAMS
  scripts/spawn_ball.py
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()