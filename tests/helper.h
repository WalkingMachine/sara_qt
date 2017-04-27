#ifndef HELPER_H
#define HELPER_H

//includes files
#include <stdio.h>
#include <unistd.h>
#include <thread>
#include <string.h>
#include <math.h>
#include <signal.h>

//includes for ROS messages
#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>

//define compilation consts
#define BUFFER 1000
#define FIRST_CPU_LINE 3
#define IDLE_INDEX 12//91 //SYS:35 USR:19 IDLE:91

//functions prototypes
void term(int signum);
float readFloatAtIndex(char* theString, int iIndex);
void refreshCPUdata(float *fCPU_Usage, float *fCpuCoresUsage, int *iNumberOfCore, bool *bRun);

#endif
