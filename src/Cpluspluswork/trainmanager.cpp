#include "trainmanager.h"
#include "ui_trainmanager.h"

TrainManager::TrainManager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TrainManager)
{
    ui->setupUi(this);
}

TrainManager::~TrainManager()
{
    delete ui;
}
