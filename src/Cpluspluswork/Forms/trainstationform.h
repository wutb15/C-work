#ifndef TRAINSTATIONFORM_H
#define TRAINSTATIONFORM_H

#include <QWidget>
#include<QLabel>
#include<QLineEdit>
#include<QComboBox>
#include<QTimeEdit>
#include<QTime>
#include<QSpinBox>
#include"form.h"
class TrainStationForm : public Form
{
public:
    TrainStationForm(int id,QWidget* parent);
private:
    void addItem();
    void deleteItem();


    void createContents();
    void createMap();
    void createTable();

    QLabel* trainnumberLabel;
    QComboBox* trainnumberCombo;

    QLabel* starttimeLabel;
    QTimeEdit* starttimeEdit;//editable

    QLabel* arrivetimeLabel;
    QTimeEdit* arrivetimeEdit;//editable

    QLabel* stationLabel;
    QComboBox* stationCombo;

    QLabel* milesLabel;
    QSpinBox* milesEdit;//editable

    QLabel* bookedLabel;
    QSpinBox* bookedEdit;//editable



};

#endif // TRAINSTATIONFORM_H
