#include "mainwindow.h"
#include <QApplication>
#include <QThread>

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "SARA_QT_USER_INTERFACE");

    ROS_INFO("Part");

    QApplication a(argc, argv);
    MainWindow w;

    w.show();

    return a.exec();
}
