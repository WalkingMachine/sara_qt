#ifndef CTHREADDIAGNOSTICS_H
#define CTHREADDIAGNOSTICS_H

#include <QThread>
#include <QString>
#include <QRegExp>

#include <ros/ros.h>

#include <diagnostic_msgs/DiagnosticArray.h>
#include <std_msgs/String.h>
#include <std_msgs/Bool.h>

#define HARDWARE_ID "MAIN_COMPUTER"

//Structure représentant un CPU
typedef struct CPU_STRUC {
	float *pCPUCoresUsage;
	int enrNumberOfCore;
} CPU_TYPE;

//Structure de la memoire
typedef struct MEMORY_STRUCT {
	int Memory_Total;
	int Memory_Used;
	int Memory_Usage;
	int Swap_Total;
	int Swap_Used;
	int Swap_Usage;
} MEMORY_TYPE;


//Structure d'une valeur d'un capteur
typedef struct SENSOR_STRUCT {
	QString strName;
	QString strValue;
} SENSOR_TYPE;

//Structure des capteurs de temperature
typedef struct TEMPERATURE_SENSORS_STRUCT {
	std::vector<SENSOR_TYPE> enrCpuSensors;
	std::vector<SENSOR_TYPE> enrSensors;
} TEMPERATURE_SENSORS_TYPE;


class CThreadRos : public QThread {
Q_OBJECT

public:
    ~CThreadRos();

protected:
	void run();

private:
	ros::NodeHandle nh;
	ros::Subscriber subscriber;
    ros::Subscriber logSubscriber;
    ros::Publisher continuePublisher;
	CPU_TYPE CPU;
	MEMORY_TYPE Memory;
	TEMPERATURE_SENSORS_TYPE Temperature_Sensors;
	bool bIsSubscribe;

	void callbackMessageReceived(const diagnostic_msgs::DiagnosticArray message);
    void callbackLogReceived(const std_msgs::String message);
	void subscribeROS();
    void unsubscribeROS();

signals:
	void updateCPU(CPU_TYPE *CPU);
	void updateMemory(MEMORY_TYPE *Memory);
	void updateTemperatureSensors(TEMPERATURE_SENSORS_TYPE *Temperature_Sensors);
    void addLog(QString newLog);

public slots:
    void publishContinue(bool bMessage);
};

#endif // CTHREADTOPICSSUBSCRIBER_H
