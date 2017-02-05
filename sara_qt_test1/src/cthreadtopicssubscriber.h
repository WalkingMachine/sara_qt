#ifndef CTHREADTOPICSSUBSCRIBER_H
#define CTHREADTOPICSSUBSCRIBER_H

#include <QThread>
#include <ros/ros.h>
#include <turtlesim/Pose.h>

class CThreadTopicsSubscriber: public QThread
{
    Q_OBJECT

public:
    CThreadTopicsSubscriber();
    void subscribe();
    void unsubscribe();
    static void callback(const turtlesim::Pose &msg);

protected:
    void run();

private:
    ros::NodeHandle nh;
    ros::Subscriber subscriber;
    bool bStop;
};

//void callback(const turtlesim::Pose &msg);

#endif // CTHREADTOPICSSUBSCRIBER_H
