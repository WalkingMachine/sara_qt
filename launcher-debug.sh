#!/bin/bash
cd ~/sara_ws


source /opt/ros/kinetic/setup.bash
source ~/sara_ws/devel/setup.bash

export ROS_MASTER_URI=http://192.168.0.118:11311/

rosrun sara_ui sara_ui --debug
