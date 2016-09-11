#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <QDialog>
#include"User.h"

namespace Ui {
    class AccountView;
}

class AccountView : public QDialog
{
    Q_OBJECT

public:
    explicit AccountView(User* user0,QWidget *parent = 0);
    ~AccountView();

private:
    Ui::AccountView *ui;
    User* user;


private slots:
    void on_pwdButton_clicked();
    void on_backButton_clicked();
};

#endif // ACCOUNT_H
