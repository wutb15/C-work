#ifndef PROFILE_H
#define PROFILE_H
#include <QDialog>

namespace Ui {
    class ProfileView;
}

class ProfileView : public QDialog
{
    Q_OBJECT

public:
    explicit ProfileView(QWidget *parent = 0);
    ~ProfileView();

private:
    Ui::ProfileView *ui;

private slots:
    void on_changeButton_clicked();

};

#endif // PROFILE_H
