#include"search.h"
#include"ui_search.h"
#include"account.h"
#include"ui_account.h"
#include<QVariant>
#include "profile.h"
#include"ui_profile.h"
#include"userview.h"
#include"ui_userview.h"
#include"charge.h"

#include"ticket.h"
class TicketView;
UserView::UserView(User *user0,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserView)
{
    ui->setupUi(this);
    user=user0;
    profile=user->getprofile();
    if(profile==nullptr)
    {
        ui->searchButton->setEnabled(false);

    }
}

UserView::~UserView()
{
    delete ui;
    delete profile;
}
void UserView::on_searchButton_clicked()
{
    SearchView searchview1(user,profile,this);
    searchview1.exec();
}

void UserView::on_pwdButton_clicked()
{
    AccountView accountview1(user,this);
    accountview1.exec();
}

void UserView::on_infoButton_clicked()
{
    ProfileView profileview1(user,this);
    profileview1.exec();
    profile=user->getprofile();
}

void UserView::on_ticketButton_clicked()
{
    TicketView ticketview1(user,this);
    ticketview1.exec();
}



void UserView::on_exitButton_clicked()
{
   this->close();
}

void UserView::on_chargeButton_clicked()
{
    Charge charge(user,this);
    charge.exec();
}
