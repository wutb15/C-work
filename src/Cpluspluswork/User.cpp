#include "User.h"
#include<QVariant>
User::User(QSqlRecord &src)
{
    username=src.value("username").toString();
    password=src.value("password").toString();
    money=src.value("money").toDouble();
    extrainformation=src.value("extrainformation").toString();

    record=new QSqlRecord(src);

}

void User::load(QSqlRecord& src)
{
    username=src.value("username").toString();
    password=src.value("password").toString();
    money=src.value("money").toDouble();
    extrainformation=src.value("extrainformation").toString();

    delete record;

    record=new QSqlRecord(src);

}

bool User::pay(double money)
{
    if(this->money>money)
    {
        this->money-=money;
        record->setValue("money",this->money);
        submit();
        return true;
    }
    else
    {
        return false;
    }
}

void User::money(double money)
{
    this->money+=money;
    record->setValue("money",this->money);
    submit();

}

QSqlRecord User::toSqlRecord()
{
    return *record;
}

void User::submit()
{
    QSqlTableModel model;
    model.setTable("users");
    QString filter=QString("username = '")+username+QString("'");
    model.setFilter(filter);
    model.select();
    if(model.rowCount()==1)
    {
        model.setRecord(0,*record);
        model.submitAll();
    }
}
