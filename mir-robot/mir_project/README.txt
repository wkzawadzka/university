1. Add dependency to mir_robot/package.xml
  <exec_depend>mir_project</exec_depend>

2. Rebuild workspace
in catkin directory:
$rm -rf build/ devel/
$catkin build
$source ~/.bashrc

3. Preliminaries
roscore
roslaunch mir_gazebo mir_maze_world.launch
rosservice call /gazebo/unpause_physics   # or click the "start" button in the Gazebo GUI

4. Running the project
STEP 1 (SLAM): Building the map
roslaunch $(find mir_project/launch/map_creation.launch)

STEP 2: Save the map
$rosrun map_server map_saver -f $(find mir_project/maps)

STEP 3: Localization & navigation
roslaunch $(find mir_project/launch/navigation.launch)
