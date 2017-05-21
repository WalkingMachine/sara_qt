#ifndef CSCENARIOS_H
#define CSCENARIOS_H

#include <ros/ros.h>
#include <yaml-cpp/yaml.h>
#include <vector>
#include <string>

#include "CScenario.h"

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QTableWidget>

class CScenarios
{
public:
	explicit CScenarios(QObject *parent = 0);
	static bool isReadableFile(QString strFileLocation);

	//for Scenarios
	void ReloadScenarios();
	void PrintScenarios();
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


signals:

public slots:
};

#endif // CSCENARIOS_H
