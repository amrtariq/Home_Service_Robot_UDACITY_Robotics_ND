#!/bin/sh
currentPath=$(pwd)
echo $currentPath
xterm  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(rospack find worlds)/myworld.world " &
sleep 10
xterm  -e  " roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$(rospack find map)/mymap.yaml " &
sleep 7
xterm  -e  " roslaunch turtlebot_rviz_launchers view_navigation.launch "
