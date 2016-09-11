#include "search.h"
#include "ui_search.h"
#include"seat.h"
#include"ui_seat.h"
#include <QtGui>
#include <QSqlQueryModel>
#include <QTableView>
#include <QSqlTableModel>
#include<QMessageBox>

SearchView::SearchView(User* user,Profile* profile,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchView)
{
    ui->setupUi(this);
    this->user=user;
    this->profile=profile;
    QSqlTableModel model;
    model.setTable("stations");
    model.select();
    for(int i=0;i<model.rowCount();i++)
    {
        QSqlRecord temp=model.record(i);
        ui->endstationBox->insertItem(temp.value(static_cast<int>(StationField::Station_Id)).toInt(),
                                      temp.value(static_cast<int>(StationField::Station_Name)).toString());
        ui->startstationBox->insertItem(temp.value(static_cast<int>(StationField::Station_Id)).toInt(),
                                        temp.value(static_cast<int>(StationField::Station_Name)).toString());

    }

}

SearchView::~SearchView()
{
    delete ui;
}

void SearchView::on_bookButton_clicked()
{
    if(ui->tableWidget->item(ui->tableWidget->currentRow(),4)->text()==tr("selectable"))
    {
        QString trainnumber(ui->tableWidget->item(ui->tableWidget->currentRow(),0)->text());
        QSqlTableModel model;
        model.setTable("trains");
        model.setFilter(tr("trainnumber = '%1'").arg(trainnumber));
        model.select();
        if(model.rowCount()==1)
        {
            Train* train =new Train(model.record(0));
            SeatView seatview1(train,train->getindex(ui->startstationBox->currentIndex()),
                               train->getindex(ui->endstationBox->currentIndex()),this->user,this->profile,this);
            seatview1.exec();
        }



    }
    else
    {
        QMessageBox::warning(this,tr("error"),tr("not selectable"),QMessageBox::Close);

    }


}

void SearchView::on_searchButton_clicked()
{
    QSqlTableModel start;
    QSqlTableModel result;
    start.setTable("trainstations");
    start.setFilter(tr("station_id = %1").arg(ui->startstationBox->currentIndex()));
    start.select();
    QList<QString>trainnumbers;
    int count=0;
    for(int i=0;i<start.rowCount();i++)
    {
        QString trainnumber=start.record(i).value(static_cast<int>(TrainStationField::TrainStation_TrainNumber)).toString();
        int miles=start.record(i).value(static_cast<int>(TrainStationField::TrainStation_Miles)).toInt();
        result.setTable("trainstations");
        result.setFilter(tr("station_id= %1 and trainnumber= '%2' and miles > %3").arg(ui->endstationBox->currentIndex())
                         .arg(trainnumber).arg(miles));
        result.select();
        if(result.rowCount()==1)
        {
            count++;
            trainnumbers.append(trainnumber);
        }
    }
    ui->tableWidget->clear();
    ui->tableWidget->resize(trainnumbers.size(),5);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setFont(QFont("Helvetica"));

    ui->tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem(tr("trainnumber")));
    ui->tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem(tr("starttime")));
    ui->tableWidget->setHorizontalHeaderItem(2,new QTableWidgetItem(tr("arrivetime")));
    ui->tableWidget->setHorizontalHeaderItem(3,new QTableWidgetItem(tr("remaintickets")));
    ui->tableWidget->setHorizontalHeaderItem(4,new QTableWidgetItem(tr("status")));


    for(int i=0;i<trainnumbers.size();i++)
    {
        QSqlTableModel model;
        model.setTable("trains");
        model.setFilter(tr("trainnumber = '%1'").arg(trainnumbers.at(i)));
        model.select();
        Train temp(model.record(0));
        int beginnumber=temp.getindex(ui->startstationBox->currentIndex());
        int endnumber=temp.getindex(ui->endstationBox->currentIndex());
        QTime starttime=temp.getstation(beginnumber)->getstarttime();
        QTime endtime=temp.getstation(endnumber)->getarrivetime();
        int remaintickets;
        int bookedtickets=0;
        for(int i=beginnumber;i<endnumber;i++)
        {
            bookedtickets=qMax(temp.getstation(i)->getbookednumber(),bookedtickets);

        }
        if(temp.getseattype()==SeatType::Bed)
        {
            remaintickets=60-bookedtickets;
        }
        else
        {
            remaintickets=120-bookedtickets;
        }

        bool selectable=(remaintickets&&(starttime.secsTo(QTime::currentTime())>30*60));//判定是否可以订


        ui->tableWidget->setItem(i,0,new QTableWidgetItem(temp.gettrainnumber()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(starttime.toString()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(endtime.toString()));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(remaintickets));
        if(selectable)
        {
            ui->tableWidget->setItem(i,4,new QTableWidgetItem(QString("selectable")));
        }
        else
        {
             ui->tableWidget->setItem(i,4,new QTableWidgetItem(QString("unselectable")));
        }






    }

}

void SearchView::on_startstationBox_currentIndexChanged(int index)
{
    ui->tableWidget->clear();
}

void SearchView::on_endstationBox_currentIndexChanged(int index)
{
    ui->tableWidget->clear();
}
