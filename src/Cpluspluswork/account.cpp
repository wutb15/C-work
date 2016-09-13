#include "account.h"
#include "ui_account.h"
#include <QtGui>
#include <QSqlQueryModel>
#include <QTableView>
#include <QSqlQuery>
#include<QSqlTableModel>
#include "userview.h"
#include <QMessageBox>

AccountView::AccountView(User* user0,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AccountView)
{
    ui->setupUi(this);
    ui->oldpwd->setEchoMode(QLineEdit::Password);
    ui->newpwd->setEchoMode(QLineEdit::Password);
    ui->confirmpwd->setEchoMode(QLineEdit::Password);
    user=user0;
}

AccountView::~AccountView()
{
    delete ui;
}
void AccountView::on_pwdButton_clicked()
{

    if(user->getpassword()==ui->oldpwd->text())
        if(ui->newpwd->text()==ui->confirmpwd->text())
        {
            user->setpassword(ui->newpwd->text());
            QMessageBox::warning(this,tr("Success"),tr("Password has been changed"),QMessageBox::Close);
            this->close();
        }
        else
            QMessageBox::warning(this,tr("Failed"),tr("Please confirm your new password"),QMessageBox::Close);
    else QMessageBox::warning(this,tr("Failed"),tr("Password is wrong"),QMessageBox::Close);
    ui->oldpwd->clear();
    ui->newpwd->clear();
    ui->confirmpwd->clear();
    ui->oldpwd->setFocus();

}

void AccountView::on_backButton_clicked()
{
    this->close();
}
