#ifndef MANAGERVIEW_H
#define MANAGERVIEW_H
#include <QDialog>
#include <QSqlRelationalTableModel>
#include <QDialogButtonBox>
#include<QTableView>
#include <QLabel>
namespace Ui {
    class ManagerView;
}
class ManagerView:public QWidget
{
    Q_OBJECT
public:
    explicit ManagerView(QWidget *parent = 0);
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
};
#endif // MANAGERVIEW_H
