#include "User.h"
#include<QVariant>
User::User(QSqlRecord &src)
{
    username=src.value("username").toString();
    password=src.value("password").toString();
    money=src.value("money").toDouble();
    extrainformation=src.value("extrainformation").toString();

}
