#include "charge.h"
#include "ui_charge.h"
#include<QIntValidator>

Charge::Charge(User * user,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Charge)
{
    this->user=user;
    ui->setupUi(this);
    ui->chargeEdit->setValidator(new QIntValidator(0,9999));
    ui->moneyEdit->setText(QString("%1").arg(user->getmoney()));
    ui->moneyEdit->setReadOnly(true);

}

Charge::~Charge()
{
    delete ui;
}

void Charge::on_closeButton_clicked()
{
    this->close();
}

void Charge::on_chargeButton_clicked()
{
    user->charge(ui->chargeEdit->text().toInt());
    ui->moneyEdit->setText(QString("%1").arg(user->getmoney()));
}
