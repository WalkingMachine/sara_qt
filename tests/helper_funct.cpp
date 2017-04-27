#include "tests/helper.h"

//extern bool   bEndScript;

void term(int signum){
//    bEndScript = true;
}

/*void refreshCPUdata(float *fCPU_Usage, float *fCpuCoresUsage, int *iNumberOfCore, bool *bRun){
    char buffer[BUFFER];    //reading buffer for command execution
    FILE * f;               //link to terminal
    printf("Loop. \n");
    int iNumber = 0;
    while(*bRun){
        //get current cpu usage via mpstat linux command
        f = popen( "mpstat -P ALL 1 1", "r" );
        iNumber = 0;

        //if not able to run command
        if ( f == 0 ) {
            fprintf( stderr, "Could not execute\n" );
        }else{
            //go to first usefull line
            for(int iReadingLine=0; iReadingLine<FIRST_CPU_LINE; iReadingLine++){
                fgets( buffer, BUFFER,  f );
            }
            while( fgets( buffer, BUFFER, f)) {
                if(buffer[0]=='\n') break;      //end loop when reading is done
                //if its the global usage line
                else if(buffer[13] == 'a' && buffer[14] == 'l' && buffer[15] == 'l'){
                    *fCPU_Usage = 100-readFloatAtIndex(buffer, IDLE_INDEX);                     //read the float value at the constant index for IDLE

                //else, if its a core usage line
                }else if(buffer[15] == '0' + iNumber){
                    fCpuCoresUsage[iNumber] = 100-readFloatAtIndex(buffer, IDLE_INDEX);  //read the float value at the constant index for IDLE
                    iNumber += 1;                                                       //increment number of cores

                }
            }
            //closing terminal
            pclose( f );
        }
        *iNumberOfCore = iNumber;
    }
    printf("End Loop. \n");
}*/

float readFloatAtIndex(char* theString, int iIndex){
    int iPosition;
    float fRetValue;
    int iIntegerValue;
    char * value;
    char * nextvalue;

    //reading last value in line (separated by spaces " ")
    nextvalue = strtok (theString," ");
    while (nextvalue != NULL)
    {
      value = nextvalue;
      nextvalue = strtok (NULL, " ");
    }

    //separating char[] before and after dot "." for float value reading.
    nextvalue = strtok (value,".");               //before dot
    value = strtok (NULL, ".");                   //after dot

    //decoding decimal value from char string
    fRetValue = 0;
    iPosition = 0;
    while(value[iPosition] >= '0' && value[iPosition] <= '9'){
      fRetValue *= 10;
      fRetValue += value[iPosition] - '0';
      iPosition ++;
    }
    fRetValue /= pow(10.0,iPosition);

    //decoding integer value from char string
    iIntegerValue = 0;
    iPosition = 0;
    while(nextvalue[iPosition] >= '0' && nextvalue[iPosition] <= '9'){
      iIntegerValue *= 10;
      iIntegerValue += nextvalue[iPosition] - '0';
      iPosition ++;
    }

    //merging both integer and decimal values
    fRetValue += iIntegerValue;
    return fRetValue;
}
