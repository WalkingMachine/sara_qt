#include <ros/ros.h>
#include <diagnostic_aggregator/analyzer.h>
#include <diagnostic_aggregator/status_item.h>
#include <diagnostic_msgs/DiagnosticStatus.h>
#include <diagnostic_msgs/DiagnosticArray.h>

/*
[ INFO] [1488949233.661324768]: 0: HDD Usage (djls_desktop)
  [ INFO] [1488951362.618096942]: 0: Update Status
  [ INFO] [1488951362.618121112]: 1: Time Since Update
  [ INFO] [1488951362.618128538]: 2: Disk Space Reading
  [ INFO] [1488951362.618140580]: 3: Disk 1 Name
  [ INFO] [1488951362.618147658]: 4: Disk 1 Size
  [ INFO] [1488951362.618154779]: 5: Disk 1 Available
  [ INFO] [1488951362.618162235]: 6: Disk 1 Use
  [ INFO] [1488951362.618172550]: 7: Disk 1 Status
  [ INFO] [1488951362.618181514]: 8: Disk 1 Mount Point
[ INFO] [1488949233.661386224]: 1: CPU Temperature (djls_desktop)
  [ INFO] [1488951412.660155747]: 0: Update Status
  [ INFO] [1488951412.660280082]: 1: Time Since Update
  [ INFO] [1488951412.660331739]: 2: Core 0 Temperature
  [ INFO] [1488951412.660355946]: 3: Core 1 Temperature
[ INFO] [1488949233.661448761]: 3: Network Usage (djls_desktop)
  [ INFO] [1488951656.703185892]: 0: Update Status
  [ INFO] [1488951656.703255300]: 1: Time Since Update
  [ INFO] [1488951656.703286974]: 2: Interface Name
  [ INFO] [1488951656.703313413]: 3: State
  [ INFO] [1488951656.703339371]: 4: Input Traffic
  [ INFO] [1488951656.703391053]: 5: Output Traffic
  [ INFO] [1488951656.703432239]: 6: MTU
  [ INFO] [1488951656.703514671]: 7: Total received MB
  [ INFO] [1488951656.703544604]: 8: Total transmitted MB
  [ INFO] [1488951656.703581726]: 9: Collisions
  [ INFO] [1488951656.703606551]: 10: Rx Errors
  [ INFO] [1488951656.703628259]: 11: Tx Errors
[ INFO] [1488949233.661481102]: 4: NTP offset from djls-desktop to ntp.ubuntu.com
*/

//FOR DEBUG:
//#define DEBUGCPU
//#define DEBUGMEMORY

#define CPU_NBR_OF_CORE 4
#define CPU_SPEED_POS 2
#define CPU_TEMP_POS 2
#define CPU_USAGE_POS 6
#define CPU_USAGE_SIZE 5
#define CPU_AVERAGE_USAGE_POS 27


//Structure représentant un coeur physique de CPU
typedef struct CPU_CORE_STRUC{
  int Clock_Speed;            //Vitesse d'horloge du coeur
  float User_Usage;           //Utilisation du coeur par l'utilisateur
  float Nice_Usage;           //Utilisation du coeur par ???
  float System_Usage;         //Utilisation du coeur par le système
  float IDLE;                 //Partie du coeur en veille
  float Core_Temperature;     //Temperature du coeur
}CPU_CORE_TYPE;

//Structure représentant un CPU
typedef struct CPU_STRUC{
  CPU_CORE_TYPE enrCPUCore[CPU_NBR_OF_CORE];
  float Average_Usage_1min;
  float Average_Usage_5min;
  float Average_Usage_15min;
}CPU_TYPE;

//Structure de la memoire
typedef struct MEMORY_STRUCT{
  int Physical_Memory_Total;
  int Physical_Memory_Used;
  int Physical_Memory_Free;
  int Swap_Total;
  int Swap_Used;
  int Swap_Free;
  int Memory_Total;
  int Memory_Used;
  int Memory_Free;
}MEMORY_TYPE;


void showNewLog(const diagnostic_msgs::DiagnosticArray &message);
float readFloatValue(const diagnostic_msgs::DiagnosticArray &message, int iStatus, int iLineNumber, char endChar);
int readIntValue(const diagnostic_msgs::DiagnosticArray &message, int iStatus, int iLineNumber, char endChar);

int main(int argc, char *argv[]){
  ros::init(argc, argv, "hello_ros");
  ros::NodeHandle nh;
  ros::Subscriber sub = nh.subscribe("diagnostics", 5, &showNewLog);
  ROS_INFO_STREAM(sub.getNumPublishers());
  ROS_INFO("Up and Running");
  ros::spin();
  return 0;
}

void showNewLog(const diagnostic_msgs::DiagnosticArray &message){
  //For CPU data Reading
  static CPU_TYPE CPU;
  static MEMORY_TYPE Memory;
  //END

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

      //Lecture de la Temperature du coeur:
      //CPU.enrCPUCore[iCoreId].Core_Temperature = readFloatValue(message, 0, CPU_TEMP_POS + iCoreId, '%');

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
}


float readFloatValue(const diagnostic_msgs::DiagnosticArray &message, int iStatus, int iLineNumber, char endChar){
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

int readIntValue(const diagnostic_msgs::DiagnosticArray &message, int iStatus, int iLineNumber, char endChar){
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
