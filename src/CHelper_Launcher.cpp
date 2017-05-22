//
// Created by lucas on 5/22/17.
//

#include "CHelper_Launcher.h"

CHelper_Launcher::~CHelper_Launcher(){
    this->exit();
}

void CHelper_Launcher::run(){
    bRunning = false;

    ROS_INFO("Thread START");

    subscribeROS();

    ROS_INFO("Ros Subscription to Diagnostics");

    while(ros::ok()){
        ROS_INFO("spin");
        ros::spin();
    }

    ROS_INFO("Thread END");
}

void CHelper_Launcher::callbackMessageReceived(const sara_ui::sara_launch message){
    static CHelper_Thread thread;
    
    if(!message.strName.compare("stop")) {
        if(bRunning){
            bRunning = false;
            thread.terminate();
        }
    }else{
        if(!bRunning){
            bRunning = true;
            thread.setCommand(message.strCommand);
            thread.start(QThread::LowPriority);
        }
    }
}

void CHelper_Launcher::subscribeROS(){
    ROS_INFO("Subscript");
    _subscriber = _nh.subscribe("sara_launch", 1, &CHelper_Launcher::callbackMessageReceived, this);
}

void CHelper_Launcher::unsubscribeROS(){
    _subscriber.shutdown();
}

void CHelper_Launcher::stop() {
    unsubscribeROS();
}

