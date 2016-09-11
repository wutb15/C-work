#ifndef SEAT_H
#define SEAT_H
#include <QDialog>
#include"BasicData/basicdata.h"
#include"User.h"
#include<QTableWidget>

namespace Ui {
    class SeatView;
}

class SeatView : public QDialog
{
    Q_OBJECT

public:
    explicit SeatView(Train* train,int beginnumber,int endnumber, User* user,Profile* profile,QWidget *parent = 0);
    ~SeatView();

private:
    Ui::SeatView *ui;

    Train* train;
    User*  user;
    int beginnumber;
    int endnumber;
    Profile* profile;


    void createChooseArea_B();

    void createChooseArea_S();


private slots:
    void on_bookButton_clicked();
    void on_seats_clicked(const QModelIndex &index);
};

#endif // SEAT_H
