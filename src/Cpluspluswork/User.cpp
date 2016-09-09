#include "User.h"
#include"search.h"
#include"ui_search.h"
#include"account.h"
#include"ui_account.h"
#include<QVariant>
#include "profile.h"
#include"ui_profile.h"
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
    model.setSort(ProfileField::Profile_Id,Qt::AscendingOrder);
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
    return this->getprofiles().at(number);
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


User::~User()
{
    delete _record;
    for(auto i:this->profiles)
    {
        delete i;
    }

}

UserView::UserView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserView)
{
    ui->setupUi(this);
}

UserView::~UserView()
{
    delete ui;
}
UserView::on_searchButton_clicked()
{
    SearchView searchview1;
    searchview1.show();
}

UserView::on_pwdButton_clicked()
{
    AccountView accountview1;
    accountview1.show();
}
UserView::on_infoButton_clicked()
{
    ProfileView profileview1;
    profileview1.show();
}
