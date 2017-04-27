#include "helper.h"

//float readFloatAtIndex(char* theString, int iIndex);
//void refreshCPUdata(float *fCPU_Usage, float *fCpuCoresUsage, int *iNumberOfCore, bool *bRun);

int main(){
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
			printf("Total  : %f\%\n", fCPU_Usage);
			for (int iLoop = 0; iLoop < iNumberOfCore; iLoop++) {
				printf("Core %i : %f\% \n", iLoop, fCPU_Core_Usage[iLoop]);
			}


		}
	}

	bRun = false;
	CPURefreshThread.join();
	printf("Stop. \n");
}
