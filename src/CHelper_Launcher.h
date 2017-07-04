//
// Created by lucas on 5/22/17.
//

#ifndef SARA_UI_CHELPER_LAUNCHER_H
#define SARA_UI_CHELPER_LAUNCHER_H

#include <QThread>

#include <ros/ros.h>
#include <sara_ui/sara_launch.h>

#include <stdlib.h>

#include <sys/types.h>
#include <signal.h>


class CHelper_Launcher : public QThread {
public:
	void Subscribe(ros::NodeHandle nh);
	
	void run();
	
	void callbackMessageReceived(const sara_ui::sara_launch message);

private:
	ros::Subscriber _subscriber;
	bool bRunning;
	pid_t pid;
};


#endif //SARA_UI_CHELPER_LAUNCHER_H
