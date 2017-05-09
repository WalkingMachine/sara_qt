#include <QApplication>
#include "mainwindow.h"
#include "CThreadDiagnostics.h"

int main(int argc, char *argv[])
{
	ros::init(argc, argv, "SARA_QT_USER_INTERFACE");
	ROS_INFO("Part");

	//Declaring objetcs
	CThreadDiagnostics Thread;
	QApplication a(argc, argv);
	MainWindow Window;
	//Setting signals/slots connections
	QObject::connect(&Window, SIGNAL(subscribeSignal()),    &Thread, SLOT(subscribeSlot()));
	QObject::connect(&Window, SIGNAL(unsubscribeSignal()),  &Thread, SLOT(unsubscribeSlot()));
	QObject::connect(&Thread, SIGNAL(updateCPU(CPU_TYPE *)),   &Window, SLOT(updateCPU(CPU_TYPE *)));
	QObject::connect(&Thread, SIGNAL(updateMemory(MEMORY_TYPE *)),   &Window, SLOT(updateMemory(MEMORY_TYPE *)));
	QObject::connect(&Thread, SIGNAL(updateTemperatureSensors(TEMPERATURE_SENSORS_TYPE *)),   &Window, SLOT(updateTemperatureSensors(TEMPERATURE_SENSORS_TYPE *)));

	if(!QCoreApplication::arguments().contains("--debug")){
		Window.showFullScreen();
	}

	//Run Threads and UIs
	Thread.start();
	Window.show();

	return a.exec();
}
