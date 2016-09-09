#ifndef SEAT_H
#define SEAT_H
#include <QDialog>

namespace Ui {
    class SeatView;
}

class SeatView : public QDialog
{
    Q_OBJECT

public:
    explicit SeatView(QWidget *parent = 0);
    ~SeatView();

private:
    Ui::SeatView *ui;

private slots:
    void on_bookButton_clicked();
};

#endif // SEAT_H
