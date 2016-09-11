#include "Handle.h"
#include<QVariant>

QString Handle::getpassword()
{
    return this->password;
}

QString Handle::getusername()
{
    return this->username;

}

void Handle::setpassword(QString src)
{
    this->password=src;
    record->setValue(1,password);

    submit();

}



Handle::~Handle()
{

}

