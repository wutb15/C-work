#ifndef PROFILEFORM_H
#define PROFILEFORM_H
#include"form.h"


#include<QWidget>
#include<QLabel>
#include<QLineEdit>
#include<QComboBox>
class ProfileForm : public Form
{
    Q_OBJECT
public:
    explicit ProfileForm(int id,QWidget* parent=0);
private:
    void addItem();
    void delteItem();
    void createContents();
    void createMap();


    QLabel* nameLabel;
    QLineEdit* nameEdit;

    QLabel* sexLabel;
    QComboBox* sexCombo;

    QLabel* phoneLabel;
    QLineEdit* phoneEdit;

    QLabel* cardIdLabel;
    QLineEdit* cardIdEdit;

};

#endif // PROFILEFORM_H
