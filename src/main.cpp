#include <QApplication>
#include "mainwindow.h"
#include "CThreadDiagnostics.h"

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "SARA_QT_USER_INTERFACE");
    ROS_INFO("Part");

    //Declaring objetcs
    CThreadDiagnostics Thread;
    QApplication a(argc, argv);
    MainWindow Window;

    //Setting signals/slots connections
    QObject::connect(&Window, SIGNAL(subscribeSignal()),    &Thread, SLOT(subscribeSlot()));
    QObject::connect(&Window, SIGNAL(unsubscribeSignal()),  &Thread, SLOT(unsubscribeSlot()));
    QObject::connect(&Thread, SIGNAL(updateCPU(int,int,int,int)),   &Window, SLOT(updateCPU(int,int,int,int)));
    QObject::connect(&Thread, SIGNAL(updateMemory(int)),   &Window, SLOT(updateMemory(int)));

    //Run Threads and UIs
    Thread.start();
    Window.show();

    return a.exec();
}
