#include "form.h"
#include "QWidget"
#include "QTableWidget"
Form::Form(QWidget *parent) :
    QDialog(parent)
{
    ui.setupUi(this);



}


void Form::createconnections()
{
    connect(ui.firstButton,SIGNAL(clicked()),this->mapper,SLOT(toFirst()));
    connect(ui.lastButton,SIGNAL(clicked()),this->mapper,SLOT(toLast()));
    connect(ui.nextButton,SIGNAL(clicked()),this->mapper,SLOT(toNext()));
    connect(ui.previousButton,SIGNAL(clicked()),this->mapper,SLOT(toPrevious()));
    connect(ui.addButton,SIGNAL(clicked()),this,SLOT(addItem()));
    connect(ui.deleteButton,SIGNAL(clicked()),this,SLOT(deleteItem()));
    connect(ui.confirmButton,SIGNAL(clicked(bool)),this->mapper,SLOT(submit()));
    connect(ui.confirmButton,SIGNAL(clicked(bool)),this,SLOT(close()));
}


