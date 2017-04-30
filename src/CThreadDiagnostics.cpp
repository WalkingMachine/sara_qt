#include "CThreadDiagnostics.h"
CThreadDiagnostics::~CThreadDiagnostics(){
	this->bThreadRun = false;
	this->exit();
}

void CThreadDiagnostics::run(){
	bIsSubscribe = false;

	CPU.enrNumberOfCore = 0;
	CPU.pCPUCoresUsage = NULL;

	ROS_INFO("Thread START");
	subscribeSlot();
	while(ros::ok()){
		ROS_INFO("spin");
		ros::spin();
	}
	ROS_INFO("Thread END");
}

void CThreadDiagnostics::subscribeSlot(){
	ROS_INFO("Subscript");
	if(!bIsSubscribe){
		subscriber = nh.subscribe("diagnostics", 1, &CThreadDiagnostics::callbackMessageReceived, this);
		bIsSubscribe=true;
	}
}

void CThreadDiagnostics::unsubscribeSlot(){
	if(bIsSubscribe){
		subscriber.shutdown();
		bIsSubscribe=false;
	}
}

void CThreadDiagnostics::callbackMessageReceived(const diagnostic_msgs::DiagnosticArray message){
	//if the hardware related data is the main computer of SARA
	if(!message.status[0].hardware_id.compare(HARDWARE_ID)){
		//read all status of the message
		for(std::vector<diagnostic_msgs::DiagnosticStatus>::const_iterator StatusIterator = message.status.begin(); StatusIterator != message.status.end(); ++StatusIterator){
			if(!StatusIterator->name.compare("CPU_Usage")){
				//Update Number of Cores
				CPU.enrNumberOfCore = readIntValue(StatusIterator->message);

				//Create new array of core
				float* enrTabCoresUsage = (float *)malloc(sizeof(float)*CPU.enrNumberOfCore);

				for(int iCoreNumber = 0; iCoreNumber<CPU.enrNumberOfCore; iCoreNumber++){
					enrTabCoresUsage[iCoreNumber] = 100 - readFloatValue(StatusIterator->values[iCoreNumber].value);
				}

				//link array with CPU struct
				CPU.pCPUCoresUsage = enrTabCoresUsage;

				//execute CPU update signal
				updateCPU(&CPU);
			}else if(!StatusIterator->name.compare("Memory_Usage")){
				//Update Memory Usages
				Memory.Memory_Total = readIntValue(StatusIterator->values[0].value);
				Memory.Memory_Used= Memory.Memory_Total - readIntValue(StatusIterator->values[1].value);
				Memory.Memory_Usage = Memory.Memory_Used * 100 / Memory.Memory_Total;
				//Update Swap Usages
				Memory.Swap_Total = readIntValue(StatusIterator->values[2].value);
				Memory.Swap_Used = Memory.Swap_Total - readIntValue(StatusIterator->values[3].value);
				Memory.Swap_Usage = Memory.Swap_Used * 100 / Memory.Swap_Total;

				//execute memory update signal
				updateMemory(&Memory);
			}
		}
	}






	/*
	 //Si le status recu est un status de data sur le CPU
	 ROS_INFO("RECEPTION");
		if(message.status[0].name[0] == 'C' && message.status[0].name[1] == 'P' && message.status[0].name[2] == 'U'){
		  //lecture des données d'utilisation du CPU pour chaque coeur
		  for(int iCoreId = 0; iCoreId < CPU_NBR_OF_CORE; iCoreId ++){
			 //Lecture de la frequence d'horloge du coeur
			 CPU.enrCPUCore[iCoreId].Clock_Speed = readIntValue(message, 1, CPU_SPEED_POS + iCoreId, 'M');;

			 //Lecture du taux d'utilisation user du coeur:
			 CPU.enrCPUCore[iCoreId].User_Usage = readFloatValue(message, 1, CPU_USAGE_POS + iCoreId*CPU_USAGE_SIZE + 1, '%');

			 //Lecture du taux d'utilisation nice du coeur:
			 CPU.enrCPUCore[iCoreId].Nice_Usage = readFloatValue(message, 1, CPU_USAGE_POS + iCoreId*CPU_USAGE_SIZE + 2, '%');

			 //Lecture du taux d'utilisation system du coeur:
			 CPU.enrCPUCore[iCoreId].System_Usage = readFloatValue(message, 1, CPU_USAGE_POS + iCoreId*CPU_USAGE_SIZE + 3, '%');

			 //Lecture du taux du coeur en IDLE:
			 CPU.enrCPUCore[iCoreId].IDLE = readFloatValue(message, 1, CPU_USAGE_POS + iCoreId*CPU_USAGE_SIZE + 4, '%');

			 //PRINT FOR DEBUG
			 #ifdef DEBUGCPU
			 ROS_INFO("Core %i Clk Speed        :  %i", iCoreId, CPU.enrCPUCore[iCoreId].Clock_Speed);
			 ROS_INFO("Core %i Nice Usage       :  %.2f", iCoreId, CPU.enrCPUCore[iCoreId].Nice_Usage);
			 ROS_INFO("Core %i System Usage     :  %.2f", iCoreId, CPU.enrCPUCore[iCoreId].System_Usage);
			 ROS_INFO("Core %i IDLE             :  %.2f", iCoreId, CPU.enrCPUCore[iCoreId].IDLE);
			 ROS_INFO("-------------------------------------------------------------------------");
			 #endif
		  }

		  //PRINT FOR DEBUG
		  #ifdef DEBUGCPU
		  //ROS_INFO("CPU Average Usage 1 min   :  %.2f", CPU.Average_Usage_1min);
		  //ROS_INFO("CPU Average Usage 5 min   :  %.2f", CPU.Average_Usage_5min);
		  //ROS_INFO("CPU Average Usage 15 min  :  %.2f", CPU.Average_Usage_15min);
		  //ROS_INFO("-------------------------------------------------------------------------");
		  #endif

		  //updateCPU(CPU.enrCPUCore[0].User_Usage + CPU.enrCPUCore[0].System_Usage, CPU.enrCPUCore[1].User_Usage + CPU.enrCPUCore[1].System_Usage,CPU.enrCPUCore[2].User_Usage + CPU.enrCPUCore[2].System_Usage,CPU.enrCPUCore[3].User_Usage + CPU.enrCPUCore[3].System_Usage);
		}
		else if(message.status[0].name[0] == 'M'){
		  Memory.Physical_Memory_Total = readIntValue(message, 0, 3, 'M');
		  Memory.Physical_Memory_Used = readIntValue(message, 0, 4, 'M');
		  Memory.Physical_Memory_Free = readIntValue(message, 0, 5, 'M') + readIntValue(message, 0, 7, 'M');
		  Memory.Swap_Total = readIntValue(message, 0, 8, 'M');
		  Memory.Swap_Used = readIntValue(message, 0, 9, 'M');
		  Memory.Swap_Free = readIntValue(message, 0, 10, 'M');
		  Memory.Memory_Total = readIntValue(message, 0, 11, 'M');
		  Memory.Memory_Used = readIntValue(message, 0, 12, 'M');
		  Memory.Memory_Free = readIntValue(message, 0, 13, 'M');

		  //PRINT FOR DEBUG
		  #ifdef DEBUGMEMORY
		  ROS_INFO("Memory Physical Total     :  %iM", Memory.Physical_Memory_Total);
		  ROS_INFO("Memory Physical Used      :  %iM", Memory.Physical_Memory_Used);
		  ROS_INFO("Memory Physical Free      :  %iM", Memory.Physical_Memory_Free);
		  ROS_INFO("Memory Swap Total         :  %iM", Memory.Swap_Total);
		  ROS_INFO("Memory Swap Used          :  %iM", Memory.Swap_Used);
		  ROS_INFO("Memory Swap Free          :  %iM", Memory.Swap_Free);
		  ROS_INFO("Memory Total              :  %iM", Memory.Memory_Total);
		  ROS_INFO("Memory Used               :  %iM", Memory.Memory_Used);
		  ROS_INFO("Memory Free               :  %iM", Memory.Memory_Free);
		  ROS_INFO("-------------------------------------------------------------------------");
		  #endif
		  //updateMemory((100.0 * Memory.Physical_Memory_Used / Memory.Physical_Memory_Total));
		}
*/
}




float CThreadDiagnostics::readFloatValue(std::string theString){
	int iDiv = 1;
	int iReadingLoop = 0;
	float fRetReadingValue = 0;
	//read all numbers before dot or comma
	while (theString[iReadingLoop] >= '0' && theString[iReadingLoop] <= '9'){
		fRetReadingValue = fRetReadingValue*10 + theString[iReadingLoop] - '0';
		iReadingLoop ++;
	}
	//if it is a dot or a comma
	if(theString[iReadingLoop] == '.' || theString[iReadingLoop] == ','){
		//continue to decimal
		iReadingLoop ++;
	}else{
		//else stop an return value
		return fRetReadingValue;
	}
	//read all numbers before end
	while (theString[iReadingLoop] >= '0' && theString[iReadingLoop] <= '9'){
		fRetReadingValue = fRetReadingValue*10 + theString[iReadingLoop] - '0';
		iDiv *= 10;
		iReadingLoop ++;
	}
	//return value
	return fRetReadingValue / iDiv;
}

int CThreadDiagnostics::readIntValue(std::string theString){
	int iRetReadingValue = 0;
	int iLoop = 0;
	while(theString[iLoop] >= '0' && theString[iLoop] <= '9'){
		iRetReadingValue = iRetReadingValue * 10 + theString[iLoop] - '0';
		iLoop ++;
	}
	return iRetReadingValue;
}
