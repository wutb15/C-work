#include "profile.h"
#include "ui_profile.h"
#include <QtGui>
#include <QSqlQueryModel>
#include <QTableView>
#include <QSqlQuery>
#include <QObject>
#include <QSplitter>
#include <QSqlRelationalTableModel>
#include <QButtonGroup>
#include <QPushButton>
#include <QDialogButtonBox>
#include <Forms/profileform.h>
#include <QMessageBox>
#include "userview.h"
ProfileView::ProfileView(User *user0,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProfileView)
{
    ui->setupUi(this);
    user=user0;
    createProfilePanel();
    ui->gridLayout->addWidget(profileView);
}


ProfileView::~ProfileView()
{
    delete ui;
}
enum
{
    Profiles_id=0,
    Profiles_sex,
    Profiles_name,
    Profiles_cardid,
    Profiles_phone,
    Profiles_username

};
void ProfileView::createProfilePanel()
{
    profileModel=new QSqlRelationalTableModel(this);
    profileModel->setTable("profiles");
    profileModel->setSort(Profiles_id,Qt::AscendingOrder);
    profileModel->setHeaderData(Profiles_id,Qt::Horizontal,tr("id"));
    profileModel->setHeaderData(Profiles_sex,Qt::Horizontal,tr("sex"));
    profileModel->setHeaderData(Profiles_name,Qt::Horizontal,tr("name"));
    profileModel->setHeaderData(Profiles_phone,Qt::Horizontal,tr("phone"));

    profileModel->setFilter(QString("username = '%1'").arg(user->getusername()));

    profileModel->select();

    profileView=new QTableView;
    profileView->setModel(profileModel);
    profileView->setSelectionMode(QAbstractItemView::SingleSelection);
    profileView->setSelectionBehavior(QAbstractItemView::SelectRows);
    profileView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    profileView->resizeColumnsToContents();
    profileView->horizontalHeader()->setStretchLastSection(true);

    profileView->setColumnHidden(Profiles_cardid, true);
    profileView->setColumnHidden(Profiles_username, true);

}



void ProfileView::on_changeButton_clicked()
{
    int profileId=-1;
    QModelIndex index=profileView->currentIndex();
    if(index.isValid())
    {
        QSqlRecord record=profileModel->record(index.row());
        profileId=record.value(Profiles_id).toInt();
    }
    ProfileForm form1(user->getusername(),profileId,this);
    form1.exec();
    updateview();

}

void ProfileView::updateview()
{
    profileModel->clear();
    profileModel->setTable("profiles");
    profileModel->setSort(Profiles_id,Qt::AscendingOrder);
    profileModel->setHeaderData(Profiles_id,Qt::Horizontal,tr("id"));
    profileModel->setHeaderData(Profiles_sex,Qt::Horizontal,tr("sex"));
    profileModel->setHeaderData(Profiles_name,Qt::Horizontal,tr("name"));
    profileModel->setHeaderData(Profiles_phone,Qt::Horizontal,tr("phone"));

    profileModel->setFilter(QString("username = '%1'").arg(user->getusername()));

    profileModel->select();
}

void ProfileView::on_closeButton_clicked()
{
   this->close();
}
