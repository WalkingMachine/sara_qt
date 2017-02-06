#include <QApplication>
#include "mainwindow.h"
#include "cthreadtopicssubscriber.h"

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "SARA_QT_USER_INTERFACE");
    ROS_INFO("Part");

    //Declaring objetcs
    CThreadTopicsSubscriber Thread;
    QApplication a(argc, argv);
    MainWindow Window;

    //Setting signals/slots connections
    QObject::connect(&Window, SIGNAL(subscribeSignal(QString)),     &Thread, SLOT(subscribeSlot(QString)));
    QObject::connect(&Window, SIGNAL(unsubscribeSignal()),          &Thread, SLOT(unsubscribeSlot()));
    QObject::connect(&Thread, SIGNAL(newMessageReceivedSignal(QString)),   &Window, SLOT(newMessageReceivedSlot(QString)));

    //Run Threads and UIs
    Thread.start();
    Window.show();

    return a.exec();
}
