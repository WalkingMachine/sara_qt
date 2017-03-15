#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#define POSITION_TAB 2
#define POSITION_TOPIC_NAME 0
#define POSITION_TOPIC_TYPE 1

#include <QMainWindow>
#include <QStringListModel>
#include <QAbstractItemView>
#include <QThread>
#include "CThreadDiagnostics.h"

#include <ros/ros.h>


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
    void updateCPU(int iCore0Usage, int iCore1Usage, int iCore2Usage, int iCore3Usage);
    void updateMemory(int iMemoryUsage);

private slots:

private:
    Ui::MainWindow *ui;
    XmlRpc::XmlRpcValue topic_list;
    ros::NodeHandle NodeHandle;
    ros::Subscriber Subscribe;

signals:
    void subscribeSignal();
    void unsubscribeSignal();

};

#endif // MAINWINDOW_H
