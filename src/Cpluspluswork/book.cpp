#include "book.h"
#include "ui_book.h"
#include <QtGui>
#include <QSqlQueryModel>
#include <QTableView>
#include <QSqlTableModel>
#include <QObject>
#include <QMessageBox>
#include"BasicDataField.h"

book::book(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::book)
{
    ui->setupUi(this);
}

book::~book()
{
    delete ui;
}

void book::on_bookButton_clicked()
{
    QSqlTableModel searchtable;
    searchtable.setTable("tickets");
    int row=0;
    searchtable.insertRow(row,1);
    //searchtable.setData(searchtable.index(row,static_cast<int>(TicketField::Ticket_Trainnumber),“传入列车号信息”);
    //searchtable.setData(searchtable.index(row,static_cast<int>(TicketField::Ticket_Profile_Id)),"传入身份信息");
    //searchtable.setData(searchtable.index(row,static_cast<int>(TicketField::Ticket_Seatnumber)),"传入座位号");
    //searchtable.setData(searchtable.index(row,static_cast<int>(TicketField::Ticket_Beginnumber)),"传入开始的车站在这辆车上的位次");
    //searchtable.setData(searchtable.index(row,static_cast<int>(TicketField::Ticket_Endnumber)),"传入结束车站在这列车的位次");
    searchtable.submitAll();
     QMessageBox::warning(this,tr("提示"),tr("订票成功"),QMessageBox::Close);
}

void book::on_exitButton_clicked()
{
    this->close();
}
