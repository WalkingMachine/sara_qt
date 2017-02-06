#ifndef CTHREADTOPICSSUBSCRIBER_H
#define CTHREADTOPICSSUBSCRIBER_H

#include <QThread>
#include <QString>
#include <ros/ros.h>
#include <turtlesim/Pose.h>

class CThreadTopicsSubscriber: public QThread
{
    Q_OBJECT

public:
   //static void setFoo(CThreadTopicsSubscriber* obj);
    ~CThreadTopicsSubscriber();

public slots:
    void subscribeSlot(QString topic);
    void unsubscribeSlot();

protected:
    void run();

private:
    ros::NodeHandle nh;
    ros::Subscriber subscriber;
    bool bThreadRun;
    bool bIsSubscribe;
    void callbackMessageReceived(const turtlesim::Pose &msg);

signals:
    void newMessageReceivedSignal(QString topic);

};
#endif // CTHREADTOPICSSUBSCRIBER_H
