#!/bin/sh
xterm  -e  "source /opt/ros/kinetic/setup.bash " &
xterm  -e  "source /home/workspace/catkin_ws/devel/setup.bash; roscore " &

sleep 5

xterm  -e  "export ROBOT_INITIAL_POSE='-x 0 -y 0 -z 0 -R 0 -P 0 -Y 0';
roslaunch turtlebot_gazebo turtlebot_world.launch " & 

sleep 5

xterm  -e  "roslaunch turtlebot_gazebo amcl_demo.launch " & 

sleep 5

xterm  -e  "roslaunch turtlebot_rviz_launchers view_navigation.launch" & 

sleep 8

xterm  -e  "rosrun pickup_objects pickup_objects "& 

xterm  -e  "rosrun add_markers add_markers"
