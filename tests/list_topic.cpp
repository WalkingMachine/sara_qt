#include <ros/ros.h>

#define POSITION_TAB 2
#define POSITION_TOPIC_NAME 0
#define POSITION_TOPIC_TYPE 1

int main(int argc, char** argv){
  ros::init(argc, argv, "ros_something");

  XmlRpc::XmlRpcValue params("ros_topic_list");
  XmlRpc::XmlRpcValue results;
  XmlRpc::XmlRpcValue r;

  ros::master::execute("getTopicTypes", params, results, r, false);

  for (int iBcl = 0; iBcl < results[POSITION_TAB].size(); iBcl++)
  {
    if(results[POSITION_TAB][iBcl].size() == 2){
      std::string topic = static_cast<std::string>(results[POSITION_TAB][iBcl][POSITION_TOPIC_NAME]);
      std::string type = static_cast<std::string>(results[POSITION_TAB][iBcl][POSITION_TOPIC_TYPE]);
      std::cout<<"Topic : "<<topic<<" -> "<<type<<std::endl;
    }
  }

  return 0;
}
