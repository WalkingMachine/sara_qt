#include <ros/ros.h>

int main(int argc, char *argv[]){
    ros::init(argc, argv, "logs_writter_node");
    ros::NodeHandle nh;

    ROS_DEBUG_STREAM("Log DEBUG");
    ROS_INFO_STREAM("Log INFO");
    ROS_WARN_STREAM("Log WARNING");
    ROS_ERROR_STREAM("Log ERROR");
    ROS_FATAL_STREAM("Log FATAL");
}
