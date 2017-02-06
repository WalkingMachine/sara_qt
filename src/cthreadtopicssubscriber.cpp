#include "cthreadtopicssubscriber.h"
CThreadTopicsSubscriber::~CThreadTopicsSubscriber(){
    this->bThreadRun = false;
    this->exit();
}

void CThreadTopicsSubscriber::run(){
    bThreadRun = true;
    bIsSubscribe = false;
    while(bThreadRun){
        ros::spin();
    }
}

void CThreadTopicsSubscriber::subscribeSlot(QString topic){
    if(!bIsSubscribe){
        subscriber = nh.subscribe("turtle1/pose", 1, &CThreadTopicsSubscriber::callbackMessageReceived, this);
        bIsSubscribe=true;
    }
}

void CThreadTopicsSubscriber::unsubscribeSlot(){
    if(bIsSubscribe){
        subscriber.shutdown();
        bIsSubscribe=false;
    }
}

void CThreadTopicsSubscriber::callbackMessageReceived(const turtlesim::Pose &msg){
//    newMessageReceivedSignal(QString::number(msg.x));
    ROS_INFO_STREAM(msg);
}
