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

void MainWindow::updateCPU(float iCore0Usage, float iCore1Usage, float iCore2Usage, float iCore3Usage){
    ROS_INFO("CPU refresh");

    ui->Core0_bar->setValue(iCore0Usage);
    ui->Core1_bar->setValue(iCore1Usage);
    ui->Core2_bar->setValue(iCore2Usage);
    ui->Core3_bar->setValue(iCore3Usage);

    ui->Core4_bar->setValue(iCore0Usage);
    ui->Core5_bar->setValue(iCore1Usage);
    ui->Core6_bar->setValue(iCore2Usage);
    ui->Core7_bar->setValue(iCore3Usage);
}

void MainWindow::updateMemory(float iMemoryUsage){
    ui->Memory_bar->setValue(iMemoryUsage*100);
}
