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

void Handle::setusername(QString src)
{
    this->username=username;
}

void Handle::setpassword(QString src)
{
    this->password=src;
}


Handle::~Handle()
{

}

