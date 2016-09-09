#include "form.h"
#include "QWidget"
#include "QTableWidget"
Form::Form(QWidget *parent) :
    QDialog(parent)
{
    ui.setupUi(this);
    ui.buttonBox->addButton(ui.addButton,QDialogButtonBox::ActionRole);
    ui.buttonBox->addButton(ui.deleteButton,QDialogButtonBox::ActionRole);
    connect(ui.firstButton,SIGNAL(clicked(bool)),this->mapper,SLOT(toFirst()));
    connect(ui.lastButton,SIGNAL(clicked(bool)),this->mapper,SLOT(toLast()));
    connect(ui.nextButton,SIGNAL(clicked(bool)),this->mapper,SLOT(toNext()));
    connect(ui.previousButton,SIGNAL(clicked(bool)),this->mapper,SLOT(toPrevious()));


    QVBoxLayout *layout=new QVBoxLayout;
    layout->addWidget(table1);

}

void Form::on_addButton_clicked()
{
   this->addItem();
}

void Form::on_deleteButton_clicked()
{
    this->deleteItem();
}

