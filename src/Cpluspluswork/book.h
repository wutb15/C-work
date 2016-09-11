#ifndef BOOK_H
#define BOOK_H
#include <QDialog>
#include"Handle.h"
#include"User.h"
#include"BasicData/basicdata.h"
namespace Ui {
    class book;
}

class book : public QDialog
{
    Q_OBJECT

public:
    explicit book( User* user, Train* train, Profile* profile,
                  int seatnumber,int beginnumber,int endnumber,QWidget *parent = 0);
    ~book();

private:
    Ui::book *ui;
    User* passenger;
    Profile* profile;
    Train* train;
    int seatnumber;
    int beginnumber;
    int endnumber;


    void createTicket(QString trainnumer,int seatnumber,int beginnumber,int endnumber,int profile_id,QString username);

    void addNumber();



private slots:
   void on_bookButton_clicked();
   void on_exitButton_clicked();
};
#endif // BOOK_H
