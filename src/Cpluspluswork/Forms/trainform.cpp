#include "trainform.h"
#include"BasicDataField.h"
class Ui::Form;
TrainForm::TrainForm(const QString &trainnumber,QWidget*parent):Form(parent)
{
    QStringList seatitems;
    seatitems<<tr("Bed")<<tr("Sit");
    seatType=new QStringListModel(seatitems,this);
    QStringList speeditems;
    speeditems<<tr("Normal")
              <<tr("Quick")
              <<tr("Dong")
              <<tr("High");
    speedType=new QStringListModel(speeditems,this);

    createContents();
    createTable();
    createMap();

    if(trainnumber!="")
    {
        for(int row=0;row<tableModel->rowCount();++row)
            {
                QSqlRecord record=tableModel->record(row);
                if(record.value(static_cast<int>(TrainField::Train_Number)).toString()==trainnumber)
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

void TrainForm::createContents()
{
    this->trainnumberEdit=new QLineEdit;

    this->trainnumberLabel=new QLabel(tr("Trainnumber: "));
    this->trainnumberLabel->setBuddy(this->trainnumberEdit);

    this->seatCombo=new QComboBox;

    this->seatLabel=new QLabel(tr("SeatType: "));
    this->seatLabel->setBuddy(this->seatCombo);

    this->seatCombo->setModel(this->seatType);


    this->speedCombo=new QComboBox;

    this->speedLabel=new QLabel(tr("SpeedType: "));
    this->speedLabel->setBuddy(this->speedCombo);

    this->speedCombo->setModel(this->speedType);




    int col_lab=0;
    int col_con=1;

    ui.gridLayout->addWidget(this->trainnumberLabel,0,col_lab);
    ui.gridLayout->addWidget(this->trainnumberEdit,0,col_con);

    ui.gridLayout->addWidget(this->seatLabel,1,col_lab);
    ui.gridLayout->addWidget(this->seatCombo,1,col_con);

    ui.gridLayout->addWidget(this->speedLabel,2,col_lab);
    ui.gridLayout->addWidget(this->speedCombo,2,col_con);


    ui.gridLayout->setColumnStretch(0,1);//改变列宽
    ui.gridLayout->setColumnStretch(1,3);


}

void TrainForm::createTable()
{
    tableModel=new QSqlRelationalTableModel(this);
    tableModel->setTable("trains");
    tableModel->setSort(static_cast<int>(TrainField::Train_Number),Qt::AscendingOrder);
    tableModel->select();

}

void TrainForm::createMap()
{
    mapper=new QDataWidgetMapper(this);
    mapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
    mapper->setModel(tableModel);

    mapper->addMapping(this->trainnumberEdit,static_cast<int>(TrainField::Train_Number));
    mapper->addMapping(this->seatCombo,static_cast<int>(TrainField::Train_SeatType));
    mapper->addMapping(this->speedCombo,static_cast<int>(TrainField::Train_SpeedType));


}


void TrainForm::addItem()
{
    int row=mapper->currentIndex();
    mapper->submit();
    tableModel->insertRow(row);
    mapper->setCurrentIndex(row);

    this->trainnumberEdit->clear();
    trainnumberEdit->setFocus();

}

void TrainForm::deleteItem()
{
    int row=mapper->currentIndex();
    tableModel->removeRow(row);
    mapper->submit();
    mapper->setCurrentIndex(qMin(row,tableModel->rowCount()-1));
}
