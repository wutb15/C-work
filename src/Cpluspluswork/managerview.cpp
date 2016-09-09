#include "managerview.h"
#include "ui_managerview.h"
#include <QtGui>
#include <QSqlQueryModel>
#include <QTableView>
#include <QSqlQuery>
#include <QObject>
#include <QMessageBox>
ManagerView::ManagerView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManagerView)
{
    ui->setupUi(this);
}

ManagerView::~ManagerView()
{
    delete ui;
}
