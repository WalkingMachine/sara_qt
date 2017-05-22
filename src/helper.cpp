/**
    Sara_UI
    helper.cpp
    Purpose: Publisher for a few system values for ui print in our robot

    @author:	Lucas Maurice
	@contact:	lucas.maurice@outlook.com
    @version:	1.0 28/04/17
*/

#include "helper.h"
#include "CHelper_Launcher.h"

int main(int argc, char **argv){
	//publication message
	diagnostic_msgs::DiagnosticArray message;

	//data vectors
	std::vector<diagnostic_msgs::KeyValue> valuesVector;
	std::vector<diagnostic_msgs::DiagnosticStatus> statusVector;

	// integer value for publisher sequence
	int iSequence = 0;

	//Memory variables
	Type_Usage enrMemory;
	Type_Usage enrSwap;

	//CPU variable
	Type_CPU CPU_data;
	CPU_data.iNumberOfCore = 0;

	//Temperature variable
	Type_Temperature temperatures;

	//init ros connection
	ros::init(argc, argv, "ui_helper");
	ros::NodeHandle nh;
	ros::Publisher diagnostic_publisher = nh.advertise<diagnostic_msgs::DiagnosticArray>("diagnostics", 100);
	ros::Rate loop_rate(2);

	//INFO print
	ROS_INFO("Starting UI helper.");

	//Create and launch usage refresh threads
	bool	bRun = true;

	std::thread CPURefreshThread(refreshCPUdata, &CPU_data, &bRun);
	std::thread MemoryRefreshThread(refreshMemoryData, &enrMemory, &enrSwap, &bRun);
	std::thread TemperatureRefreshThread(refreshTemperatureData, &temperatures, &bRun);

    CHelper_Launcher LauncherThread;
    LauncherThread.run();

	//Start publisher loop
	while(ros::ok()){
		//clear status
		statusVector.clear();

		if(CPU_data.iNumberOfCore){
			//add status to vector
			statusVector.push_back(CPUPublisher(&CPU_data));
			statusVector.push_back(MemoryPublisher(&enrMemory, &enrSwap));
			if(temperatures.iNumberOfSensors){
				statusVector.push_back(TemperaturePublisher(&temperatures));
			}

			//add header and status vector to message
			message.header = header_generate(iSequence);
			message.status = statusVector;

			//publish message
			diagnostic_publisher.publish(message);
		}

		//increment static sequence number
		iSequence ++;

		//delay for respect publication ratess
		loop_rate.sleep();
		ros::spinOnce();
	}

	bRun = false;
	CPURefreshThread.join();
    LauncherThread.stop();
	ROS_INFO("END UI helper.");
}
