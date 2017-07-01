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
	ROS_INFO("Command reception");

	if (!message.strName.compare("stop")) {
		ROS_INFO("stop");
		if (bRunning) {
			ROS_INFO("stop - go");
			bRunning = false;
			kill(pid, SIGINT);
		}
	} else {
		ROS_INFO("run");
		if (!bRunning) {
			ROS_INFO("run - go");
			bRunning = true;

			//generate command to run
			char command[500];
			strcpy(command, message.strCommand.c_str()  );
			strcat(command, " & echo $!");

			//run roslaunch
			int newPID;
			FILE *fp = popen(command, "r");

			//read new PID
			fscanf(fp, "%d", &newPID);
			pclose(fp);

			//save PID
			pid = newPID;
		}
	}
}

void CHelper_Launcher::Subscribe(ros::NodeHandle nh) {
	_subscriber = nh.subscribe("sara_launch", 1, &CHelper_Launcher::callbackMessageReceived, this);
}

