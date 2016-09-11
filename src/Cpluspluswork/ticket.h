#ifndef TICKET_H
#define TICKET_H
#include <QDialog>
#include "User.h"
#include <QTableView>
namespace Ui {
    class TicketView;
}

class TicketView : public QDialog
{
    Q_OBJECT

public:
    explicit TicketView(User * user0,QWidget *parent = 0);
    ~TicketView();

private:
    Ui::TicketView *ui;
    User *user;
    void createTicketPanel();
    QSqlRelationalTableModel *ticketModel;
    QWidget *ticketPanel;
    QTableView *ticketView;
    QPushButton *backButton;
private slots:
    void on_backButton_clicked();
};
#endif // TICKET_H
