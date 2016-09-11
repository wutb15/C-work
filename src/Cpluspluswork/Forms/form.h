#ifndef FORM_H
#define FORM_H

#include "ui_form.h"
#include<QDataWidgetMapper>
#include<QSql>
#include<QSqlRelationalTableModel>
#include<QString>
#include"BasicDataField.h"

namespace Ui
{class Form;}

class Form : public QDialog
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);

private:

    virtual void createMap()=0;//创建表与数据库对应关系
    virtual void createContents()=0;//创建表的内容
    virtual void createTable()=0;//创建和链接表;
private slots:
    virtual void addItem()=0;//执行增加元素的作用
    virtual void deleteItem()=0;//执行删减元素的作用





protected:
    Ui::Form ui;
    QDataWidgetMapper* mapper;
    QSqlRelationalTableModel* tableModel;
    void createconnections();
};

#endif // FORM_H
