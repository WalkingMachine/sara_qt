#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ros::init(argc, argv,"publish_velocity");
    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel",0);
    geometry_msgs::Twist msg;

    msg.linear.x=-1.0;
    while(!ros::ok());
    if(ros::ok()){
        pub.publish(msg);
    }

    MainWindow w;
    w.show();

    return a.exec();
}
