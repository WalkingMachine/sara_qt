#include <ros/ros.h>
#include <rosgraph_msgs/Log.h>
#include <turtlesim/Pose.h>


void showNewLog(const rosgraph_msgs::Log &message);

int main(int argc, char *argv[]){
  ros::init(argc, argv, "hello_ros");
  ros::console::set_logger_level(ROSCONSOLE_DEFAULT_NAME, ros::console::levels::Debug);
  ros::NodeHandle nh;
  ros::Subscriber sub = nh.subscribe("/rosout", 1000, &showNewLog);
  ros::spin();
  return 0;
}

void showNewLog(const rosgraph_msgs::Log &message){
  printf("TRY - %s \n",message.msg);
}
