#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#define POSITION_TAB 2
#define POSITION_TOPIC_NAME 0
#define POSITION_TOPIC_TYPE 1

#include <QMainWindow>
#include <QStringListModel>
#include <QAbstractItemView>

#include <QFileDialog>
#include <QProgressBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QLabel>
#include <QSizePolicy>


#include <QThread>

#include "CScenarios.h"
#include "CThreadDiagnostics.h"

#include <ros/ros.h>
#include <csignal>


namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow {
Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	
	void setProduction();
	
	~MainWindow();

public slots:
	
	void updateCPU(CPU_TYPE *CPU);
	
	void updateMemory(MEMORY_TYPE *Memory);
	
	void updateTemperatureSensors(TEMPERATURE_SENSORS_TYPE *Temperature_Sensors);

private slots:
	
	void on_pushButton_clicked();
	
	void on_chooseFileButton_clicked();
	
	void on_launchScenarioBT_clicked();
	
	void on_stopScenarioBT_clicked();

private:
	Ui::MainWindow *ui;
	//CPU Usage Box
	QProgressBar **CPU_Usage_Bars;
	
	void generateCPU_Usage_Box(int numberOfCores);
	
	XmlRpc::XmlRpcValue topic_list;
	ros::NodeHandle NodeHandle;
	ros::Subscriber Subscribe;
	
	CScenarios _Scenarios;
	
	void InitScenarios();

signals:
	
	void subscribeSignal();
	
	void unsubscribeSignal();
	
};

#endif // MAINWINDOW_H
