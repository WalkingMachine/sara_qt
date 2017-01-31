#include <ros/ros.h>
#include <QApplication>
#include <QPushButton>
#include "dialog.h"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    Dialog monDialog;
    monDialog.show();

    return app.exec();
}
