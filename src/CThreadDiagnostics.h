#ifndef CTHREADDIAGNOSTICS_H
#define CTHREADDIAGNOSTICS_H

#include <QThread>
#include <QString>
#include <ros/ros.h>
#include <diagnostic_aggregator/analyzer.h>
#include <diagnostic_aggregator/status_item.h>
#include <diagnostic_msgs/DiagnosticStatus.h>
#include <diagnostic_msgs/DiagnosticArray.h>

//FOR DEBUG:
#define DEBUGCPU
#define DEBUGMEMORY

#define CPU_NBR_OF_CORE 8
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
  CPU_CORE_TYPE enrCPUCore[4];
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


class CThreadDiagnostics: public QThread
{
    Q_OBJECT

public:
    ~CThreadDiagnostics();

public slots:
    void subscribeSlot();
    void unsubscribeSlot();

protected:
    void run();

private:
    ros::NodeHandle nh;
    ros::Subscriber subscriber;
    CPU_TYPE CPU;
    MEMORY_TYPE Memory;
    bool bThreadRun;
    bool bIsSubscribe;
    void callbackMessageReceived(const diagnostic_msgs::DiagnosticArray &message);
    //for ros diagnostics data reading
    float readFloatValue(const diagnostic_msgs::DiagnosticArray &message, int iStatus, int iLineNumber, char endChar);
    int readIntValue(const diagnostic_msgs::DiagnosticArray &message, int iStatus, int iLineNumber, char endChar);


signals:
    void updateCPU(float iCore0Usage, float iCore1Usage, float iCore2Usage, float iCore3Usage);
    void updateMemory(float iMemoryUsage);

};
#endif // CTHREADTOPICSSUBSCRIBER_H
