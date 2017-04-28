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
	int	i = 0;									// integer value for publisher sequence

	//Memory variables
	Type_Usage enrMemory;
	Type_Usage enrSwap;

	//CPU variables
	int	iNumberOfCore = 0;					// number of core of the CPU
	char	strCPU_Usage[FLOAT_CAR_SIZE];						//
	char	strTabCPU_Cores_Usage[NUM_MAX_CORES][FLOAT_CAR_SIZE];	// actual usage of each CPU's core


	//threads values
	bool	bRun = true;							//

	//init ros connection
	ros::init(argc, argv, "ui_helper");
	ros::NodeHandle nh;

	ROS_INFO("Starting UI helper.");

	ros::Publisher diagnostic_publisher = nh.advertise<diagnostic_msgs::DiagnosticArray>("diagnostics", 100);

	ros::Rate loop_rate(2);

	//Create and launch usage refresh threads
	std::thread CPURefreshThread(refreshCPUdata, strCPU_Usage, strTabCPU_Cores_Usage, &iNumberOfCore, &bRun);
	std::thread MemoryRefreshThread(refreshMemoryData, &enrMemory, &enrSwap, &bRun);

	while(ros::ok()){
		//CPU publisher function
		CPUPublisher(diagnostic_publisher, strCPU_Usage, strTabCPU_Cores_Usage, iNumberOfCore);
		MemoryPublisher(diagnostic_publisher, &enrMemory, &enrSwap);

		ros::spinOnce();
		//delay for respect publication ratess
		loop_rate.sleep();
	}

	bRun = false;
	CPURefreshThread.join();
	ROS_INFO("END UI helper.");
}
