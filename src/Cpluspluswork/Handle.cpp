#include "Handle.h"

Handle::Handle()
{

}

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
    record->setValue("password",password);
    submit();

}



Handle::~Handle()
{

}

