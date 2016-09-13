#include "ticket.h"
#include "ui_ticket.h"
#include <QtGui>
#include <QSqlQueryModel>
#include <QTableView>
#include <QSqlQuery>
#include <QObject>
#include <QSplitter>
#include <QSqlRelationalTableModel>
#include <QButtonGroup>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QMessageBox>
#include "userview.h"



TicketView::TicketView(User *user0,QWidget *parent):QDialog(parent),
    ui(new Ui::TicketView)
{
    ui->setupUi(this);
    user=user0;
    createTicketContent();
}


TicketView::~TicketView()
{
    delete ui;
}
enum
{

    Tickets_id=0,
    Tickets_profileid,
    Tickets_seatnumber,
    Tickets_trainnumber,
    Tickets_beginnumber,
    Tickets_endnumber

};

//create the Tablwidget to show tickets
void TicketView::createTicketContent()
{
    QSqlTableModel model;
    model.setTable("tickets");
    model.setFilter(QString("username = '%1'").arg(user->getusername()));
    model.select();
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setRowCount(model.rowCount());
    ui->tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem(tr("trainnumber")));
    ui->tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem(tr("startstation")));
    ui->tableWidget->setHorizontalHeaderItem(2,new QTableWidgetItem(tr("endstation")));
    ui->tableWidget->setHorizontalHeaderItem(3,new QTableWidgetItem(tr("starttime")));
    ui->tableWidget->setHorizontalHeaderItem(4,new QTableWidgetItem(tr("arrivetime")));
    ui->tableWidget->setHorizontalHeaderItem(5,new QTableWidgetItem(tr("cardid")));

    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for(int i=0;i<model.rowCount();i++)
    {
        Ticket ticket(model.record(i));
        Train train(ticket.getTrain());
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(train.gettrainnumber()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(train.getstation(ticket.getbeginnumber()).getstation().getname()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(train.getstation(ticket.getendnumber()).getstation().getname()));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(train.getstation(ticket.getbeginnumber()).getstarttime().toString()));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(train.getstation(ticket.getendnumber()).getarrivetime().toString()));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(ticket.getProfile().getcardid()));




    }

}


void TicketView::on_closeButton_clicked()
{
   this->close();
}
