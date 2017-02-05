#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    on_bpReloadTopics_clicked();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_bpReloadTopics_clicked()
{
    XmlRpc::XmlRpcValue params("ros_topic_list");;

    XmlRpc::XmlRpcValue r;

    ui->result->setText(QString::fromStdString("test"));
    ui->comboTopics->clear();
    ui->comboTopics->addItem("Choose a topic ...");

    ros::master::execute("getTopicTypes", params, topic_list, r, false);
    for (int iBcl = 0; iBcl < topic_list[POSITION_TAB].size(); iBcl++){
        if(topic_list[POSITION_TAB][iBcl].size() == 2){
            std::string topic = static_cast<std::string>(topic_list[POSITION_TAB][iBcl][POSITION_TOPIC_NAME]);
            std::string type = static_cast<std::string>(topic_list[POSITION_TAB][iBcl][POSITION_TOPIC_TYPE]);
            ui->comboTopics->addItem(QString::fromStdString(topic));
        }
    }
}

void MainWindow::on_comboTopics_currentIndexChanged(int index)
{
    index --;
    if(index>=0){
        ui->result_4->setText(QString::fromStdString(topic_list[POSITION_TAB][index][POSITION_TOPIC_NAME]));
    }
}
