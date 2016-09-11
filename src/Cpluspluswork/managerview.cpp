#include "managerview.h"
#include "ui_managerview.h"
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
ManagerView::ManagerView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManagerView)
{
    ui->setupUi(this);
}

ManagerView::~ManagerView()
{
    delete ui;
}
ManagerView::ManagerView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManagerView)
{
    ui->setupUi(this);
    createTrainPanel();
    createStationPanel();
    buttonBox->addButton(tr("addTrain"),QDialogButtonBox::ActionRole);
    buttonBox->addButton(tr("deleteTrain"),QDialogButtonBox::ActionRole);
    buttonBox->addButton(tr("editStation"),QDialogButtonBox::ActionRole);
    QSplitter *layout(Qt::Vertical);//总体设置为竖直方向布局
    layout->addWidget(trainPanel);
    layout->addWidget(stationPanel);
    layout->addWidget(buttonBox);//包含三个按钮：addTrain,deleteTrain,editTrain
    connect(addButton,SIGNAL(clicked()),this,SLOT(addTrain());
    connect(deleteButton,SIGNAL(clicked()),this,SLOT(deleteTrain());
    connect(editButton,SIGNAL(clicked()),this,SLOT(editStation());
    trainView->setCurrentIndex(trainModel->index(0,0));
}
enum
{
    Trains_rowid=0,
    Trains_trainnumber=1,
    Trains_seattype=2,
    Trains_speedtype=3
};

void ManagerView::createTrainPanel()
{
    trainPanel=new QWidget;
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
    trainView->setColumnHidden(Trains_rowid,true);
    trainView->horizontalHeader()->setStretchLastSection(true);

    trainLabel=new QLabel(tr("Train"));
    trainLabel->setBuddy(trainView);
    connect(trainView->selectionModel(),SIGNAL(currentRowChanged(const QModelIndex&,const QModelIndex&)),this,SLOT(updateStationView()));
}

enum
{
    Stations_rowid=0,
    Stations_id=1,
    Stations_trainnumber=2,
    Stations_starttime=3,
    Stations_arrivetime=4,
    Stations_stationid=5,
    Stations_miles=6,
    Stations_bookednumber=7

};

void ManagerView::createStationPanel()
{
    stationPanel=new QWidget;
    stationModel=new QSqlRelationalTableModel(this);
    stationModel->setTable("trainstations");
    stationModel->setSort(Stations_id,Qt::AscendingOrder);
    stationModel->setHeaderData(Stations_id,Qt::Horizontal,tr("id"));
    stationModel->setHeaderData(Stations_trainnumber,Qt::Horizontal,tr("trainnumber"));
    stationModel->setHeaderData(Stations_starttime,Qt::Horizontal,tr("starttime"));
    stationModel->setHeaderData(Stations_arrivetime,Qt::Horizontal,tr("arrivetime"));
    stationModel->select();

    stationView=new QTableView;
    stationView->setModel(stationModel);
    stationView->setSelectionMode(QAbstractItemView::SingleSelection);
    stationView->setSelectionBehavior(QAbstractItemView::SelectRows);
    stationView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    stationView->resizeColumnsToContents();
    stationView->horizontalHeader()->setStretchLastSection(true);
    stationView->setColumnHidden(Stations_rowid, true);
    stationView->setColumnHidden(Stations_stationid, true);
    stationView->setColumnHidden(Stations_miles, true);
    stationView->setColumnHidden(Stations_bookednumber, true);


    stationLabel=new QLabel(tr("Stations"));
    stationLabel->setBuddy(stationView);

}
void ManagerView::updateStationView()
{
    QModelIndex index=trainView->currentIndex();
    if(index.isValid())
    {
        QSqlRecord record=trainModel->record(index.row());
        int id=record.value("trainnumber").toInt();
        stationModel->setFilter(QString("trainnumber=%1").arg((id)));
    }
    else
    {
        stationModel->setFilter("trainnumber=-1");
        stationLabel->setText(tr("Stations"));
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
    int id=record.value(Trains_rowid).toInt();
    int numStations=0;

    QSqlQuery query(QString("SELECT COUNT(*)FROM stations""WHERE rowid=%1").arg(id));
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
        query.exec(QString("DELETE FROM stations""WHERE rowid=%1").arg(id));
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
    if(index.isvalid())
    {
        QSqlRecord record=stationModel->record(index.row());
        stationId=record.value(Stations_id).toInt();
    }
    TrainStationForm form1(stationId,this);
    form1.exec();
    updateStationView();
}
