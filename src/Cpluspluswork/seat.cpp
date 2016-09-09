#include "seat.h"
#include "ui_seat.h"
#include"book.h"
#include"BasicDataField.h"
#include"BasicData/basicdata.h"

#include <QtGui>
#include <QSqlQueryModel>
#include <QTableView>
#include <QSqlQuery>
#include <QObject>

#include <QMessageBox>
SeatView::SeatView(const Train *train, int beginnumber, int endnumber, const User *user, const Profile *profile, QWidget *parent):
    QDialog(parent)
    ,ui(new Ui::SeatView)
{
    this->train=train;
    this->beginnumber=beginnumber;
    this->endnumber=endnumber;
    this->user=user;
    this->profile=profile;
    switch(this->train->getseattype())
    {
        case SeatType::Bed:
            this->createChooseArea_B();
            break;
        case SeatType::Sit:
            this->createChooseArea_S();
            break;
        default:
            break;



    }
    ui->setupUi(this);
}

void SeatView::createChooseArea_B()
{


}

SeatView::~SeatView()
{
    delete ui;
}
SeatView::on_bookButton_clicked()
{
    book book1;
    book1.show();
}
