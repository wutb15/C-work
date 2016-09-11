#ifndef MANAGERVIEW_H
#define MANAGERVIEW_H
#include <QDialog>
#include <QSqlRelationalTableModel>
#include <QDialogButtonBox>
#include<QTableView>
#include <QLabel>
#include"Manager.h"
namespace Ui {
    class ManagerView;
}
class ManagerView:public QDialog
{
    Q_OBJECT
public:
    explicit ManagerView(Manager* manager,QWidget* parent=0);
    ~ManagerView();
private slots:
    void addTrain();
    void deleteTrain();
    void updateStationView();
    void editStation();
private:
    Ui::ManagerView *ui;
    void createTrainPanel();
    void createStationPanel();
    QSqlRelationalTableModel *trainModel;
    QSqlRelationalTableModel *stationModel;
    QWidget *trainPanel;
    QWidget *stationPanel;
    QLabel *trainLabel;
    QLabel *stationLabel;
    QTableView *trainView;
    QTableView *stationView;
    QDialogButtonBox *buttonBox;
    QPushButton *addtrain;
    QPushButton *deletetrain;
    QPushButton *editstation;
    Manager* manager;
};
#endif // MANAGERVIEW_H
