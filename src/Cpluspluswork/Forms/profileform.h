#ifndef PROFILEFORM_H
#define PROFILEFORM_H
#include"form.h"

class Form;
class ProfileForm : public Form
{
    Q_OBJECT
public:
    explicit ProfileForm(int id,QWidget* parent=0);
};

#endif // PROFILEFORM_H
