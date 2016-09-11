#include "Manager.h"
#include<QVariant>
#include<QSqlTableModel>
Manager::Manager(QSqlRecord src)
{
    password=src.value("password").toString();
    username=src.value("username").toString();
    record=new QSqlRecord(src);

}

void Manager::load(QSqlRecord& src)
{
    password=src.value("password").toString();
    username=src.value("username").toString();

    delete record;
    record=new QSqlRecord(src);
}

QSqlRecord Manager::toSqlRecord()
{
    return *record;
}

void Manager::submit()
{
    QSqlTableModel model;
    model.setTable("managers");
    QString filter=QString("username = '")+username+QString("'");
    model.setFilter(filter);
    model.select();
    if(model.rowCount()==1)
    {
        model.setRecord(0,*record);
        model.submitAll();
    }
}
