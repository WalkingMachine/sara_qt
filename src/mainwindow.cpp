#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    on_bpReloadTopics_clicked();
    iKeySelectedTopic = -1;
    bIsSubscribe = false;

    //Create model (list of topics)
    model = new QStringListModel(this);
    //Link Node Message List to Model
    ui->listTopicsMessages->setModel(model);
}

MainWindow::~MainWindow()
{
    delete model;
    delete ui;
}

//When you reload the topic list
void MainWindow::on_bpReloadTopics_clicked()
{
    //Reset combobox items list
    ui->comboTopics->clear();
    ui->comboTopics->addItem("Choose a topic ...");

    //Reload topic list
    XmlRpc::XmlRpcValue params("ros_topic_list");
    XmlRpc::XmlRpcValue r;
    ros::master::execute("getTopicTypes", params, topic_list, r, false);

    //For each topics:
    for (int iBcl = 0; iBcl < topic_list[POSITION_TAB].size(); iBcl++){
        if(topic_list[POSITION_TAB][iBcl].size() == 2){
            //read topic name and type
            QString topic = QString::fromStdString(topic_list[POSITION_TAB][iBcl][POSITION_TOPIC_NAME]);
            QString type = QString::fromStdString(topic_list[POSITION_TAB][iBcl][POSITION_TOPIC_TYPE]);

            //add item to combobox
            ui->comboTopics->addItem(topic + "-------- of type --------" + type);
        }
    }
}

//When you choose a topic in the combobox
void MainWindow::on_comboTopics_currentIndexChanged(int index)
{
    iKeySelectedTopic = --index;
    if(index>=0){
        ui->result_4->setText(QString::fromStdString(topic_list[POSITION_TAB][index][POSITION_TOPIC_NAME]));
    }
}

//When you turn on the subscription
void MainWindow::on_cbRunSubscriber_clicked(bool checked)
{
    if(checked){
        if(!bIsSubscribe && iKeySelectedTopic != -1){
            bIsSubscribe = true;
            subscribeSignal("/turtle1/pose");
        }else{
            ui->cbRunSubscriber->setChecked(false);
        }
    }else if(!checked){
        unsubscribeSignal();
        bIsSubscribe = false;
        ui->result_2->setText("Unsubscribe");
    }
}

void MainWindow::newMessageReceivedSlot(QString topic){
    // Get the position
//    ui->listTopicsMessages->setItem(0, 1, new QTableWidgetItem("Hello"));
}
