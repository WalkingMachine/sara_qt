//
// Created by lucas on 5/22/17.
//

#include "CHelper_Launcher.h"

void CHelper_Launcher::run() {
	bRunning = false;
	
	ROS_INFO("Thread START");
	
	ROS_INFO("Ros Subscription to Diagnostics");
	
	ROS_INFO("spin");
	ros::spin();
	
	ROS_INFO("Thread END");
}

void CHelper_Launcher::callbackMessageReceived(const sara_ui::sara_launch message) {
	static CHelper_Thread thread;
	
	if (!message.strName.compare("stop")) {
		if (bRunning) {
			bRunning = false;
			thread.terminate();
		}
	} else {
		if (!bRunning) {
			bRunning = true;
			thread.setCommand(message.strCommand);
			thread.start(QThread::LowPriority);
		}
	}
}

void CHelper_Launcher::Subscribe(ros::NodeHandle nh) {
	_subscriber = nh.subscribe("sara_launch", 1, &CHelper_Launcher::callbackMessageReceived, this);
}

