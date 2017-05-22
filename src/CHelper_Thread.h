//
// Created by lucas on 5/22/17.
//

#ifndef SARA_UI_CHELPER_THREAD_H
#define SARA_UI_CHELPER_THREAD_H

#include <QThread>

#include <stdlib.h>

class CHelper_Thread : public QThread {
public:
	void run();
	
	void setCommand(std::string command);


private:
	std::string _strCommand;
	
	void runCommand();
};


#endif //SARA_UI_CHELPER_THREAD_H
