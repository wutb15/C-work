#ifndef MANAGER_H
#define MANAGER_H
#include"Handle.h"
#include "QWidget"
#include "QSqlRelationalTableModel"

class Manager:public Handle
{
public:
      Manager(QSqlRecord&src);
      ~Manager(){delete record;}
      QSqlRecord toSqlRecord();
      void  load(QSqlRecord& src);


};

class ManagerView:public QWidget
{
    Q_OBJECT
private slots:
    void editTrain();
    void editStation();
private:
    void createTrainPanel();
    void createStationPanel();
    QSqlRelationalTableModel *trainModel;
    QSqlRelationalTableModel *stationModel;
    QWidget *trainPanel;
    QWidget *stationPanel;
};

#endif // MANAGER_H
