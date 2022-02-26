# Home Service Robot

<p align="center"><img src="./Images/homeServiceRobot.gif"></p>

**Project Goals**

Use the knowledge gathered through Robotics NanoDegree to configure robot to be able to map, navigate send and track goals in a simulated designed enviroment.

* Enviroment Done using Building Editor in Gazebo.
* Teleoperate the robot and manually to create a map using SLAM.
* make pick_objects node to send two goals to robot one after another.
* make add_markers node to show/hide markers either with pre-set delay or depending on robot reaching goals.

### Configuration

* Ubuntu 16.04 OS with and g++/gcc
* ROS Kinetic
* following ROS packages were used and the process of obtaining them is detailed below:
	* [gmapping](http://wiki.ros.org/gmapping)
	* [turtlebot_teleop](http://wiki.ros.org/turtlebot_teleop)
	* [turtlebot_rviz_launchers](http://wiki.ros.org/turtlebot_rviz_launchers)
	* [turtlebot_gazebo](http://wiki.ros.org/turtlebot_gazebo)

### Directory Tree and contents

```
.
├── README.md
├── images
│   ├── ... ...
├── CMakeLists.txt
├── add_markers
│   └── src
│       ├── add_markers.cpp
│       └── add_markers_5s.cpp
│   ├──  ... ...
├── map
│   ├── mymap.pgm
│   ├── mymap.yaml
├── pick_objects
│   └── src
│       ├── pick_objects.cpp
│   ├──  ... ...
├── rvizConfig
│   └── rvizConfigMarker.rviz
├── scripts
│   ├── add_marker.sh
│   ├── home_service.sh
│   ├── pick_objects.sh
│   ├── test_navigation.sh
│   └── test_slam.sh
├── slam_gmapping
│   ├── gmapping
│   |── ... ...
├── turtlebot
│   |── turtlebot_teleop
│   |── ... ...
├── turtlebot_interactions
│   |── turtlebot_rviz_launchers
│   |── ... ...
|── turtlebot_simulator
│   ├── turtlebot_gazebo
│   |── ... ...

```

This directory represents the main project's `src` folder structure with following contents

* README.md: this file.
* **images** - GIF for Final Output
* **add_markers** - add marker node C++ node
* **map** - map data
* **pick_objects** - pick-objects C++ node code
* **rvizConfig** - folder with rViz configurations used with some launch scripts
* **scripts** - shell scripts
  * `home_service.sh` - main script for the home-service-robot
	* `add_marker.sh` - script for testing add_marker concept with `add_markers_5s.cpp`
	* `pick_objects.sh` - script for testing pick_objects concept with `pick_objects`
	* `test_navigation.sh` - script for testing navigation
	* `test_slam.sh` - script for performing SLAM and preparing map
* **slam_gmapping** -  ROS package with `gmapping_demo.launch` file
* **turtlebot** -  ROS package with `keyboard_teleop.launch` file
* **turtlebot_interactions** -  ROS package with `view_navigation.launch` file
* **turtlebot_simulator** -  ROS package with `turtlebot_world.launch` file

---

### Clone and Build

first create catkin_ws as follows:

```
mkdir -p catkin_ws/src
cd catkin_ws/src
catkin_init_workspace
```

clone the repo directly in src folder

Install dependencies:

```
rosdep -i install gmapping -y
rosdep -i install turtlebot_teleop -y
rosdep -i install turtlebot_rviz_launchers -y
rosdep -i install turtlebot_gazebo -y
```

Go back to catkin workspace and build it

```
cd ~/catkin_ws/
catkin_make
```
now you can visit scripts folder and run required scripts
Ex. home_service.sh
```
source devel/setup.bash
cd ~/catkin_ws/src/scripts
chmod +x ./home_service.sh
./home_service.sh
```
