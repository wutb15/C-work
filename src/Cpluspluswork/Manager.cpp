#include "Manager.h"
#include<QVariant>

Manager::Manager(QSqlRecord& src)
{
    password=src.value("password").toString();
    username=src.value("username").toString();

}
