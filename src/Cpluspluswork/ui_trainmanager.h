/********************************************************************************
** Form generated from reading UI file 'trainmanager.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRAINMANAGER_H
#define UI_TRAINMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TrainManager
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TrainManager)
    {
        if (TrainManager->objectName().isEmpty())
            TrainManager->setObjectName(QStringLiteral("TrainManager"));
        TrainManager->resize(400, 300);
        menuBar = new QMenuBar(TrainManager);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        TrainManager->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TrainManager);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        TrainManager->addToolBar(mainToolBar);
        centralWidget = new QWidget(TrainManager);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        TrainManager->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(TrainManager);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        TrainManager->setStatusBar(statusBar);

        retranslateUi(TrainManager);

        QMetaObject::connectSlotsByName(TrainManager);
    } // setupUi

    void retranslateUi(QMainWindow *TrainManager)
    {
        TrainManager->setWindowTitle(QApplication::translate("TrainManager", "TrainManager", 0));
    } // retranslateUi

};

namespace Ui {
    class TrainManager: public Ui_TrainManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRAINMANAGER_H
