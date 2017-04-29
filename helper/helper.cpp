/**
    Sara_UI
    helper.cpp
    Purpose: Publisher for a few system values for ui print in our robot

    @author:	Lucas Maurice
	 @contact:	lucas.maurice@outlook.com
    @version:	1.0 28/04/17
*/

#include "helper.h"
int main(int argc, char **argv){
	//publication message
	diagnostic_msgs::DiagnosticArray message;

	//data vectors
	std::vector<diagnostic_msgs::KeyValue> valuesVector;
	std::vector<diagnostic_msgs::DiagnosticStatus> statusVector;

	int	iSequence = 0;									// integer value for publisher sequence

	//Memory variables
	Type_Usage enrMemory;
	Type_Usage enrSwap;

	//CPU variable
	Type_CPU CPU_data;
	CPU_data.iNumberOfCore = 0;


	//threads values
	bool	bRun = true;							//

	//init ros connection
	ros::init(argc, argv, "ui_helper");
	ros::NodeHandle nh;

	ROS_INFO("Starting UI helper.");

	ros::Publisher diagnostic_publisher = nh.advertise<diagnostic_msgs::DiagnosticArray>("diagnostics", 100);

	ros::Rate loop_rate(2);

	//Create and launch usage refresh threads
	std::thread CPURefreshThread(refreshCPUdata, &CPU_data, &bRun);
	std::thread MemoryRefreshThread(refreshMemoryData, &enrMemory, &enrSwap, &bRun);

	while(ros::ok()){
		//clear status
		statusVector.clear();

		//add status to vector
		statusVector.push_back(CPUPublisher(&CPU_data));
		statusVector.push_back(MemoryPublisher(&enrMemory, &enrSwap));

		//add header and status to message
		message.header = header_generate(iSequence);
		message.status = statusVector;

		//publish message
		if(CPU_data.iNumberOfCore){
			diagnostic_publisher.publish(message);
		}

		//increment static sequence number
		iSequence ++;

		ros::spinOnce();
		//delay for respect publication ratess
		loop_rate.sleep();
	}

	bRun = false;
	CPURefreshThread.join();
	ROS_INFO("END UI helper.");
}
