#include "form.h"

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
}

void Form::on_addButton_clicked()
{
   this->addItem();
}

void Form::on_deleteButton_clicked()
{
    this->delteItem();
}
