#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <QDialog>
#include"User.h"

namespace Ui {
    class AccounView;
}

class AccountView : public QDialog
{
    Q_OBJECT

public:
    explicit AccountView(User* user,QWidget *parent = 0);
    ~AccountView();

private:
    Ui::AccounView *ui;
    User* user;


private slots:
    void on_pwdButton_clicked();
};

#endif // ACCOUNT_H