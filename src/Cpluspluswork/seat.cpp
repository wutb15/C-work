#include "seat.h"
#include "ui_seat.h"
#include"book.h"

#include <QtGui>
#include <QSqlQueryModel>
#include <QTableView>
#include <QSqlQuery>
#include <QObject>

#include <QMessageBox>
SeatView::SeatView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SeatView)
{
    ui->setupUi(this);
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
