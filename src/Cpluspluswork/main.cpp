#include "trainmanager.h"
#include <QApplication>
#include"Forms/form.h"
#include<QString>
#include<QSql>
#include<QSqlDatabase>
#include<QMessageBox>
bool createConnection(const QString& path)
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName(path);

    if(!db.open())
    {
        QMessageBox::critical(0,QObject::tr("DataBase Error"),db.lastError().text());

        return false;
    }
    return true;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    const QString path="../../res/database.db3";
    if(!createConnection(path))
    {
        return 1;
    }
    TrainManager w;

    w.show();

    return a.exec();
}
