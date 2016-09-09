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

void book::createTicket(QString trainnumber,int seatnumber,int beginnumber,int endnumber,int profile_id,QString username)
{
    QSqlTableModel searchtable;
    searchtable.setTable("tickets");
    int row=0;
    searchtable.insertRow(row,1);

    searchtable.setData(searchtable.index(row,static_cast<int>(TicketField::Ticket_Trainnumber),trainnumber);
    searchtable.setData(searchtable.index(row,static_cast<int>(TicketField::Ticket_Profile_Id)),profile_id);
    searchtable.setData(searchtable.index(row,static_cast<int>(TicketField::Ticket_Seatnumber)),seatnumber);
    searchtable.setData(searchtable.index(row,static_cast<int>(TicketField::Ticket_Beginnumber)),beginnumber);
    searchtable.setData(searchtable.index(row,static_cast<int>(TicketField::Ticket_Endnumber)),endnumber);
    searchtable.setData(searchtable.index(row,static_cast<int>(TicketField::Ticket_Username)),username);
    searchtable.submitAll();
}

void book::on_bookButton_clicked()
{

    //use createTicket;
     QMessageBox::warning(this,tr("提示"),tr("订票成功"),QMessageBox::Close);
}

void book::on_exitButton_clicked()
{
    this->close();
}
