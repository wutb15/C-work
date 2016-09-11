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
SeatView::SeatView( Train *train, int beginnumber, int endnumber,  User *user,  Profile *profile, QWidget *parent):
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
    ui->seats->resize(20,3);

    ui->seats->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->seats->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->seats->setFont(QFont("Helvetica"));

    QStringList words;
    words<<"up"
        <<"middle"
       <<"down";
    for(int i=0;i<20;i++)
    {
        for(int j=0;j<3;j++)
        {
            QSqlQuery query;
            query.prepare("SELECT * FROM users where trainnumber =:trainnumber AND seatnumber =:seatnumber AND beginnumber<:endnumber AND endnumber <:beginnumber");
            query.bindValue(":seatnumber",i*3+j+1);
            query.bindValue(":endnumber",endnumber);
            query.bindValue(":beginnumber",beginnumber);
            query.bindValue(":trainnumber",this->train->gettrainnumber());
            query.exec();
            if(query.next())
            {
                QTableWidgetItem* item =new QTableWidgetItem(tr("%1 %2").arg(i).arg(words.at(j)));
                item->setBackgroundColor(QColor(Qt::GlobalColor::gray));//灰色代表无法选，白色代表可选；
                item->setTextColor(QColor(Qt::GlobalColor::black));
                ui->seats->setItem(i,j,item);



            }
            else
            {
               QTableWidgetItem* item =new QTableWidgetItem(tr("%1 %2").arg(i).arg(words.at(j)));
               item->setBackgroundColor(QColor(Qt::GlobalColor::white));
               item->setTextColor(QColor(Qt::GlobalColor::black));
               ui->seats->setItem(i,j,item);
            }
        }
    }



}

void SeatView::createChooseArea_S()
{
     ui->seats->resize(20,7);
     int number=0;
     for(int i=0;i<20;i++)
     {
         for(int j=0;j<7;j++)
         {
             if(j=3)
             {
                 continue;
                 ui->seats->item(i,j)->setBackgroundColor(QColor(Qt::GlobalColor::red));


             }
             else
             {
                 number++;
                 QSqlQuery query;
                 query.prepare("SELECT * FROM users where trainnumber =:trainnumber AND seatnumber =:seatnumber AND beginnumber<:endnumber AND endnumber <:beginnumber");
                 query.bindValue(":seatnumber",number);
                 query.bindValue(":endnumber",endnumber);
                 query.bindValue(":beginnumber",beginnumber);
                 query.bindValue(":trainnumber",this->train->gettrainnumber());
                 if(query.next())
                 {
                     QTableWidgetItem* item =new QTableWidgetItem(tr("%1 %2").arg(i).arg(words.at(j)));
                     item->setBackgroundColor(QColor(Qt::GlobalColor::gray));
                     item->setTextColor(QColor(Qt::GlobalColor::black));
                     ui->seats->setItem(i,j,item);

                 }
                 else
                 {
                     QTableWidgetItem* item =new QTableWidgetItem(tr("%1 %2").arg(i).arg(words.at(j)));
                     item->setBackgroundColor(QColor(Qt::GlobalColor::white));
                     item->setTextColor(QColor(Qt::GlobalColor::black));
                     ui->seats->setItem(i,j,item);
                 }

             }
         }
     }

}

SeatView::~SeatView()
{
    delete ui;
    delete train;
}
SeatView::on_bookButton_clicked()
{
    int number;
    if(this->train->getseattype()==SeatType::Bed)
    {
        number=ui->seats->currentColumn()+ui->seats->currentRow()*3+1;

    }
    else
    {
        if(ui->seats->currentColumn()>3)
       {

            number=ui->seats->currentColumn()+ui->seats->currentRow()*6;
       }
        else
        {
            number=ui->seats->currentColumn()+ui->seats->currentRow()*6+1;
        }

    }
    book book1=book(this->user,this->train,this->profile,number,this->beginnumber,this->endnumber,this);
    book1.exec();

}

void SeatView::on_seats_clicked(const QModelIndex &index)
{
   if(ui->seats->item(index.row(),index.column())->backgroundColor()==QColor(Qt::GlobalColor::white))
   {
       ui->bookButton->setEnabled(true);
   }
   else
   {
       ui->bookButton->setEnabled(false);
   }
}
