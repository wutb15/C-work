#ifndef PROFILE_H
#define PROFILE_H
#include <QDialog>
#include "User.h"
#include<QTableView>
namespace Ui {
    class ProfileView;
}

class ProfileView : public QDialog
{
    Q_OBJECT

public:
    explicit ProfileView(User * user0,QWidget *parent = 0);
    ~ProfileView();

private:
    Ui::ProfileView *ui;
    User *user;
    void createProfilePanel();
    QSqlRelationalTableModel *profileModel;
    QTableView *profileView;

    void updateview();
private slots:

    void on_changeButton_clicked();
    void on_closeButton_clicked();
    void on_switchButton_clicked();
};

#endif // PROFILE_H
