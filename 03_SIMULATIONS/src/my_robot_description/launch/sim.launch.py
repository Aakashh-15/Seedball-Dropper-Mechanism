import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, SetEnvironmentVariable
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
import xacro

def generate_launch_description():
    pkg_name = 'my_robot_description'
    pkg_share = get_package_share_directory(pkg_name)

    install_dir = os.path.dirname(pkg_share) 
    if 'GZ_SIM_RESOURCE_PATH' in os.environ:
        gz_resource_path = os.environ['GZ_SIM_RESOURCE_PATH'] + ':' + install_dir
    else:
        gz_resource_path = install_dir
    set_resource_path = SetEnvironmentVariable(name='GZ_SIM_RESOURCE_PATH', value=gz_resource_path)

    # Process Robot Xacro
    file_subpath = 'urdf/my_robot.xacro'
    xacro_file = os.path.join(pkg_share, file_subpath)
    robot_description_raw = xacro.process_file(xacro_file).toxml()
    
    # Define Nodes
    node_robot_state_publisher = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        output='screen',
        parameters=[{'robot_description': robot_description_raw,
                     'use_sim_time': True}]
    )

    gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            [os.path.join(get_package_share_directory('ros_gz_sim'),
                          'launch', 'gz_sim.launch.py')]),
        launch_arguments={'gz_args': '-r empty.sdf'}.items(),
    )

    spawn_robot = Node(
        package='ros_gz_sim',
        executable='create',
        arguments=['-topic', 'robot_description',
                   '-entity', 'my_robot'], 
        output='screen'
    )

    return LaunchDescription([
        set_resource_path,
        gazebo,
        node_robot_state_publisher,
        spawn_robot,
    ])