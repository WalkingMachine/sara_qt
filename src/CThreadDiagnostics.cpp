#include "CThreadDiagnostics.h"
CThreadDiagnostics::~CThreadDiagnostics(){
    this->bThreadRun = false;
    this->exit();
}

void CThreadDiagnostics::run(){
    bThreadRun = true;
    bIsSubscribe = false;
    ROS_INFO("Thread On");
    subscribeSlot();
    while(bThreadRun){
        ros::spin();
    }
    ROS_INFO("Thread On");
}

void CThreadDiagnostics::subscribeSlot(){
    ROS_INFO("Subscript");
    if(!bIsSubscribe){
        subscriber = nh.subscribe("diagnostics", 1, &CThreadDiagnostics::callbackMessageReceived, this);
        bIsSubscribe=true;
    }
}

void CThreadDiagnostics::unsubscribeSlot(){
    if(bIsSubscribe){
        subscriber.shutdown();
        bIsSubscribe=false;
    }
}

void CThreadDiagnostics::callbackMessageReceived(const diagnostic_msgs::DiagnosticArray &message){

    //Si le status recu est un status de data sur le CPU
      if(message.status[0].name[0] == 'C' && message.status[0].name[1] == 'P' && message.status[0].name[2] == 'U'){
        //lecture des données d'utilisation du CPU pour chaque coeur
        for(int iCoreId = 0; iCoreId < CPU_NBR_OF_CORE; iCoreId ++){
          //Lecture de la frequence d'horloge du coeur
          CPU.enrCPUCore[iCoreId].Clock_Speed = readIntValue(message, 1, CPU_SPEED_POS + iCoreId, 'M');;

          //Lecture du taux d'utilisation user du coeur:
          CPU.enrCPUCore[iCoreId].User_Usage = readFloatValue(message, 1, CPU_USAGE_POS + iCoreId*CPU_USAGE_SIZE + 1, '%');

          //Lecture du taux d'utilisation nice du coeur:
          CPU.enrCPUCore[iCoreId].Nice_Usage = readFloatValue(message, 1, CPU_USAGE_POS + iCoreId*CPU_USAGE_SIZE + 2, '%');

          //Lecture du taux d'utilisation system du coeur:
          CPU.enrCPUCore[iCoreId].System_Usage = readFloatValue(message, 1, CPU_USAGE_POS + iCoreId*CPU_USAGE_SIZE + 3, '%');

          //Lecture du taux du coeur en IDLE:
          CPU.enrCPUCore[iCoreId].IDLE = readFloatValue(message, 1, CPU_USAGE_POS + iCoreId*CPU_USAGE_SIZE + 4, '%');

          //PRINT FOR DEBUG
          #ifdef DEBUGCPU
          ROS_INFO("Core %i Clk Speed        :  %i", iCoreId, CPU.enrCPUCore[iCoreId].Clock_Speed);
          ROS_INFO("Core %i User Usage       :  %.2f", iCoreId, CPU.enrCPUCore[iCoreId].User_Usage);
          ROS_INFO("Core %i Nice Usage       :  %.2f", iCoreId, CPU.enrCPUCore[iCoreId].Nice_Usage);
          ROS_INFO("Core %i System Usage     :  %.2f", iCoreId, CPU.enrCPUCore[iCoreId].System_Usage);
          ROS_INFO("Core %i IDLE             :  %.2f", iCoreId, CPU.enrCPUCore[iCoreId].IDLE);
          ROS_INFO("-------------------------------------------------------------------------");
          #endif
        }
        //Lecture des taux moyens d'utilisation de processeur
        CPU.Average_Usage_1min = readFloatValue(message, 1, CPU_AVERAGE_USAGE_POS, '%');
        CPU.Average_Usage_5min = readFloatValue(message, 1, CPU_AVERAGE_USAGE_POS + 1, '%');
        CPU.Average_Usage_15min = readFloatValue(message, 1, CPU_AVERAGE_USAGE_POS + 2, '%');

        //PRINT FOR DEBUG
        #ifdef DEBUGCPU
        ROS_INFO("CPU Average Usage 1 min   :  %.2f", CPU.Average_Usage_1min);
        ROS_INFO("CPU Average Usage 5 min   :  %.2f", CPU.Average_Usage_5min);
        ROS_INFO("CPU Average Usage 15 min  :  %.2f", CPU.Average_Usage_15min);
        ROS_INFO("-------------------------------------------------------------------------");
        #endif

      }
      else if(message.status[0].name[0] == 'M'){
        Memory.Physical_Memory_Total = readIntValue(message, 0, 3, 'M');
        Memory.Physical_Memory_Used = readIntValue(message, 0, 4, 'M');
        Memory.Physical_Memory_Free = readIntValue(message, 0, 5, 'M') + readIntValue(message, 0, 7, 'M');
        Memory.Swap_Total = readIntValue(message, 0, 8, 'M');
        Memory.Swap_Used = readIntValue(message, 0, 9, 'M');
        Memory.Swap_Free = readIntValue(message, 0, 10, 'M');
        Memory.Memory_Total = readIntValue(message, 0, 11, 'M');
        Memory.Memory_Used = readIntValue(message, 0, 12, 'M');
        Memory.Memory_Free = readIntValue(message, 0, 13, 'M');

        //PRINT FOR DEBUG
        #ifdef DEBUGMEMORY
        ROS_INFO("Memory Physical Total     :  %iM", Memory.Physical_Memory_Total);
        ROS_INFO("Memory Physical Used      :  %iM", Memory.Physical_Memory_Used);
        ROS_INFO("Memory Physical Free      :  %iM", Memory.Physical_Memory_Free);
        ROS_INFO("Memory Swap Total         :  %iM", Memory.Swap_Total);
        ROS_INFO("Memory Swap Used          :  %iM", Memory.Swap_Used);
        ROS_INFO("Memory Swap Free          :  %iM", Memory.Swap_Free);
        ROS_INFO("Memory Total              :  %iM", Memory.Memory_Total);
        ROS_INFO("Memory Used               :  %iM", Memory.Memory_Used);
        ROS_INFO("Memory Free               :  %iM", Memory.Memory_Free);
        ROS_INFO("-------------------------------------------------------------------------");
        #endif
      }
      updateCPU(CPU.enrCPUCore[0].User_Usage + CPU.enrCPUCore[0].System_Usage, CPU.enrCPUCore[1].User_Usage + CPU.enrCPUCore[1].System_Usage,CPU.enrCPUCore[2].User_Usage + CPU.enrCPUCore[2].System_Usage,CPU.enrCPUCore[3].User_Usage + CPU.enrCPUCore[3].System_Usage);
      updateMemory((100.0 * Memory.Physical_Memory_Used / Memory.Physical_Memory_Total));
}

float CThreadDiagnostics::readFloatValue(const diagnostic_msgs::DiagnosticArray &message, int iStatus, int iLineNumber, char endChar){
  int iDiv = 1;
  int iReadingLoop = 0;
  float fRetReadingValue = 0;
  while (message.status[iStatus].values[iLineNumber].value[iReadingLoop] != '.'){
    if(message.status[iStatus].values[iLineNumber].value[iReadingLoop] >= '0' && message.status[iStatus].values[iLineNumber].value[iReadingLoop] <= '9'){
      fRetReadingValue = fRetReadingValue*10 + message.status[iStatus].values[iLineNumber].value[iReadingLoop] - '0';
    }
    iReadingLoop ++;
  }
  while (message.status[iStatus].values[iLineNumber].value[iReadingLoop] != endChar){
    if(message.status[iStatus].values[iLineNumber].value[iReadingLoop] >= '0' && message.status[1].values[iLineNumber].value[iReadingLoop] <= '9'){
      fRetReadingValue = fRetReadingValue*10 + message.status[iStatus].values[iLineNumber].value[iReadingLoop] - '0';
      iDiv *= 10;
    }
    iReadingLoop ++;
  }
  return fRetReadingValue / iDiv;
}

int CThreadDiagnostics::readIntValue(const diagnostic_msgs::DiagnosticArray &message, int iStatus, int iLineNumber, char endChar){
  int iReadingLoop = 0;
  int iRetReadingValue = 0;
  while (message.status[iStatus].values[iLineNumber].value[iReadingLoop] != endChar){
    if(message.status[iStatus].values[iLineNumber].value[iReadingLoop] >= '0' && message.status[iStatus].values[iLineNumber].value[iReadingLoop] <= '9'){
      iRetReadingValue = iRetReadingValue*10 + message.status[iStatus].values[iLineNumber].value[iReadingLoop] - '0';
    }
    iReadingLoop ++;
  }
  return iRetReadingValue;
}