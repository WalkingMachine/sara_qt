/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QSpinBox *nombre1;
    QComboBox *operation;
    QGridLayout *gridLayout_2;
    QPushButton *boutonEgal;
    QSpinBox *nombre2;
    QLabel *resultat;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(525, 121);
        horizontalLayout = new QHBoxLayout(Dialog);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        nombre1 = new QSpinBox(Dialog);
        nombre1->setObjectName(QStringLiteral("nombre1"));

        gridLayout->addWidget(nombre1, 0, 0, 1, 1);

        operation = new QComboBox(Dialog);
        operation->setObjectName(QStringLiteral("operation"));

        gridLayout->addWidget(operation, 0, 1, 1, 1);


        horizontalLayout->addLayout(gridLayout);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        boutonEgal = new QPushButton(Dialog);
        boutonEgal->setObjectName(QStringLiteral("boutonEgal"));

        gridLayout_2->addWidget(boutonEgal, 0, 1, 1, 1);

        nombre2 = new QSpinBox(Dialog);
        nombre2->setObjectName(QStringLiteral("nombre2"));

        gridLayout_2->addWidget(nombre2, 0, 0, 1, 1);


        horizontalLayout->addLayout(gridLayout_2);

        resultat = new QLabel(Dialog);
        resultat->setObjectName(QStringLiteral("resultat"));

        horizontalLayout->addWidget(resultat);


        retranslateUi(Dialog);

        operation->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0));
        operation->clear();
        operation->insertItems(0, QStringList()
         << QApplication::translate("Dialog", "+", 0)
         << QApplication::translate("Dialog", "-", 0)
         << QApplication::translate("Dialog", "*", 0)
         << QApplication::translate("Dialog", "/", 0)
        );
        boutonEgal->setText(QApplication::translate("Dialog", "=", 0));
        resultat->setText(QApplication::translate("Dialog", "R\303\251sultat", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
