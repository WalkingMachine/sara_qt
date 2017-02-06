#include <ros/ros.h>
#include <rosgraph_msgs/Log.h>
#include <turtlesim/Pose.h>


void showNewLog(const turtlesim::Pose &message);

int main(int argc, char *argv[]){
  ros::init(argc, argv, "hello_ros");
  ros::NodeHandle nh;
  ros::Subscriber sub = nh.subscribe("turtle1/pose", 5, &showNewLog);
  ROS_INFO_STREAM(sub.getNumPublishers());
  ros::spin();
  return 0;
}

void showNewLog(const turtlesim::Pose &message){
  ROS_INFO("log");
}
