#include <ros/ros.h>
//#include <QApplication>

int main(int argc, char** argv){
  ros::init(argc, argv, "hello_ros");

  ros::NodeHandle nh;

  ROS_INFO_STREAM("Hello SARA");

}
