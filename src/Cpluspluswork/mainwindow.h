#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"Handle.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_exitButton_clicked();
    void on_logButton_clicked();
    void on_newButton_clicked();
private:
    Ui::MainWindow *ui;
    Handle* handler;
    HandleType type;
};

#endif // MAINWINDOW_H
