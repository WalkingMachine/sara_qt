#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#define POSITION_TAB 2
#define POSITION_TOPIC_NAME 0
#define POSITION_TOPIC_TYPE 1

#include <QMainWindow>
#include <QStringListModel>
#include <QAbstractItemView>
#include <QThread>
#include "cthreadtopicssubscriber.h"

#include <ros/ros.h>
#include <turtlesim/Pose.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void subscriptionCallback(const turtlesim::Pose msg);

public slots:
    void newMessageReceivedSlot(QString topic);

private slots:
    void on_bpReloadTopics_clicked();
    void on_comboTopics_currentIndexChanged(int index);
    void on_cbRunSubscriber_clicked(bool checked);

private:
    Ui::MainWindow *ui;
    XmlRpc::XmlRpcValue topic_list;
    ros::NodeHandle NodeHandle;
    ros::Subscriber Subscribe;

    int iKeySelectedTopic;
    bool bIsSubscribe;

    QStringListModel *model;

signals:
    void subscribeSignal(QString topic);
    void unsubscribeSignal();

};

#endif // MAINWINDOW_H
