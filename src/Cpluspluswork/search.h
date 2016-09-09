#ifndef SEARCH_H
#define SEARCH_H
#include <QDialog>

namespace Ui {
    class SearchView;
}

class SearchView : public QDialog
{
    Q_OBJECT

public:
    explicit SearchView(QWidget *parent = 0);
    ~SearchView();

private:
    Ui::SearchView *ui;

private slots:
    void on_bookButton_clicked();
};

#endif // SEARCH_H
