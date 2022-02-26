#!/bin/sh
currentPath=$(pwd)
echo $currentPath
xterm  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$currentPath/../../src/worlds/U2.world " &
sleep 10
xterm  -e  " roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$currentPath/../../src/map/mymap.yaml " &
sleep 7
xterm  -e  " roslaunch turtlebot_rviz_launchers view_navigation.launch " &
sleep 7
xterm  -e  " rosrun  add_markers add_markers_5s"
