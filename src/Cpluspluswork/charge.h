#ifndef CHARGE_H
#define CHARGE_H

#include <QDialog>
#include"User.h"
namespace Ui {
class Charge;
}

class Charge : public QDialog
{
    Q_OBJECT

public:
    explicit Charge(User* user,QWidget *parent = 0);
    ~Charge();

private slots:
    void on_closeButton_clicked();

    void on_chargeButton_clicked();

private:
    Ui::Charge *ui;
    User* user;
};

#endif // CHARGE_H
