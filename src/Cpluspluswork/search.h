#ifndef SEARCH_H
#define SEARCH_H
#include <QDialog>
#include"User.h"
#include"BasicData/basicdata.h"

namespace Ui {
    class SearchView;
}

class SearchView : public QDialog
{
    Q_OBJECT

public:
    explicit SearchView( User* user, Profile* profile,QWidget *parent = 0);
    ~SearchView();

private:
    Ui::SearchView *ui;
    User* user;
    Profile* profile;

private slots:
    void on_bookButton_clicked();
    void on_searchButton_clicked();
    void on_startstationBox_currentIndexChanged(int index);
    void on_endstationBox_currentIndexChanged(int index);
};

#endif // SEARCH_H
