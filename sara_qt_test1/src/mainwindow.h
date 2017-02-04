#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <stdlib.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void goForward();
    void goBackward();

private:
    Ui::MainWindow *ui;
    geometry_msgs::Twist msg;

};

#endif // MAINWINDOW_H
