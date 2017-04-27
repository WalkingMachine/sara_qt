#include "helper.h"

volatile bool bEndScript = false;

int main(int argc, char *argv[]){
    //create safe exit handler (on signal SIGTERM)
    struct sigaction action;
    memset(&action, 0, sizeof(struct sigaction));
    action.sa_handler = term;
    sigaction(SIGINT, &action, NULL);
    sigaction(SIGTERM, &action, NULL);


	int     i = 0;                  //
	int     iNumberOfCore = 0;      // number of core of the CPU
	float   fCPU_Usage;             //
	float   fCPU_Core_Usage[10];    // actual usage of each CPU's core
	bool    bRun = true;            //
	printf("Run. \n");

	//Create and launch CPU usage refresh thread
	std::thread CPURefreshThread(refreshCPUdata, &fCPU_Usage, fCPU_Core_Usage, &iNumberOfCore, &bRun);


	for(int iLoopTest = 0; iLoopTest<100; iLoopTest++) {
		usleep(500000);
		//waiting for full data reading for CPU
		if(iNumberOfCore){


			//just for debug
			printf("----------%i----------\n", i); i++;
			printf("there is %i core(s). \n", iNumberOfCore);
			printf("Total  : %f \n", fCPU_Usage);
			for (int iLoop = 0; iLoop < iNumberOfCore; iLoop++) {
				printf("Core %i : %f \n", iLoop, fCPU_Core_Usage[iLoop]);
			}
		}
		if(bEndScript)break;
	}

	bRun = false;
	CPURefreshThread.join();
	printf("Stop. \n");
}
