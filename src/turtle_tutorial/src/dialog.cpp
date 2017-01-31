#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    connect(ui->boutonEgal, SIGNAL(clicked()), this, SLOT(calculerOperation()));
}

void Dialog::calculerOperation(){
    int iResult;
    switch(ui->operation->currentIndex()){
    case 0:
        iResult = ui->nombre1->value() + ui->nombre2->value();
        break;
    case 1:
        iResult = ui->nombre1->value() - ui->nombre2->value();
        break;
    case 2:
        iResult = ui->nombre1->value() * ui->nombre2->value();
        break;
    case 3:
        if(ui->nombre2->value()){
            iResult = ui->nombre1->value() / ui->nombre2->value();
        }
        break;
    }
    ui->resultat->setNum(iResult);
}

Dialog::~Dialog()
{
    delete ui;
}

