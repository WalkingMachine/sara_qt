#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QObject::connect(ui->bp_forward, SIGNAL(clicked()), this, SLOT(goForward()));
    QObject::connect(ui->bp_backward, SIGNAL(clicked()), this, SLOT(goBackward()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::goForward()
{
    msg.linear.x = 100;
    msg.linear.y = 0;
    msg.linear.z = 0;
    msg.angular.x = 0;
    msg.angular.y = 0;
    msg.angular.z = 0;
    //pub.publish(msg);
}

void MainWindow::goBackward()
{
    msg.linear.x = -100;
    msg.linear.y = 0;
    msg.linear.z = 0;
    msg.angular.x = 0;
    msg.angular.y = 0;
    msg.angular.z = 0;
    //pub.publish(msg);
}
