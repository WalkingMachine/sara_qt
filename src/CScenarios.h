#ifndef CSCENARIOS_H
#define CSCENARIOS_H

#include <ros/ros.h>
#include <yaml-cpp/yaml.h>

#include <QObject>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDir>


class CScenarios : public QObject
{
	Q_OBJECT
public:
	explicit CScenarios(QObject *parent = 0);
	void CreateNewFile();
	bool FileExist();

private:
	QString _scenariosFilePath;
	bool _fileExist;
	void UpdatePathFromSave(void);
	void ReloadScenarios(void);


signals:

public slots:
};

#endif // CSCENARIOS_H
