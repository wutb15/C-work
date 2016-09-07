#include "trainstationform.h"
#include<QSqlRelationalDelegate>
TrainStationForm::TrainStationForm(int id,QWidget* parent):Form(parent)
{


    createContents();
    createTable();
    createMap();

    if(id!=-1)
    {
        for(int row=0;row<tableModel->rowCount();++row)
            {
                QSqlRecord record=tableModel->record(row);
                if(record.value(static_cast<int>(TrainField::Train_Number)).toInt()==id)
                {
                    mapper->setCurrentIndex(row);
                    break;
                }
            }
    }
    else
    {
        mapper->toFirst();
    }

}


void TrainStationForm::createContents()
{
    this->trainnumberCombo=new QComboBox;

    this->trainnumberLabel=new QLabel("Trainnumber: ");
    this->trainnumberLabel->setBuddy(this->trainnumberCombo);
    this->trainnumberCombo->hidePopup();

    this->starttimeEdit=new QTimeEdit;

    this->starttimeLabel=new QLabel("Starttime: ");
    this->starttimeLabel->setBuddy(this->starttimeEdit);

    this->arrivetimeEdit=new QTimeEdit;

    this->arrivetimeLabel=new QLabel("ArriveTime: ");
    this->arrivetimeLabel->setBuddy(this->arrivetimeEdit);

    this->stationCombo=new QComboBox;

    this->stationLabel=new QLabel("Station : ");
    this->stationLabel->setBuddy(this->stationCombo);

    this->milesEdit=new QSpinBox;

    this->milesLabel=new QLabel("Miles From the start: ");
    this->milesLabel->setBuddy(this->milesEdit);

    this->bookedEdit=new QSpinBox;

    this->bookedLabel=new QLabel("Booked ");
    this->bookedLabel->setBuddy(this->bookedEdit);





    //add to layout

    int col_lab=0;
    int col_con=1;

    ui.gridLayout->addWidget(this->trainnumberLabel,0,col_lab);
    ui.gridLayout->addWidget(this->trainnumberCombo,0,col_con);

    ui.gridLayout->addWidget(this->arrivetimeLabel,1,col_lab);
    ui.gridLayout->addWidget(this->arrivetimeEdit,1,col_con);

    ui.gridLayout->addWidget(this->starttimeLabel,2,col_lab);
    ui.gridLayout->addWidget(this->starttimeEdit,2,col_con);

    ui.gridLayout->addWidget(this->stationLabel,3,col_lab);
    ui.gridLayout->addWidget(this->stationCombo,3,col_con);

    ui.gridLayout->addWidget(this->milesLabel,4,col_lab);
    ui.gridLayout->addWidget(this->milesEdit,4,col_con);

    ui.gridLayout->addWidget(this->bookedLabel,5,col_lab);
    ui.gridLayout->addWidget(this->bookedEdit,5,col_con);



    ui.gridLayout->setColumnStretch(0,1);//改变列宽
    ui.gridLayout->setColumnStretch(1,3);





}


void TrainStationForm::createTable()
{

    tableModel=new QSqlRelationalTableModel(this);

    tableModel->setTable("trainstations");
    tableModel->setRelation(static_cast<int>(TrainStationField::TrainStation_TrainNumber),
                            QSqlRelation("trains","trainnumber","trainnumber"));
    tableModel->setRelation(static_cast<int>(TrainStationField::TrainStation_Station_Id),
                            QSqlRelation("stations","id","name"));

    tableModel->setSort(static_cast<int>(TrainStationField::TrainStation_Number),Qt::AscendingOrder);
    tableModel->select();


    QSqlTableModel* relationModel=tableModel->relationModel(static_cast<int>(TrainStationField::TrainStation_TrainNumber));
    this->trainnumberCombo->setModel(relationModel);
    this->trainnumberCombo->setModelColumn(
                relationModel->fieldIndex("trainnumber"));

    QSqlTableModel* relationModel2=tableModel->relationModel(static_cast<int>(TrainStationField::TrainStation_Id));

    this->stationCombo->setModel(relationModel2);
    this->stationCombo->setModelColumn(
                relationModel2->fieldIndex("name"));





}

void TrainStationForm::createMap()
{
    mapper=new QDataWidgetMapper(this);

    mapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
    mapper->setModel(tableModel);
    mapper->setItemDelegate(new QSqlRelationalDelegate(this));
    mapper->addMapping(this->trainnumberCombo,static_cast<int>(TrainStationField::TrainStation_TrainNumber));
    mapper->addMapping(this->starttimeEdit,static_cast<int>(TrainStationField::TrainStation_StartTime));
    mapper->addMapping(this->arrivetimeEdit,static_cast<int>(TrainStationField::TrainStation_ArriveTime));
    mapper->addMapping(this->stationCombo,static_cast<int>(TrainStationField::TrainStation_Station_Id));
    mapper->addMapping(this->bookedEdit,static_cast<int>(TrainStationField::TrainStation_BookedNumber));
    mapper->addMapping(this->milesEdit,static_cast<int>(TrainStationField::TrainStation_Miles));



}

void TrainStationForm::addItem()
{
    int row=mapper->currentIndex();
    mapper->submit();
    tableModel->insertRow(row);
    mapper->setCurrentIndex(row);

    this->milesEdit->clear();
    this->bookedEdit->clear();
    this->arrivetimeEdit->clear();
    this->starttimeEdit->clear();


    this->arrivetimeEdit->setFocus();
    //TODO
}

void TrainStationForm::deleteItem()
{
    int row=mapper->currentIndex();
    tableModel->removeRow(row);
    mapper->submit();
    mapper->setCurrentIndex(qMin(row,tableModel->rowCount()-1));


}
