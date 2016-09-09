#include "search.h"
#include "ui_search.h"
#include"seat.h"
#include"ui_seat.h"
#include <QtGui>
#include <QSqlQueryModel>
#include <QTableView>
#include <QSqlQuery>

SearchView::SearchView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchView)
{
    ui->setupUi(this);
}

SearchView::~SearchView()
{
    delete ui;
}

SearchView::on_bookButton_clicked()
{
    SeatView seatview1;
    seatview1.show();
}
