#ifndef USERVIEW_H
#define USERVIEW_H
namespace Ui {
    class UserView;
}

class UserView : public QDialog
{
    Q_OBJECT

public:
    explicit UserView(QWidget *parent = 0);
    ~UserView();

private:
    Ui::UserView *ui;
private slots:
    on_searchButton_clicked();
    on_pwdButton_clicked();
    on_infoButton_clicked();


};
#endif // USERVIEW_H
