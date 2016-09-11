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
TicketView::TicketView(User *user0,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TicketView)
{
    ui->setupUi(this);
    user=user0;
    createTicketPanel();
    QSplitter layout(Qt::Vertical);
    layout.addWidget(ticketPanel);
    layout.addWidget(backButton);
}


TicketView::~TicketView()
{
    delete ui;
}
enum
{

    Tickets_id=1,
    Tickets_profileid=2,
    Tickets_seatnumber=3,
    Tickets_trainnumber=4,
    Tickets_beginnumber=5,
    Tickets_endnumber=6

};
void TicketView::createTicketPanel()
{
    ticketPanel=new QWidget;
    ticketModel=new QSqlRelationalTableModel(this);
    ticketModel->setTable("tickets");
    ticketModel->setSort(Tickets_id,Qt::AscendingOrder);
    ticketModel->setHeaderData(Tickets_id,Qt::Horizontal,tr("id"));
    ticketModel->setHeaderData(Tickets_profileid,Qt::Horizontal,tr("sex"));
    ticketModel->setHeaderData(Tickets_seatnumber,Qt::Horizontal,tr("name"));
    ticketModel->setHeaderData(Tickets_trainnumber,Qt::Horizontal,tr("phone"));


    ticketView=new QTableView;
    ticketView->setModel(ticketModel);
    ticketView->setSelectionMode(QAbstractItemView::SingleSelection);
    ticketView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ticketView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ticketView->resizeColumnsToContents();
    ticketView->horizontalHeader()->setStretchLastSection(true);

    ticketView->setColumnHidden(Tickets_beginnumber, true);
    ticketView->setColumnHidden(Tickets_endnumber, true);
    QModelIndex index=ticketView->currentIndex();
    if(index.isValid())
    {
    QSqlRecord record =ticketModel->record(index.row());
    QString name=record.value("username").toString();
    ticketModel->setFilter(QString("username=%1").arg(name));
    }
    ticketModel->select();

}


void TicketView::on_backButton_clicked()
{
    UserView userview1(user);
    userview1.show();
    this->close();
}
