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
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    QStringList head;
    head<<"trainnumber"<<"starttime"<<"arrivetime"<<"remaintickets"<<"status";
    ui->tableWidget->setHorizontalHeaderLabels(head);





}

SearchView::~SearchView()
{
    delete ui;
}

void SearchView::on_bookButton_clicked()
{
    if(ui->tableWidget->currentIndex().isValid())
    {
        if(ui->tableWidget->item(ui->tableWidget->currentRow(),4)->text()==tr("selectable"))
        {
            QString trainnumber(ui->tableWidget->item(ui->tableWidget->currentRow(),0)->text());
            QSqlTableModel model;
            model.setTable("trains");
            model.setFilter(QString("trainnumber = '%1'").arg(trainnumber));
            model.select();

            if(model.rowCount()==1)
            {
                Train* train =new Train(model.record(0));
                qDebug()<<train->gettrainnumber();
                SeatView seatview1(train,train->getindex(ui->startstationBox->currentIndex()+1),
                               train->getindex(ui->endstationBox->currentIndex()+1),this->user,this->profile,this);
                seatview1.exec();
                delete train;
            }



        }
        else
        {
            QMessageBox::warning(this,tr("error"),tr("not selectable"),QMessageBox::Close);

        }
    }
    else
    {
        QMessageBox::warning(this,tr("error"),tr("not select a row"),QMessageBox::Close);
    }


}

void SearchView::on_searchButton_clicked()
{
    QSqlTableModel start;
    QSqlTableModel result;
    start.setTable("trainstations");
    start.setFilter(QString("station_id = '%1'").arg(ui->startstationBox->currentIndex()+1));
    start.select();
    qDebug()<<QString("station_id = '%1'").arg(ui->startstationBox->currentIndex()+1);
    qDebug()<<start.rowCount();

    QList<QString>trainnumbers;
    int count=0;
    for(int i=0;i<start.rowCount();i++)
    {
        QString trainnumber=start.record(i).value(static_cast<int>(TrainStationField::TrainStation_TrainNumber)).toString();
        qDebug()<<trainnumber;
        int miles=start.record(i).value(static_cast<int>(TrainStationField::TrainStation_Miles)).toInt();
        result.setTable("trainstations");
        result.setFilter(tr("station_id= %1 and trainnumber= '%2' and miles > %3").arg(ui->endstationBox->currentIndex()+1)
                         .arg(trainnumber).arg(miles));
        result.select();
        if(result.rowCount()==1)
        {
            count++;
            trainnumbers.append(trainnumber);
        }
    }
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(trainnumbers.size());
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setFont(QFont("Helvetica"));

    QStringList head;
    head<<"trainnumber"<<"starttime"<<"arrivetime"<<"remaintickets"<<"status";
    ui->tableWidget->setHorizontalHeaderLabels(head);

    for(int i=0;i<trainnumbers.size();i++)
    {
        qDebug()<<trainnumbers.size();
        QSqlTableModel model;
        model.setTable("trains");
        model.setFilter(QString("trainnumber = '%1'").arg(trainnumbers.at(i)));
        model.select();
        qDebug()<<model.rowCount();
        QSqlRecord record=model.record(0);
        Train* temp=new Train(record);
        int beginnumber=temp->getindex(ui->startstationBox->currentIndex()+1);
        int endnumber=temp->getindex(ui->endstationBox->currentIndex()+1);
        QTime starttime=temp->getstation(beginnumber).getstarttime();
        QTime endtime=temp->getstation(endnumber).getarrivetime();
        int remaintickets;
        int bookedtickets=0;
        qDebug()<<beginnumber<<endnumber;
        qDebug()<<starttime.toString();
        for(int i=beginnumber;i<endnumber;i++)
        {
            bookedtickets=qMax(temp->getstation(i).getbookednumber(),bookedtickets);

        }
        qDebug()<<bookedtickets;
        if(temp->getseattype()==SeatType::Bed)
        {
            remaintickets=60-bookedtickets;
        }
        else
        {
            remaintickets=120-bookedtickets;
        }
        qDebug()<<remaintickets;

        bool selectable=(remaintickets&&(starttime.secsTo(QTime::currentTime())>30*60));//判定是否可以订
        selectable=true;
        qDebug()<<selectable;
        qDebug()<<starttime.toString();
        qDebug()<<endtime.toString();
        qDebug()<<temp->gettrainnumber();

        ui->tableWidget->setItem(i,0,new QTableWidgetItem(temp->gettrainnumber()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(starttime.toString()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(endtime.toString()));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(QString("%1").arg(remaintickets)));
        if(selectable)
        {
            ui->tableWidget->setItem(i,4,new QTableWidgetItem(QString("selectable")));
        }
        else
        {
             ui->tableWidget->setItem(i,4,new QTableWidgetItem(QString("unselectable")));
        }
       delete temp;








    }

}

void SearchView::on_startstationBox_currentIndexChanged(int index)
{
    ui->tableWidget->clear();
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setFont(QFont("Helvetica"));

    QStringList head;
    head<<"trainnumber"<<"starttime"<<"arrivetime"<<"remaintickets"<<"status";
    ui->tableWidget->setHorizontalHeaderLabels(head);
}

void SearchView::on_endstationBox_currentIndexChanged(int index)
{
    ui->tableWidget->clear();
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setFont(QFont("Helvetica"));

    QStringList head;
    head<<"trainnumber"<<"starttime"<<"arrivetime"<<"remaintickets"<<"status";
    ui->tableWidget->setHorizontalHeaderLabels(head);
}
