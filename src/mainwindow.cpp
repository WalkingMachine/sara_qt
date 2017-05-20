#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent):
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	ROS_INFO("UI on");
}

void MainWindow::setProduction(){
	this->showFullScreen();
	this->setCursor(Qt::BlankCursor);
	ui->mainTab->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
	ROS_INFO("UI off");
	std::raise(SIGTERM);
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
	QVBoxLayout *new1Layout = new QVBoxLayout();	//generate new 1st cpu usage layout
	QVBoxLayout *new2Layout = new QVBoxLayout();	//generate new 2nd cpu usage layout
	QVBoxLayout *new3Layout = new QVBoxLayout();	//generate new 3rd cpu usage layout
	QVBoxLayout *new4Layout = new QVBoxLayout();	//generate new 4th cpu usage layout

	//link 1st cpu usage layout in  master cpu usage layout
	newLayout->addLayout(new1Layout);
	//link 2nd cpu usage layout in  master cpu usage layout
	newLayout->addLayout(new2Layout);
	//link 3rd cpu usage layout in  master cpu usage layout
	newLayout->addLayout(new3Layout);
	//link 4th cpu usage layout in  master cpu usage layout
	newLayout->addLayout(new4Layout);

	//link with new layout
	if(ui->CPU_u->layout()){
		delete ui->CPU_u->layout();
	}
	ui->CPU_u->setLayout(newLayout);

	//allocate new size for number of cores
	CPU_Usage_Bars = new QProgressBar*[numberOfCores];

	//generate all progress bars
	for(int iLoop = 0; iLoop < numberOfCores; iLoop++){
		//allocate progress bar
		CPU_Usage_Bars[iLoop] = new QProgressBar();
		if(iLoop<numberOfCores/4){
			//add first half in left layout
			new1Layout->addWidget(CPU_Usage_Bars[iLoop]);
		}else if(iLoop<numberOfCores/2){
			//add second half in left layout
			new2Layout->addWidget(CPU_Usage_Bars[iLoop]);
		}else if(iLoop<numberOfCores*3/4){
			//add second half in left layout
			new3Layout->addWidget(CPU_Usage_Bars[iLoop]);
		}else{
			//add second half in left layout
			new4Layout->addWidget(CPU_Usage_Bars[iLoop]);
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

void MainWindow::updateTemperatureSensors(TEMPERATURE_SENSORS_TYPE *Temperature_Sensors){
	if(Temperature_Sensors != NULL){
		ui->listWidget->clear();
		for(std::vector<SENSOR_TYPE>::const_iterator Sensor = Temperature_Sensors->enrCpuSensors.begin(); Sensor != Temperature_Sensors->enrCpuSensors.end(); ++Sensor){
			new QListWidgetItem(Sensor->strName + ": " + Sensor->strValue + "°C", ui->listWidget);
		}
		for(std::vector<SENSOR_TYPE>::const_iterator Sensor = Temperature_Sensors->enrSensors.begin(); Sensor != Temperature_Sensors->enrSensors.end(); ++Sensor){
			new QListWidgetItem(Sensor->strName + ": " + Sensor->strValue, ui->listWidget);
		}
	}
}

void MainWindow::on_pushButton_clicked()
{
//	 delete this;
	this->~MainWindow();
}
