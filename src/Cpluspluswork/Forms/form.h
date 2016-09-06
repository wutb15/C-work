#ifndef FORM_H
#define FORM_H

#include "ui_form.h"
#include<QDataWidgetMapper>
#include<QSql>
#include<QSqlRelationalTableModel>

class Ui::Form;

class Form : public QDialog
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);

private:
    virtual void addItem()=0;//执行增加元素的作用
    virtual void delteItem()=0;//执行删减元素的作用
    virtual void createMap()=0;//创建表与数据库对应关系
    virtual void createContents()=0;//创建表的内容



protected:
    Ui::Form ui;
    QDataWidgetMapper* mapper;
    QSqlRelationalTableModel* tableModel;
private slots:
    void on_addButton_clicked();
    void on_deleteButton_clicked();
};

#endif // FORM_H
