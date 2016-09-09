#include "profile.h"
#include "ui_profile.h"
#include <QtGui>
#include <QSqlQueryModel>
#include <QTableView>
#include <QSqlQuery>

#include <QMessageBox>
ProfileView::ProfileView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProfileView)
{
    ui->setupUi(this);
}

ProfileView::~ProfileView()
{
    delete ui;
}
