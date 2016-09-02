#ifndef LOGIN_H
#define LOGIN_H
#include<QDialog>

namespace Ui
{
    class login;
}

class login:public QDialog
{
    Q_OBJECT
public:
    login(QWidget *parent =0);
    ~login();
    int identify;
private:
    Ui::login *uiptr;
private slots:
    void on_logButton_clicked();
    void on_newButton_clicked();
};

#endif // LOGIN_H
