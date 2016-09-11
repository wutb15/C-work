#include"search.h"
#include"ui_search.h"
#include"account.h"
#include"ui_account.h"
#include<QVariant>
#include "profile.h"
#include"ui_profile.h"
#include"userview.h"
#include"ui_userview.h"

UserView::UserView(User *user0,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserView)
{
    ui->setupUi(this);
    user=user0;
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
UserView::on_ticketButton_clicked()
{
    TicketView ticketview1;
    ticketview1.show();
}
