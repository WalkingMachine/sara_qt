#include "cthreadtopicssubscriber.h"
CThreadTopicsSubscriber::CThreadTopicsSubscriber(){

}

void CThreadTopicsSubscriber::run(){
    bStop = true;
    while(bStop){
        ros::spin();
    }
}

void CThreadTopicsSubscriber::subscribe(){
    subscriber = nh.subscribe("turtle1/pose", 1000, &callback);
}

void CThreadTopicsSubscriber::unsubscribe(){
    subscriber.shutdown();
}

void CThreadTopicsSubscriber::callback(const turtlesim::Pose &msg){
  ROS_INFO_STREAM(msg);
}
