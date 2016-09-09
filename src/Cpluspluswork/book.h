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
    explicit book(const Handle* handler,QWidget *parent = 0);
    ~book();

private:
    Ui::book *ui;
    User* passenger;
    Profile* profile;



private slots:
   void on_bookButton_clicked();
   void on_exitButton_clicked();
};
#endif // BOOK_H
