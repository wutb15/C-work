#include "account.h"
#include "ui_account.h"
#include <QtGui>
#include <QSqlQueryModel>
#include <QTableView>
#include <QSqlQuery>

AccountView::AccountView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AccountView)
{
    ui->setupUi(this);
}

AccountView::~AccountView()
{
    delete ui;
}
AccountView::on_pwdButton_clicked()
{
//在数据库中修改密码
    QMessageBox::warning(this,tr("Success"),tr("Password has been changed"),QMessageBox::Close);
}
