#ifndef CSCENARIO_H
#define CSCENARIO_H

#include <ros/ros.h>

#include <QString>
#include <QTreeWidgetItem>
#include <stdexcept>      // std::invalid_argument

class CScenario{

public:
	CScenario(QString strName, QString strCommand);
	CScenario(QString strName, QString strCommand, int iNumberOfUse);
	void setName(QString strName);
	void setCommand(QString strCommand);
	void setNumberOfUse(int iNumberOfUse);
	QString getName();
	QString getCommand();
	int getNumberOfUse();
	void newUtilisation();
	void printScenario();

private:
	QString _strName;
	QString _strCommand;
	int _iNumberOfUse;
};

#endif // CSCENARIO_H
