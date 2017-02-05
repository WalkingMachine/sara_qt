#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "hello_ros");
    ros::NodeHandle nh;

    QApplication a(argc, argv);
    MainWindow w;

    w.show();

    return a.exec();
}
