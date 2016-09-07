#ifndef TRAINFORM_H
#define TRAINFORM_H
#include"form.h"
#include <QWidget>

#include<QLabel>
#include<QLineEdit>
#include<QComboBox>
#include<QStringListModel>
enum class SeatType
{
    Bed,
    Sit
};

enum class SpeedType
{
    Normal,
    Quick,
    Dong,
    High
};

class TrainForm : public Form
{
    Q_OBJECT
public:
    TrainForm(const QString& Trainnumber ,QWidget* parent);
private:
    void addItem();
    void deleteItem();


    void createContents();
    void createMap();
    void createTable();

    QLabel* trainnumberLabel;
    QLineEdit* trainnumberEdit;

    QComboBox* seatCombo;
    QLabel*  seatLabel;

    QComboBox* speedCombo;
    QLabel*  speedLabel;

    QStringListModel* seatType;
    QStringListModel* speedType;



};

#endif // TRAINFORM_H
