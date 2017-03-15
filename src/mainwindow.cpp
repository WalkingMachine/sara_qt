#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ROS_INFO("UI on");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateCPU(int iCore0Usage, int iCore1Usage, int iCore2Usage, int iCore3Usage){
    ui->Core0_bar->setValue(iCore0Usage);
    ui->Core1_bar->setValue(iCore1Usage);
    ui->Core2_bar->setValue(iCore2Usage);
    ui->Core3_bar->setValue(iCore3Usage);
}

void MainWindow::updateMemory(int iMemoryUsage){
    ui->Memory_bar->setValue(iMemoryUsage);
}
