#include "mainwindow.h"
#include "ui_mainwindow.h"

/**
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);
	ROS_INFO("UI on");
	InitScenarios();
	ui->scenatioTree->setSortingEnabled(true);
}

/**
 * @brief MainWindow::setProduction
 * settings for production
 */
void MainWindow::setProduction() {
	this->showFullScreen();
	this->setCursor(Qt::BlankCursor);
	ui->mainTab->setCurrentIndex(0);
}

/**
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow() {
	ROS_INFO("UI off");
	std::raise(SIGTERM);
	delete ui;
}

/**
 * Update CPU diagnostics on UI. Set number of progress bar in function of number of monitored cores.
 * @brief MainWindow::updateCPU
 * @param CPU
 *
 */
void MainWindow::updateCPU(CPU_TYPE *CPU) {
	static int numberOfCores = 0;
	if (CPU->pCPUCoresUsage != NULL) {
		if (numberOfCores != CPU->enrNumberOfCore) {
			numberOfCores = CPU->enrNumberOfCore;
			generateCPU_Usage_Box(numberOfCores);
		}
		
		if (CPU->enrNumberOfCore > 0) {
			for (int iLoop = 0; iLoop < CPU->enrNumberOfCore; iLoop++) {
				CPU_Usage_Bars[iLoop]->setValue(CPU->pCPUCoresUsage[iLoop]);
			}
		}
	}
}

/**
 * Generate a QT widget containing all CPU cores usage ProgressBar
 * @brief MainWindow::generateCPU_Usage_Box
 * @param numberOfCores
 */
void MainWindow::generateCPU_Usage_Box(int numberOfCores) {
	QHBoxLayout *newLayout = new QHBoxLayout();    //generate new master cpu usage layout
	QVBoxLayout *new1Layout = new QVBoxLayout();    //generate new 1st cpu usage layout
	QVBoxLayout *new2Layout = new QVBoxLayout();    //generate new 2nd cpu usage layout
	QVBoxLayout *new3Layout = new QVBoxLayout();    //generate new 3rd cpu usage layout
	QVBoxLayout *new4Layout = new QVBoxLayout();    //generate new 4th cpu usage layout
	
	//link 1st cpu usage layout in  master cpu usage layout
	newLayout->addLayout(new1Layout);
	//link 2nd cpu usage layout in  master cpu usage layout
	newLayout->addLayout(new2Layout);
	//link 3rd cpu usage layout in  master cpu usage layout
	newLayout->addLayout(new3Layout);
	//link 4th cpu usage layout in  master cpu usage layout
	newLayout->addLayout(new4Layout);
	
	//link with new layout
	if (ui->CPU_u->layout()) {
		delete ui->CPU_u->layout();
	}
	ui->CPU_u->setLayout(newLayout);
	
	//allocate new size for number of cores
	CPU_Usage_Bars = new QProgressBar *[numberOfCores];
	
	//generate all progress bars
	for (int iLoop = 0; iLoop < numberOfCores; iLoop++) {
		//allocate progress bar
		CPU_Usage_Bars[iLoop] = new QProgressBar();
		if (iLoop < numberOfCores / 4) {
			//add first half in left layout
			new1Layout->addWidget(CPU_Usage_Bars[iLoop]);
		} else if (iLoop < numberOfCores / 2) {
			//add second half in left layout
			new2Layout->addWidget(CPU_Usage_Bars[iLoop]);
		} else if (iLoop < numberOfCores * 3 / 4) {
			//add second half in left layout
			new3Layout->addWidget(CPU_Usage_Bars[iLoop]);
		} else {
			//add second half in left layout
			new4Layout->addWidget(CPU_Usage_Bars[iLoop]);
		}
	}
	
	//update ox title
	ui->CPU_u->setTitle("CPU Usage (" + QString::number(numberOfCores) + " cores)");
}

/**
 * Update memory usage ProgressBar and Values in the name of the group
 * @brief MainWindow::updateMemory
 * @param Memory
 */
void MainWindow::updateMemory(MEMORY_TYPE *Memory) {
	QString newTitle =
			"Memory (" + QString::number(Memory->Memory_Used) + "M/" + QString::number(Memory->Memory_Total) +
			"M) | Swap (" + QString::number(Memory->Swap_Used) + "M/" + QString::number(Memory->Swap_Total) + "M)";
	ui->Memory->setTitle(newTitle);
	ui->Memory_bar->setValue(Memory->Memory_Usage);
	ui->Swap_bar->setValue(Memory->Swap_Usage);
}

/**
 * Generate a table containing all temperatures sensors and thoses values
 * @brief MainWindow::updateTemperatureSensors
 * @param Temperature_Sensors
 */
void MainWindow::updateTemperatureSensors(TEMPERATURE_SENSORS_TYPE *Temperature_Sensors) {
	if (Temperature_Sensors != NULL) {
		ui->listWidget->clear();
		for (std::vector<SENSOR_TYPE>::const_iterator Sensor = Temperature_Sensors->enrCpuSensors.begin();
		     Sensor != Temperature_Sensors->enrCpuSensors.end(); ++Sensor) {
			new QListWidgetItem(Sensor->strName + ": " + Sensor->strValue + "°C", ui->listWidget);
		}
		for (std::vector<SENSOR_TYPE>::const_iterator Sensor = Temperature_Sensors->enrSensors.begin();
		     Sensor != Temperature_Sensors->enrSensors.end(); ++Sensor) {
			new QListWidgetItem(Sensor->strName + ": " + Sensor->strValue, ui->listWidget);
		}
	}
}

void MainWindow::on_pushButton_clicked() {
	this->~MainWindow();
}

/**
 * Initialise scenarios page
 * @brief MainWindow::InitScenarios
 */
void MainWindow::InitScenarios() {
	if (!_Scenarios.getFilePath().isEmpty()) {
		ui->scenatioTree->clear();
		
		if (_Scenarios.getNumberOfScenarios() > 0) {
			int iIndex = 0;
			for (QList<CScenario>::iterator Scenario = _Scenarios._Scenarios.begin();
			     Scenario != _Scenarios._Scenarios.end(); Scenario++) {
				QTreeWidgetItem *item = new QTreeWidgetItem();
				
				item->setText(0, Scenario->getName());
				item->setData(0, Qt::UserRole, qVariantFromValue((void *) &_Scenarios._Scenarios[iIndex]));
				
				item->setData(1, Qt::EditRole, Scenario->getNumberOfUse());
				item->setData(1, Qt::DisplayRole, QString().number(Scenario->getNumberOfUse()));
				
				item->setText(2, Scenario->getCommand());
				
				ui->scenatioTree->insertTopLevelItem(iIndex, item);
				iIndex++;
			}
		}
		
		if (_Scenarios.getNumberOfScenarios() < 2) {
			ui->Scenario_Path->setText(
					_Scenarios.getFilePath() + " - " + QString::number(_Scenarios.getNumberOfScenarios()) +
					" Scenario");
		} else {
			ui->Scenario_Path->setText(
					_Scenarios.getFilePath() + " - " + QString::number(_Scenarios.getNumberOfScenarios()) +
					" Scenarios");
		}
	} else {
		ui->Scenario_Path->setText(QString("No Scenarios File loaded."));
	}
}

/**
 * @brief MainWindow::on_chooseFileButton_clicked
 * Handler for choose a scenario file.
 */
void MainWindow::on_chooseFileButton_clicked() {
	QString newPath = QFileDialog::getOpenFileName(this, tr("Select Scenarios file"), QDir::homePath(),
	                                               tr("Scenarios file (*.scenario) ;; All files (*.*)"));
	if (!newPath.isEmpty()) {
		if (!QFile::exists(newPath)) {
			QMessageBox(QMessageBox::Information, "File Error", "The selected file do not exist!",
			            QMessageBox::Close).exec();
		} else if (!CScenarios::isReadableFile(newPath)) {
			QMessageBox(QMessageBox::Information, "File Error", "The selected file is not in a readable format (YAML)!",
			            QMessageBox::Close).exec();
		} else {
			_Scenarios.setFilePath(newPath);
			InitScenarios();
		}
	}
}

void MainWindow::on_launchScenarioBT_clicked() {
	if (!ui->scenatioTree->selectedItems().isEmpty()) {
		CScenario *selectedScenario = (CScenario *) ui->scenatioTree->selectedItems()[0]->data(0,
		                                                                                       Qt::UserRole).value<void *>();
		_Scenarios.RunScenario(selectedScenario);
		ui->scenatioTree->selectedItems()[0]->setData(1, Qt::EditRole, selectedScenario->getNumberOfUse());
		ui->scenatioTree->selectedItems()[0]->setData(1, Qt::DisplayRole,
		                                              QString().number(selectedScenario->getNumberOfUse()));
	}
}

void MainWindow::addLog(QString newLog){
    ui->logText->append("<b>" + QDateTime::currentDateTime().toString("HH:mm:ss.zzz") + ": </b>" + newLog);
}
