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
private slots:
    on_searchButton_clicked();
    on_pwdButton_clicked();
    on_infoButton_clicked();
    on_ticketButton_clicked();

};
#endif // USERVIEW_H
