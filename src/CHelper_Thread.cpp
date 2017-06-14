//
// Created by lucas on 5/22/17.
//

#include "CHelper_Thread.h"

void CHelper_Thread::run() {
	if (!_strCommand.empty()) {
		for (int iLoop = 0; iLoop < 50; iLoop++) {
			system(_strCommand.c_str());
			sleep(1);
		}
	}
}

void CHelper_Thread::runCommand() {

}

void CHelper_Thread::setCommand(std::string command) {
	_strCommand = command;
}

