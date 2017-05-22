//
// Created by lucas on 5/22/17.
//

#ifndef SARA_UI_CHELPER_LAUNCHER_H
#define SARA_UI_CHELPER_LAUNCHER_H

#include <QThread>

#include <ros/ros.h>
#include <sara_ui/sara_launch.h>

#include <stdlib.h>

#include "CHelper_Thread.h"

class CHelper_Launcher : public QThread{
public:
    ~CHelper_Launcher();
    void run();
    void stop();
    void callbackMessageReceived(const sara_ui::sara_launch message);

private:
    ros::NodeHandle _nh;
    ros::Subscriber _subscriber;
    bool bRunning;
    void subscribeROS();
    void unsubscribeROS();
};


#endif //SARA_UI_CHELPER_LAUNCHER_H
