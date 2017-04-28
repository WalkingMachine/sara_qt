#ifndef CTHREADDIAGNOSTICS_H
#define CTHREADDIAGNOSTICS_H

#include <QThread>
#include <QString>
#include <ros/ros.h>
#include <diagnostic_msgs/DiagnosticStatus.h>
#include <diagnostic_msgs/DiagnosticArray.h>

#include "monitors.h"

//FOR DEBUG:
#define DEBUGCPU
#define DEBUGMEMORY

//Structure représentant un CPU
typedef struct CPU_STRUC{
	float * pCPUCoresUsage;
	int enrNumberOfCore;
}CPU_TYPE;

//Structure de la memoire
typedef struct MEMORY_STRUCT{
	int Physical_Memory_Total;
	int Physical_Memory_Used;
	int Physical_Memory_Free;
	int Swap_Total;
	int Swap_Used;
	int Swap_Free;
	int Memory_Total;
	int Memory_Used;
	int Memory_Free;
}MEMORY_TYPE;


class CThreadDiagnostics: public QThread
{
	Q_OBJECT

public:
	~CThreadDiagnostics();

public slots:
	void subscribeSlot();
	void unsubscribeSlot();

protected:
	void run();

private:
	ros::NodeHandle nh;
	ros::Subscriber subscriber;
	CPU_TYPE CPU;
	MEMORY_TYPE Memory;
	bool bThreadRun;
	bool bIsSubscribe;
	void callbackMessageReceived(const diagnostic_msgs::DiagnosticArray &message);
	//for ros diagnostics data reading
	float readFloatValue(std::string theString);
	int readIntValue(std::string theString);


signals:
	void updateCPU(CPU_TYPE *CPU);
	void updateMemory(float iMemoryUsage);

};
#endif // CTHREADTOPICSSUBSCRIBER_H
