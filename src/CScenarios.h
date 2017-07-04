#ifndef CSCENARIOS_H
#define CSCENARIOS_H

#include <ros/ros.h>
#include <sara_ui/sara_launch.h>

#include <yaml-cpp/yaml.h>
#include <vector>
#include <string>
#include <fstream>

#include "CScenario.h"
#include "helper.h"

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QTableWidget>

class CScenarios {
public:
	explicit CScenarios(QObject *parent = 0);
	
	static bool isReadableFile(QString strFileLocation);
	
	//for Scenarios
	void ReloadScenarios();
	
	void PrintScenarios();
	
	void RunScenario(CScenario *scenario);
	
	void StopScenario();
	
	int getNumberOfScenarios();
	
	QList<CScenario> _Scenarios;
	
	//for file management:
	QString getFilePath();
	
	void setFilePath(QString scenariosFilePath);
	
	bool FileExist();
	
	void CreateNewFile();

private:
	QString _scenariosFilePath;
	bool _fileExist;
	
	void UpdatePathFromSave(void);
	
	ros::NodeHandle _nh;
	ros::Publisher _command_publisher;

signals:

public slots:
};

#endif // CSCENARIOS_H
