#ifndef USERVIEW_H
#define USERVIEW_H
#include "User.h"
namespace Ui {
    class UserView;
}

class UserView : public QDialog
{
    Q_OBJECT

public:
    explicit UserView(User*user0,QWidget *parent = 0);
    ~UserView();

private:
    Ui::UserView *ui;
    User *user;
    Profile* profile;
private slots:
    void  on_searchButton_clicked();
    void on_pwdButton_clicked();
    void on_infoButton_clicked();
    void on_ticketButton_clicked();

    void on_exitButton_clicked();
};
#endif // USERVIEW_H
