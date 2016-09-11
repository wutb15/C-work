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
    QSplitter *layout(Qt::Vertical);
    layout->addWidget(profilePanel);
    layout->addWidget(changeButton);
}


ProfileView::~ProfileView()
{
    delete ui;
}
enum
{
    Profiles_rowid=0,
    Profiles_id=1,
    Profiles_sex=2,
    Profiles_name=3,
    Profiles_cardid=4,
    Profiles_phone=5,
    Profiles_username=6

};
void ProfileView::createProfilePanel()
{
    profilePanel=new QWidget;
    profileModel=new QSqlRelationalTableModel(this);
    profileModel->setTable("profiles");
    profileModel->setSort(Profiles_id,Qt::AscendingOrder);
    profileModel->setHeaderData(Profiles_id,Qt::Horizontal,tr("id"));
    profileModel->setHeaderData(Profiles_sex,Qt::Horizontal,tr("sex"));
    profileModel->setHeaderData(Profiles_name,Qt::Horizontal,tr("name"));
    profileModel->setHeaderData(Profiles_phone,Qt::Horizontal,tr("phone"));
    QModelIndex index=profileModel->currentIndex();
    if(index.isValid())
    {
        QSqlRecord record =profileModel->record(index.row());
        QString name=record.value("username");
        profileModel->setFilter(QString("username= '%1'").arg(name));
    }
    profileModel->select();

    profileView=new QTableView;
    profileView->setModel(stationModel);
    profileView->setSelectionMode(QAbstractItemView::SingleSelection);
    profileView->setSelectionBehavior(QAbstractItemView::SelectRows);
    profileView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    profileView->resizeColumnsToContents();
    profileView->horizontalHeader()->setStretchLastSection(true);
    profileView->setColumnHidden(Profiles_rowid, true);
    profileView->setColumnHidden(Profiles_cardid, true);
    profileView->setColumnHidden(Profiles_username, true);

}

void ProfileView::on_changeButton_clicked()
{
    int profileId=-1;
    QModelIndex index=profileView->currentIndex();
    if(index.isvalid())
    {
        QSqlRecord record=profileModel->record(index.row());
        profileId=record.value(Profiles_id).toInt();
    }
    ProfileForm form1(user->getusername(),this);
    form1.exec();
}
ProfileView::on_backButton_clicked()
{
    UserView userview1(user);
    userview1.show();
    this->close();
}
