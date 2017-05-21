#include "CScenario.h"
CScenario::CScenario(QString strName, QString strCommand){
	CScenario(strName, strCommand, 0);
}

CScenario::CScenario(QString strName, QString strCommand, int iNumberOfUse){
	setName(strName);
	setCommand(strCommand);
	setNumberOfUse(iNumberOfUse);
}

void CScenario::setName(QString strName){
	if(strName.isEmpty()){
		throw std::invalid_argument("Name is Empty.");
	}
	_strName = strName;
}

void CScenario::setCommand(QString strCommand){
	if(strCommand.isEmpty()){
		throw std::invalid_argument("Command is Empty.");
	}
	_strCommand = strCommand;
}

void CScenario::setNumberOfUse(int iNumberOfUse){
	_iNumberOfUse = iNumberOfUse;
}

QString CScenario::getName(){
	return _strName;
}

QString CScenario::getCommand(){
	return _strCommand;
}

int CScenario::getNumberOfUse(){
	return _iNumberOfUse;
}





void CScenario::newUtilisation(){
	_iNumberOfUse++;
}





void CScenario::printScenario(){
	ROS_INFO("Scenario %s use command \"%s\". Used %i times.", _strName.toUtf8().constData(), _strCommand.toUtf8().constData(), _iNumberOfUse);
}
