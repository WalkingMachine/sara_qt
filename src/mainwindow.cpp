#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent):
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	ROS_INFO("UI on");
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::updateCPU(CPU_TYPE *CPU){
	static int numberOfCores = 0;
	if(CPU->pCPUCoresUsage!=NULL){
		if(numberOfCores != CPU->enrNumberOfCore){
			numberOfCores = CPU->enrNumberOfCore;
			QString newTitle = "CPU ("+ QString::number(CPU->enrNumberOfCore) +" cores)";
			ui->CPU->setTitle(newTitle);
		}

		switch (CPU->enrNumberOfCore) {
		case 8:
			ui->Core7_bar->setValue(CPU->pCPUCoresUsage[7]);
		case 7:
			ui->Core6_bar->setValue(CPU->pCPUCoresUsage[6]);
		case 6:
			ui->Core5_bar->setValue(CPU->pCPUCoresUsage[5]);
		case 5:
			ui->Core4_bar->setValue(CPU->pCPUCoresUsage[4]);
		case 4:
			ui->Core3_bar->setValue(CPU->pCPUCoresUsage[3]);
		case 3:
			ui->Core2_bar->setValue(CPU->pCPUCoresUsage[2]);
		case 2:
			ui->Core1_bar->setValue(CPU->pCPUCoresUsage[1]);
		case 1:
			ui->Core0_bar->setValue(CPU->pCPUCoresUsage[0]);
			break;
		default:
			break;
		}
	}
}

void MainWindow::updateMemory(float iMemoryUsage){
	ui->Memory_bar->setValue(iMemoryUsage*100);
}
