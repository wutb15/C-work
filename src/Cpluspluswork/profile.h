#ifndef PROFILE_H
#define PROFILE_H
#include <QDialog>
#include "User.h"

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
    QWidget *profilePanel;
    QTableView *profileView;
    QPushButton *changeButton;
    QPushButton *backButton;
private slots:
    void on_changeButton_clicked();
    void on_backButton_clicked();
};

#endif // PROFILE_H
