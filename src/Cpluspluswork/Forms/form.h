#ifndef FORM_H
#define FORM_H

#include "ui_form.h"

class Form : public QDialog
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);

protected:
    Ui::Form ui;
};

#endif // FORM_H
