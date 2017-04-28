/**
    Sara_UI
    helper_funct.cpp
    Purpose: Publisher for a few system values for ui print in our robot

    @author:	Lucas Maurice
	 @contact:	lucas.maurice@outlook.com
    @version:	1.0 28/04/17
*/
#include "tests/helper.h"

void refreshCPUdata(char strCPU_Usage[], char strTabCPU_Cores_Usage[][FLOAT_CAR_SIZE], int *iNumberOfCore, bool *bRun){
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
					readLastValue(buffer, strCPU_Usage, FLOAT_CAR_SIZE, ' ');

					//else, if its a core usage line
				}else if(buffer[15] == '0' + iCores){
					readLastValue(buffer, strTabCPU_Cores_Usage[iCores], FLOAT_CAR_SIZE, ' ');

					iCores += 1;
				}
			}
			//closing terminal
			pclose(f);
		}
		*iNumberOfCore = iCores;
	}

	ROS_INFO("Stop CPU usage reading loop.");
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


void CPUPublisher(ros::Publisher publisher, char strCPU_Usage[], char strTabCPU_Cores_Usage[][FLOAT_CAR_SIZE],int iNumberOfCore){
	static int iSequence = 0; //sequence number
	//security for publish only if there are data about CPU usage (use number of core for this)
	if(iNumberOfCore){
		//publications variables
		diagnostic_msgs::KeyValue value;
		diagnostic_msgs::DiagnosticStatus status;
		diagnostic_msgs::DiagnosticArray message;

		//data vectors
		std::vector<diagnostic_msgs::KeyValue> valuesVector;
		std::vector<diagnostic_msgs::DiagnosticStatus> statusVector;

		//string stream for generate status message
		std::stringstream strName;

		//generate status message
		strName << "cores:" << iNumberOfCore;

		//push data into vector for each CPU cores
		for (int iLoop = 0; iLoop < iNumberOfCore; iLoop++) {
			value.key = '0' + iLoop;
			value.value = strTabCPU_Cores_Usage[iLoop];
			valuesVector.push_back(value);
		}

		//generate status with standard hardware ID and previous generated value vector and name
		status = status_generate("CPU_Usage", strName.str(), HARDWARE_ID, 0, valuesVector);
		statusVector.push_back(status);

		//add header and status to message
		message.header = header_generate(iSequence);
		message.status = statusVector;

		//publish message
		publisher.publish(message);

		//increment static sequence number
		iSequence ++;
	}
}
