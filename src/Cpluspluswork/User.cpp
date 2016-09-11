#include"User.h"

User::User(QSqlRecord src)
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

QList<Profile*> User::getprofiles()
{
    for(auto i:this->profiles)
    {
        delete i;
    }
    this->profiles.clear();

    QSqlTableModel model;
    model.setTable("profiles");
    QString filter="username = '"+this->username+"'";
    model.setFilter(filter);
    model.setSort(static_cast<int>(ProfileField::Profile_Id),Qt::AscendingOrder);
    model.select();

    for(int i=0;i<model.rowCount();i++)
    {
        Profile*temp=new Profile(model.record(i));
        this->profiles.append(temp);
    }

    return this->profiles;

}

Profile* User::getprofile(int number)
{
    if(number<this->getprofiles().size())
    {
        return this->getprofiles().at(number);
    }
    else
    {
        return nullptr;
    }
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

void User::charge(double money)
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


User::~User()
{
    delete record;
    for(auto i:this->profiles)
    {
        delete i;
    }

}

