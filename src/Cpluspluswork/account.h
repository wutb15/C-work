#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <QDialog>

namespace Ui {
    class AccountView;
}

class AccountView : public QDialog
{
    Q_OBJECT

public:
    explicit AccountView(QWidget *parent = 0);
    ~AccountView();

private:
    Ui::AccountView *ui;

private slots:
    void on_pwdButton_clicked();
};

#endif // ACCOUNT_H
