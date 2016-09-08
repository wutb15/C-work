#include "book.h"
#include "ui_book.h"
#include <QtGui>
#include <QSqlQueryModel>
#include <QTableView>
#include <QSqlQuery>
#include <QObject>
#include <QMessageBox>
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
    //处理数据库中内容
     QMessageBox::warning(this,tr("提示"),tr("订票成功"),QMessageBox::Close);
}

void book::on_exitButton_clicked()
{
    this->close();
}
