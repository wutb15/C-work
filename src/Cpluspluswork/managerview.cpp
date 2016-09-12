#include "managerview.h"
#include "ui_ManagerView.h"
#include <QtGui>
#include <QSqlQueryModel>
#include <QTableView>
#include <QSqlQuery>
#include <QObject>
#include <QSplitter>
#include <QMessageBox>
#include <QSqlRelationalTableModel>
#include <QButtonGroup>
#include <QPushButton>
#include <QDialogButtonBox>
#include <Forms/trainstationform.h>
#include<QAbstractItemView>
#include<QSqlRelationalDelegate>

ManagerView::~ManagerView()
{
    delete ui;
}
ManagerView::ManagerView(Manager* manager,QWidget *parent) :
    QDialog(parent),

    ui(new Ui::ManagerView)
{
    this->manager=manager;
    ui->setupUi(this);

    createTrainPanel();
    createStationPanel();
    addtrainButton=new QPushButton(tr("addTrain"),this);
    deletetrainButton=new QPushButton(tr("delete"),this);
    editstationButton=new QPushButton(tr("edit_station"),this);
    closeButton=new QPushButton(tr("Close"),this);
    buttonBox=new QDialogButtonBox(this);
    buttonBox->addButton(addtrainButton,QDialogButtonBox::ActionRole);
    buttonBox->addButton(deletetrainButton,QDialogButtonBox::ActionRole);
    buttonBox->addButton(editstationButton,QDialogButtonBox::ActionRole);
    buttonBox->addButton(closeButton,QDialogButtonBox::ActionRole);

    ui->buttonBoxLayout->addWidget(buttonBox);
    ui->trainLayout->addWidget(trainView);
    ui->trainstationLayout->addWidget(this->stationView);

    connect(addtrainButton,SIGNAL(clicked()),this,SLOT(addTrain()));
    connect(deletetrainButton,SIGNAL(clicked()),this,SLOT(deleteTrain()));
    connect(editstationButton,SIGNAL(clicked()),this,SLOT(editStation()));
    connect(closeButton,SIGNAL(clicked(bool)),this,SLOT(accept()));
    trainView->setCurrentIndex(trainModel->index(0,0));

}
enum
{

    Trains_trainnumber=0,
    Trains_seattype=1,
    Trains_speedtype=2
};

void ManagerView::createTrainPanel()
{
    trainModel=new QSqlRelationalTableModel(this);
    //设置火车线路视图
    trainModel->setTable("trains");
    trainModel->setSort(Trains_trainnumber,Qt::AscendingOrder);
    trainModel->setHeaderData(Trains_trainnumber,Qt::Horizontal,tr("trainnumber"));
    trainModel->setHeaderData(Trains_seattype,Qt::Horizontal,tr("seattype"));
    trainModel->setHeaderData(Trains_speedtype,Qt::Horizontal,tr("speedtype"));
    trainModel->select();

    trainView=new QTableView;
    trainView->setModel(trainModel);
    trainView->setItemDelegate(new QSqlRelationalDelegate(this));
    trainView->setSelectionMode(QAbstractItemView::SingleSelection);
    trainView->setSelectionBehavior(QAbstractItemView::SelectRows);
    trainView->resizeColumnsToContents();

    trainView->horizontalHeader()->setStretchLastSection(true);

    trainView->verticalHeader()->setHidden(true);


    trainLabel=new QLabel(tr("Train"));
    trainLabel->setBuddy(trainView);
    connect(trainView->selectionModel(),SIGNAL(currentRowChanged(const QModelIndex&,const QModelIndex&)),this,SLOT(updateStationView()));
}

enum
{

    Stations_id,
    Stations_trainnumber,
    Stations_starttime,
    Stations_arrivetime,
    Stations_stationid,
    Stations_miles,
    Stations_bookednumber

};

void ManagerView::createStationPanel()
{
    stationModel=new QSqlRelationalTableModel(this);
    stationModel->setTable("trainstations");
    stationModel->setSort(Stations_id,Qt::AscendingOrder);
    stationModel->setRelation(Stations_stationid,QSqlRelation("stations","id","name"));
    stationModel->setHeaderData(Stations_id,Qt::Horizontal,tr("id"));
    stationModel->setHeaderData(Stations_trainnumber,Qt::Horizontal,tr("trainnumber"));
    stationModel->setHeaderData(Stations_starttime,Qt::Horizontal,tr("starttime"));
    stationModel->setHeaderData(Stations_arrivetime,Qt::Horizontal,tr("arrivetime"));
    stationModel->setHeaderData(Stations_stationid,Qt::Horizontal,tr("stationname"));

    stationView=new QTableView;
    stationView->setModel(stationModel);
    stationView->setSelectionMode(QAbstractItemView::SingleSelection);
    stationView->setSelectionBehavior(QAbstractItemView::SelectRows);
    stationView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    stationView->horizontalHeader()->setStretchLastSection(true);

    stationView->setColumnHidden(Stations_id, true);
    stationView->setColumnHidden(Stations_miles, true);
    stationView->setColumnHidden(Stations_bookednumber, true);


    stationLabel=new QLabel(tr("S&tations"));
    stationLabel->setBuddy(stationView);

}
void ManagerView::updateStationView()
{
    QModelIndex index=trainView->currentIndex();
    if(index.isValid())
    {
        QSqlRecord record=trainModel->record(index.row());
        QString id=record.value("trainnumber").toString();
        stationModel->setFilter(QString("trainnumber= '%1'").arg((id)));
    }
    else
    {
        stationModel->setFilter("trainnumber= -1");
        stationLabel->setText(tr("S&tations"));
    }
    stationModel->select();
    stationView->horizontalHeader()->setVisible(stationModel->rowCount()>0);
}
void ManagerView::addTrain()
{
    int row=trainModel->rowCount();
    trainModel->insertRow(row);
    QModelIndex index=trainModel->index(row,Trains_trainnumber);
    trainView->setCurrentIndex(index);
    trainView->edit(index);
}
void ManagerView::deleteTrain()
{
    QModelIndex index=trainView->currentIndex();
    if(!index.isValid())
        return;
    QSqlDatabase::database().transaction();
    QSqlRecord record=trainModel->record(index.row());
    int id=record.value(Trains_trainnumber).toInt();
    int numStations=0;

    QSqlQuery query(QString("SELECT COUNT(*)FROM stations""WHERE trainnumber=%1").arg(id));
    if(query.next())
        numStations=query.value(0).toInt();
    if(numStations>0)
    {
        int r=QMessageBox::warning(this,tr("Delete Train"),tr("Delete %1 and all its stations?").arg(record.value(Trains_trainnumber).toString()),QMessageBox::Yes|QMessageBox::No);
        if (r==QMessageBox::No)
        {
            QSqlDatabase::database().rollback();
            return;
        }
        query.exec(QString("DELETE FROM stations""WHERE trainnumber=%1").arg(id));
    }
    trainModel->removeRow(index.row());
    trainModel->submitAll();
    QSqlDatabase::database().commit();

    updateStationView();
    trainView->setFocus();
}
void ManagerView::editStation()
{
    int stationId=-1;
    QModelIndex index=stationView->currentIndex();
    if(index.isValid())
    {
        QSqlRecord record=stationModel->record(index.row());
        stationId=record.value(Stations_id).toInt();
    }
    TrainStationForm form1(stationId,this);
    form1.exec();
    updateStationView();
}
