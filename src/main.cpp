#include <QApplication>

#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "CThreadDiagnostics.h"

int main(int argc, char *argv[]) {
	ros::init(argc, argv, "SARA_QT_USER_INTERFACE");
	ROS_INFO("Part");
	
	//Declaring objetcs
	CThreadDiagnostics Thread;

	QApplication a(argc, argv);
	MainWindow Window;
	
	//Setting Fullscreen and other stufs if it is not debbuging
	if (!QCoreApplication::arguments().contains("--debug")) {
		Window.setProduction();
	} else {
		//Scenarios.PrintScenarios();
	}
	
	//Setting signals/slots connections for diagnostics over ROS topics
    QObject::connect(&Thread, SIGNAL(addLog(QString)), &Window, SLOT(addLog(QString)));
    QObject::connect(&Thread, SIGNAL(updateCPU(CPU_TYPE * )), &Window, SLOT(updateCPU(CPU_TYPE * )));
	QObject::connect(&Thread, SIGNAL(updateMemory(MEMORY_TYPE * )), &Window, SLOT(updateMemory(MEMORY_TYPE * )));
	QObject::connect(&Thread, SIGNAL(updateTemperatureSensors(TEMPERATURE_SENSORS_TYPE * )), &Window,
	                 SLOT(updateTemperatureSensors(TEMPERATURE_SENSORS_TYPE * )));
	
	//Run Threads and UIs
	Thread.start();    //thread for diagnostics reading over Diagnostics topic
	Window.show();        //main windows UI
	
	return a.exec();
}
