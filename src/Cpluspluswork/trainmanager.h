#ifndef TRAINMANAGER_H
#define TRAINMANAGER_H

#include <QMainWindow>

namespace Ui {
class TrainManager;
}

class TrainManager : public QMainWindow
{
    Q_OBJECT

public:
    explicit TrainManager(QWidget *parent = 0);
    ~TrainManager();

private:
    Ui::TrainManager *ui;
};

#endif // TRAINMANAGER_H
