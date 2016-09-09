#ifndef MANAGERVIEW_H
#define MANAGERVIEW_H
#include <QDialog>

namespace Ui {
    class ManagerView;
}
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
#endif // MANAGERVIEW_H
