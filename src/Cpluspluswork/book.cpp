#include "book.h"
#include "ui_book.h"
#include <QtGui>
#include <QSqlQueryModel>
#include <QTableView>
#include <QSqlTableModel>
#include <QObject>
#include <QMessageBox>
#include"BasicDataField.h"

const double mile_co=0.5;

const double speed_co[4]={1,2,3,4.5};
const double seat_co[2]={2,1};

int cal(int miles,SeatType seattype,SpeedType speedtype)
{
    return int(miles*mile_co*speed_co[static_cast<int>(speedtype)]*seat_co[static_cast<int>(seattype)]);

}

book::book( User *user,  Train *train,  Profile *profile, int seatnumber, int beginnumber, int endnumber, QWidget *parent):
    QDialog(parent),ui(new Ui::book)
{
    this->passenger=user;
    this->train=train;
    this->profile=profile;
    this->seatnumber=seatnumber;
    this->beginnumber=beginnumber;
    this->endnumber=endnumber;
    ui->setupUi(this);



    TrainStation* begin=this->train->getstation(beginnumber);
    TrainStation* end=this->train->getstation(endnumber);
    qDebug()<<end->getarrivetime().toString();
    qDebug()<<beginnumber;
    qDebug()<<begin->getstarttime();

    ui->trainumberEdit->setText(this->train->gettrainnumber());
    ui->endtimeEdit->setTime(end->getarrivetime());
    ui->starttimeEdit->setTime(begin->getstarttime());
    qDebug()<<static_cast<int>(this->train->getseattype());
    qDebug()<<cal(end->getmiles()-begin->getmiles(),
                  this->train->getseattype(),this->train->getspeedtype());
    ui->costEdit->setText(QString("%1").arg(cal(end->getmiles()-begin->getmiles(),
                              this->train->getseattype(),this->train->getspeedtype())));
    ui->startstationEdit->setText(QString("%1").arg(begin->getstation()->getname()));
    ui->endstationEdit->setText(QString("%1").arg(end->getstation()->getname()));

}

book::~book()
{
    delete ui;
}

void book::createTicket(QString trainnumber,int seatnumber,int beginnumber,int endnumber,int profile_id,QString username)
{
    QSqlTableModel searchtable;
    searchtable.setTable("tickets");
    int row=0;
    searchtable.insertRow(row);

    searchtable.setData(searchtable.index(row,static_cast<int>(TicketField::Ticket_Trainnumber)),trainnumber);
    searchtable.setData(searchtable.index(row,static_cast<int>(TicketField::Ticket_Profile_Id)),profile_id);
    searchtable.setData(searchtable.index(row,static_cast<int>(TicketField::Ticket_Seatnumber)),seatnumber);
    searchtable.setData(searchtable.index(row,static_cast<int>(TicketField::Ticket_Beginnumber)),beginnumber);
    searchtable.setData(searchtable.index(row,static_cast<int>(TicketField::Ticket_Endnumber)),endnumber);
    searchtable.setData(searchtable.index(row,static_cast<int>(TicketField::Ticket_Username)),username);
    searchtable.submitAll();
}

void book::addNumber()
{
    QSqlTableModel model;
    model.setTable("trainstations");
    model.setFilter(tr("trainnumber = '%1'").arg(this->train->gettrainnumber()));
    model.setSort(static_cast<int>(TrainStationField::TrainStation_Miles),Qt::AscendingOrder);
    model.select();
    for(int i=beginnumber;i<endnumber;i++)
    {
        QSqlRecord record=model.record(i);
        int bookednumber=record.value(static_cast<int>(TrainStationField::TrainStation_BookedNumber)).toInt();
        record.setValue(static_cast<int>(TrainStationField::TrainStation_BookedNumber),bookednumber+1);
        model.setRecord(i,record);
    }
    model.submitAll();

}






void book::on_bookButton_clicked()
{
    double money =cal(train->getstation(endnumber)->getmiles()-train->getstation(beginnumber)->getmiles(),train->getseattype(),train->getspeedtype());
    if(this->passenger->pay(money))
    {


         createTicket(train->gettrainnumber(),seatnumber,beginnumber,endnumber,profile->getid(),this->passenger->getusername());
         addNumber();

        QMessageBox::information(this,QString("提示"),QString("订票成功"),QMessageBox::Close);
    }
    else
    {
        QMessageBox::warning(this,tr("warning"),tr("money is not enough"),QMessageBox::Close);
    }
}

void book::on_exitButton_clicked()
{
    this->close();
}
