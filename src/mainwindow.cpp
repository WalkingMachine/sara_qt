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
			generateCPU_Usage_Box(numberOfCores);
		}

		if(CPU->enrNumberOfCore > 0){
			for(int iLoop = 0; iLoop < CPU->enrNumberOfCore; iLoop++){
				CPU_Usage_Bars[iLoop]->setValue(CPU->pCPUCoresUsage[iLoop]);
			}
		}
	}
}

void MainWindow::generateCPU_Usage_Box(int numberOfCores){
	QHBoxLayout *newLayout = new QHBoxLayout();	//generate new master cpu usage layout
	QVBoxLayout *newLLayout = new QVBoxLayout();	//generate new left cpu usage layout
	QVBoxLayout *newRLayout = new QVBoxLayout();	//generate new right cpu usage layout

	//link left cpu usage layout in  master cpu usage layout
	newLayout->addLayout(newLLayout);
	//link right cpu usage layout in  master cpu usage layout
	newLayout->addLayout(newRLayout);

	//link with new layout
	ui->CPU_u->setLayout(newLayout);

	//allocate new size for number of cores
	CPU_Usage_Bars = new QProgressBar*[numberOfCores];

	//generate all progress bars
	for(int iLoop = 0; iLoop < numberOfCores; iLoop++){
		//allocate progress bar
		CPU_Usage_Bars[iLoop] = new QProgressBar();
		if(iLoop<numberOfCores/2){
			//add first half in left layout
			newLLayout->addWidget(CPU_Usage_Bars[iLoop]);
		}else{
			//add second half in left layout
			newRLayout->addWidget(CPU_Usage_Bars[iLoop]);
		}
	}

	//update ox title
	ui->CPU_u->setTitle("CPU Usage ("+ QString::number(numberOfCores) +" cores)");
}

void MainWindow::updateMemory(MEMORY_TYPE *Memory){
	QString newTitle = "Memory (" + QString::number(Memory->Memory_Used) + "M/" + QString::number(Memory->Memory_Total)+ "M) | Swap (" + QString::number(Memory->Swap_Used) + "M/" + QString::number(Memory->Swap_Total)+ "M)";
	ui->Memory->setTitle(newTitle);
	ui->Memory_bar->setValue(Memory->Memory_Usage);
	ui->Swap_bar->setValue(Memory->Swap_Usage);
}
