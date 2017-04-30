/**
    Sara_UI
    helper.h
    Purpose: Publisher for a few system values for ui print in our robot

    @author:	Lucas Maurice
	 @contact:	lucas.maurice@outlook.com
    @version:	1.0 28/04/17
*/

#ifndef HELPER_H
#define HELPER_H

//includes files
#include <stdio.h>
#include <unistd.h>
#include <thread>
#include <string.h>
#include <math.h>


#include <time.h>

//includes for ROS messages
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Header.h>
#include <sstream>

//includes for diagnostics
#include <diagnostic_msgs/DiagnosticStatus.h>
#include <diagnostic_msgs/DiagnosticArray.h>

//define compilation consts
#define BUFFER 1000
#define FIRST_CPU_LINE 3
#define IDLE_INDEX 12//91 //SYS:35 USR:19 IDLE:91
#define FLOAT_CAR_SIZE 10
#define INT_CAR_SIZE 10
#define NUM_MAX_CORES 10
#define HARDWARE_ID "MAIN_COMPUTER"

//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------- TYPES DECLARATIONS ---------------------------------------------
//--------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
//	Struct for the CPU usage
//		@members	char strCPU_Usage[]									: String containing total CPU usage
//					char strTabCPU_Cores_Usage[][FLOAT_CAR_SIZE]	: Strings array containing CPU usage, core by core
//					int iNumberOfCore										: Number of cores
typedef struct{
	char strCPU_Usage[FLOAT_CAR_SIZE];
	char strTabCPU_Cores_Usage[NUM_MAX_CORES][FLOAT_CAR_SIZE];
	int iNumberOfCore;
}Type_CPU;
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
//	Struct for an usage value (with a total capacity and an actually used capacity)
//		@members		char strTotal[INT_CAR_SIZE]	: string integer for the total capacity of the usage
//						char strUsed[INT_CAR_SIZE]		: string integer for the actually in use capacity of the usage
typedef struct{
	char strTotal[INT_CAR_SIZE];
	char strUsed[INT_CAR_SIZE];
}Type_Usage;
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
//	Struct for the Temperature usage
//		@members	char strCPU_Usage[]									: String containing total CPU usage
//					char strTabCPU_Cores_Usage[][FLOAT_CAR_SIZE]	: Strings array containing CPU usage, core by core
//					int iNumberOfCore										: Number of cores
typedef struct{
	std::vector<diagnostic_msgs::KeyValue> valuesVector;
	int iNumberOfSensors;
}Type_Temperature;
//------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------------------
//-------------------------------------------- FUNCTIONS PROTOTYPES --------------------------------------------
//--------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
//	Function of the thread that will read CPU usage.
//		@param	Type_CPU *CPU_data	: pointer to the CPU data
//					bool *bRun				: pointer to the running flag
//		@return	nothing
void refreshCPUdata(Type_CPU *CPU_data, const bool *bRun);
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
//	Function of the thread that will read CPU usage.
//		@param	Type_Usage *enrMemory	: pointer to the memory data
//					Type_Usage *enrSwap		: pointer to the swap data
//					bool *bRun					: pointer to the running flag
//		@return	nothing
void refreshMemoryData(Type_Usage *enrMemory, Type_Usage *enrSwap, const bool *bRun);
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
//	Function of the thread that will read CPU usage.
//		@param	Type_Usage *enrMemory	: pointer to the memory data
//					Type_Usage *enrSwap		: pointer to the swap data
//					bool *bRun					: pointer to the running flag
//		@return	nothing
void refreshTemperatureData(Type_Temperature *temperatureValues, const bool *bRun);
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
//	Read the last string part of a string with specified charactere separator.
//	Assuming than the first string end by a \0 or a \n.
//		@param	char *theLine		: input string
//					char theResult[]	: output string
//					int iSizeResult	: size of the output string
//					char cSeparator	: separator charactere
//		@return	nothing
void readLastValue(char *theLine, char theResult[], int iSizeResult, char cSeparator);
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
//	Read the last string part of a string with specified charactere separator.
//	Assuming than the first string end by a \0 or a \n.
//		@param	char *theLine			: input string
//					Type_Usage *enrUsage	: pointer to the memory usage
//		@return	nothing
void readMemoryUsageValues(char *theLine, Type_Usage *enrUsage);
//------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------------------
//----------------------------------------- FUNCTIONS FOR PUBLISH DATA -----------------------------------------
//--------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
//	Generate a standard header for ros topic publisher
//		@param	int iSeq				: sequence number for verifications
//		@return	std_msgs::Header	: return the header
std_msgs::Header header_generate(int iSeq);
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
//	Generate a diagnostics status for diagnostics publishers
//		@param	std::string strName												: Name of the status
//					std::string strMessage											: Message of the status
//					std::string strHardwareID										: Harware identifier
//					char level															: Level of operation
//					std::vector<diagnostic_msgs::KeyValue> valuesVector	: Vector of data
//		@return	diagnostic_msgs::DiagnosticStatus							: return the status
diagnostic_msgs::DiagnosticStatus status_generate(std::string strName, std::string strMessage, std::string strHardwareID, char level, std::vector<diagnostic_msgs::KeyValue> valuesVector);
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
//	Generate the status of CPU data for publisher
//		@param	Type_CPU *CPU_data						: pointer to the CPU data
//		@return	diagnostic_msgs::DiagnosticStatus	: return the status
diagnostic_msgs::DiagnosticStatus CPUPublisher(Type_CPU *CPU_data);
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
//	Generate the status of Memory data for publisher
//		@param	Type_Usage *enrMemory					: pointer to the memory data
//					Type_Usage *enrSwap						: pointer to the swap data
//		@return	diagnostic_msgs::DiagnosticStatus	: return the status
diagnostic_msgs::DiagnosticStatus MemoryPublisher(Type_Usage *enrMemory, Type_Usage *enrSwap);
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
//	Generate the status of Memory data for publisher
//		@param	Type_Usage *enrMemory					: pointer to the memory data
//					Type_Usage *enrSwap						: pointer to the swap data
//		@return	diagnostic_msgs::DiagnosticStatus	: return the status
diagnostic_msgs::DiagnosticStatus TemperaturePublisher(Type_Temperature *temperatureValues);
//------------------------------------------------------------------------------------------

#endif
