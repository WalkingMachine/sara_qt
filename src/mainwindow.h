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
#include <QDateTime>

#include <QThread>

#include "CScenarios.h"
#include "CThreadRos.h"

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
    void addLog(QString newLog);

private slots:
	void on_chooseFileButton_clicked();
    void on_launchScenarioBT_clicked();
    void on_continueBTTrue_clicked();
    void on_continueBTFalse_clicked();
    void on_quit_clicked();
    void on_powerOff_clicked();

private:
	Ui::MainWindow *ui;
	//CPU Usage Box
    QProgressBar **CPU_Usage_Bars;
    QMessageBox alertBoxLaunch;
    QMessageBox alertBoxShutdown;
	
	void generateCPU_Usage_Box(int numberOfCores);
	
	XmlRpc::XmlRpcValue topic_list;
	ros::NodeHandle NodeHandle;
	ros::Subscriber Subscribe;
	
	CScenarios _Scenarios;
	
	void InitScenarios();


signals:
	void subscribeSignal();
	void unsubscribeSignal();
    void publishContinue(bool bValue);
};

#endif // MAINWINDOW_H
