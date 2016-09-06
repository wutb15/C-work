#include "profileform.h"
#include<QRegExpValidator>
class Ui::Form;

ProfileForm::ProfileForm(int id,QWidget* parent):Form(parent)
{


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

    ui.gridLayout->setColumnStretch(0,1);//改变列宽
    ui.gridLayout->setColumnStretch(1,3);



}

void ProfileForm::createMap()
{
    mapper=new QDataWidgetMapper(this);


}

void ProfileForm::addItem()
{

}
