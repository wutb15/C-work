#include "profileform.h"
#include<QRegExpValidator>
#include"BasicDataField.h"
#include<QSqlRecord>
class Ui::Form;

ProfileForm::ProfileForm(const QString& username, int id,QWidget* parent):Form(parent),_username(username)
{

    createContents();
    createTable();
    createMap();

    if(id!=-1)
    {
        for(int row=0;row<tableModel->rowCount();++row)
        {
            QSqlRecord record=tableModel->record(row);
            if(record.value(static_cast<int>(ProfileField::Profile_Id)).toInt()==id)
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


void ProfileForm::createContents()
{
    sexCombo=new QComboBox;

    sexLabel=new QLabel(tr("Sex: "));
    sexLabel->setBuddy(sexCombo);

    sexCombo->insertItem(0,tr("Female"));
    sexCombo->insertItem(1,tr("Male"));




    nameEdit=new QLineEdit;

    nameLabel=new QLabel(tr("Name: "));
    nameLabel->setBuddy(nameEdit);


    phoneEdit=new QLineEdit;

    phoneLabel=new QLabel(tr("phone: "));
    phoneLabel->setBuddy(phoneEdit);

    cardIdEdit=new QLineEdit;

    cardIdLabel=new QLabel(tr("cardid: "));
    cardIdLabel->setBuddy(cardIdLabel);

    this->usernameEdit=new QLineEdit;

    this->usernameLabel=new QLabel("Username:");
    this->usernameLabel->setBuddy(this->usernameEdit);

    this->usernameEdit->setText(_username);
    this->usernameEdit->setReadOnly(true);



    int col_lab=0;
    int col_con=1;

    ui.gridLayout->addWidget(sexLabel,0,col_lab);
    ui.gridLayout->addWidget(sexCombo,0,col_con);

    ui.gridLayout->addWidget(nameLabel,1,col_lab);
    ui.gridLayout->addWidget(nameEdit,1,col_con);

    ui.gridLayout->addWidget(phoneLabel,2,col_lab);
    ui.gridLayout->addWidget(phoneEdit,2,col_con);

    ui.gridLayout->addWidget(cardIdLabel,3,col_lab);
    ui.gridLayout->addWidget(cardIdEdit,3,col_con);

    ui.gridLayout->addWidget(this->usernameLabel,4,col_lab);
    ui.gridLayout->addWidget(this->usernameEdit,4,col_con);


    ui.gridLayout->setColumnStretch(0,1);//改变列宽
    ui.gridLayout->setColumnStretch(1,3);



}

void ProfileForm::createTable()
{
    tableModel=new QSqlRelationalTableModel(this);
    tableModel->setTable("profiles");
    tableModel->setSort(static_cast<int>(ProfileField::Profile_Id),Qt::AscendingOrder);
    tableModel->setFilter(("username = " + _username));
    tableModel->select();



}

void ProfileForm::createMap()
{
    mapper=new QDataWidgetMapper(this);
    mapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
    mapper->setModel(tableModel);
    mapper->addMapping(sexCombo,static_cast<int>(ProfileField::Profile_Sex));
    mapper->addMapping(this->nameEdit,static_cast<int>(ProfileField::Profile_Name));
    mapper->addMapping(this->usernameEdit,static_cast<int>(ProfileField::Profile_Username));
    mapper->addMapping(this->phoneEdit,static_cast<int>(ProfileField::Profile_Phone));
    mapper->addMapping(this->cardIdEdit,static_cast<int>(ProfileField::Profile_Cardid));





}

void ProfileForm::addItem()
{
    int row=mapper->currentIndex();
    mapper->submit();
    tableModel->insertRow(row);
    mapper->setCurrentIndex(row);



    nameEdit->clear();
    phoneEdit->clear();
    cardIdEdit->clear();
    usernameEdit->setText(_username);


    nameEdit->setFocus();



}

void ProfileForm::deleteItem()
{
    int row=mapper->currentIndex();
    tableModel->removeRow(row);
    mapper->submit();
    mapper->setCurrentIndex(qMin(row,tableModel->rowCount()-1));

}
