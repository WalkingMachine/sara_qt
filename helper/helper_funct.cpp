/**
    Sara_UI
    helper_funct.cpp
    Purpose: Publisher for a few system values for ui print in our robot

    @author:	Lucas Maurice
	 @contact:	lucas.maurice@outlook.com
    @version:	1.0 28/04/17
*/
#include "helper.h"

void refreshCPUdata(Type_CPU *CPU_data, const bool *bRun){
	char buffer[BUFFER];    //reading buffer for command execution

	FILE * f;               //link to terminal

	int iCores;

	ROS_INFO("Start CPU usage reading loop.");

	while(*bRun){

		//get current cpu usage via mpstat linux command
		f = popen( "mpstat -P ALL 1 1", "r" );
		//if not able to run command
		if ( f == 0 ) {
			ROS_INFO("Could not execute");
		}else{
			iCores = 0;
			//go to first usefull line
			for(int iReadingLine=0; iReadingLine<FIRST_CPU_LINE; iReadingLine++){
				fgets( buffer, BUFFER,  f );
			}
			while( fgets( buffer, BUFFER, f)) {
				//end loop when reading is done
				if(buffer[0]=='\n') break;
				//else, if its the global usage line
				else if(buffer[13] == 'a' && buffer[14] == 'l' && buffer[15] == 'l'){
					readLastValue(buffer, CPU_data->strCPU_Usage, FLOAT_CAR_SIZE, ' ');

					//else, if its a core usage line
				}else if(buffer[15] == '0' + iCores){
					readLastValue(buffer, CPU_data->strTabCPU_Cores_Usage[iCores], FLOAT_CAR_SIZE, ' ');

					iCores += 1;
				}
			}
			//closing terminal
			pclose(f);
		}
		CPU_data->iNumberOfCore = iCores;
	}

	ROS_INFO("Stop CPU usage reading loop.");
}

void refreshMemoryData(Type_Usage *enrMemory, Type_Usage *enrSwap, const bool *bRun){
	char buffer[BUFFER];    //reading buffer for command execution

	FILE * f;               //link to terminal

	ROS_INFO("Start Memory usage reading loop.");

	while(*bRun){
		//get current cpu usage via mpstat linux command
		f = popen( "free -lm", "r" );

		//if not able to run command
		if ( f == 0 ) {
			ROS_INFO("Could not execute");
		}else{
			while(fgets(buffer, BUFFER, f)) {
				//Memory line reached
				if(buffer[0]=='L'){
					readMemoryUsageValues(buffer, enrMemory);
				}
				//Swap line reached
				else if(buffer[0] == 'S'){
					readMemoryUsageValues(buffer, enrSwap);
				}
			}
			//closing terminal
			pclose(f);

			//waiting for next prob
			usleep(1000000);
		}
	}
	ROS_INFO("Stop Memory usage reading loop.");
}

void readLastValue(char *theLine, char theResult[], int iSizeResult, char cSeparator){
	int iIndex = -1;
	int iLoop = 0;
	bool bOk = false;

	//security check for pointer initialisation
	if(theLine != NULL){
		//browse all chars until reach end line charactere '\n' or the string end charactere '\0'.
		while(theLine[iLoop] != '\n' && theLine[iLoop] != '\0'){
			if(theLine[iLoop] == cSeparator){
				//store the index after the separator caractere
				iIndex = iLoop + 1;
			}
			iLoop ++;
		}

		//copy the end characteres of the line
		for(iLoop = iIndex; iLoop - iIndex + 1 < iSizeResult; iLoop++){
			//if reach end line charactere '\n' or the string end charactere '\0' before the end of the result array.
			if(theLine[iLoop] == '\n' || theLine[iLoop] == '\0'){
				//break the loop
				break;
			}else{
				//copy charactere
				theResult[iLoop - iIndex] = theLine[iLoop];
			}
		}
		//write end charactere of the result string
		theResult[iLoop - iIndex] = '\0';
	}
}

void readMemoryUsageValues(char buffer[], Type_Usage *enrUsage){
	int iBufferLoop = 0;
	int iIndex;
	//go to first number (TOTAL Memory)
	while(!(buffer[iBufferLoop] >= '0' && buffer[iBufferLoop] <= '9') && buffer[iBufferLoop] != '\0'){
		iBufferLoop ++;
	}

	iIndex = iBufferLoop;
	//copy all characters of the first number
	while((buffer[iBufferLoop] >= '0' && buffer[iBufferLoop] <= '9') && buffer[iBufferLoop] != '\0'){
		enrUsage->strTotal[iBufferLoop - iIndex] = buffer[iBufferLoop];
		iBufferLoop ++;
	}
	enrUsage->strTotal[iBufferLoop - iIndex] = '\0';

	//go to second number (USED Memory)
	while(!(buffer[iBufferLoop] >= '0' && buffer[iBufferLoop] <= '9') && buffer[iBufferLoop] != '\0'){
		iBufferLoop ++;
	}

	//go to end of number
	while((buffer[iBufferLoop] >= '0' && buffer[iBufferLoop] <= '9') && buffer[iBufferLoop] != '\0'){
		iBufferLoop ++;
	}

	//go to third number (FREE Memory)
	while(!(buffer[iBufferLoop] >= '0' && buffer[iBufferLoop] <= '9') && buffer[iBufferLoop] != '\0'){
		iBufferLoop ++;
	}

	iIndex = iBufferLoop;
	//copy all caracters of the second number
	while((buffer[iBufferLoop] >= '0' && buffer[iBufferLoop] <= '9') && buffer[iBufferLoop] != '\0'){
		enrUsage->strUsed[iBufferLoop - iIndex] = buffer[iBufferLoop];
		iBufferLoop ++;
	}
	enrUsage->strUsed[iBufferLoop - iIndex] = '\0';
}

std_msgs::Header header_generate(int iSeq){
	//just write some datas
	std_msgs::Header enrRetHeader;
	enrRetHeader.seq = iSeq;
	enrRetHeader.stamp = ros::Time::now();			//read timestamp
	enrRetHeader.frame_id = "0";
	return enrRetHeader;
}

diagnostic_msgs::DiagnosticStatus status_generate(std::string strName, std::string strMessage, std::string strHardwareID, char level, std::vector<diagnostic_msgs::KeyValue> valuesVector){
	//just write some datas
	diagnostic_msgs::DiagnosticStatus status;
	status.name = strName;
	status.message = strMessage;
	status.hardware_id = strHardwareID;
	status.level = level;
	status.values = valuesVector;
	return status;
}

diagnostic_msgs::DiagnosticStatus CPUPublisher(Type_CPU *CPU_data){
	//publications variables
	diagnostic_msgs::KeyValue value;

	//data vectors
	std::vector<diagnostic_msgs::KeyValue> valuesVector;

	//string stream for generate status message
	std::stringstream strName;

	//generate status message
	strName << CPU_data->iNumberOfCore;

	//push data into vector for each CPU cores
	for (int iLoop = 0; iLoop < CPU_data->iNumberOfCore; iLoop++) {
		value.key = '0' + iLoop;
		value.value = CPU_data->strTabCPU_Cores_Usage[iLoop];
		valuesVector.push_back(value);
	}

	//generate status with standard hardware ID and previous generated value vector and name
	return status_generate("CPU_Usage", strName.str(), HARDWARE_ID, 0, valuesVector);
}

diagnostic_msgs::DiagnosticStatus MemoryPublisher(Type_Usage *enrMemory, Type_Usage *enrSwap){
	//publications variables
	diagnostic_msgs::KeyValue value;

	//data vector
	std::vector<diagnostic_msgs::KeyValue> valuesVector;

	//string stream for generate status message
	std::stringstream strName;

	//copy values
	value.key = "Mem_Total";
	value.value = enrMemory->strTotal;
	valuesVector.push_back(value);
	value.key = "Mem_Used";
	value.value = enrMemory->strUsed;
	valuesVector.push_back(value);
	value.key = "Swap_Total";
	value.value = enrSwap->strTotal;
	valuesVector.push_back(value);
	value.key = "Swap_Used";
	value.value = enrSwap->strUsed;
	valuesVector.push_back(value);

	//generate status with standard hardware ID and previous generated value vector and name
	return status_generate("Memory_Usage", "", HARDWARE_ID, 0, valuesVector);
}
