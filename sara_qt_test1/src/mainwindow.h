#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#define POSITION_TAB 2
#define POSITION_TOPIC_NAME 0
#define POSITION_TOPIC_TYPE 1

#include <QMainWindow>
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

private slots:
    void on_bpReloadTopics_clicked();
    void on_comboTopics_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    XmlRpc::XmlRpcValue topic_list;
};

#endif // MAINWINDOW_H
