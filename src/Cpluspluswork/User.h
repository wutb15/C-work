#ifndef USER_H
#define USER_H
#include"Handle.h"

class User : public Handle
{
protected:
    double money;
    QString extrainformation;
public:
    User(QSqlRecord &src);
  //  QSqlRecord& toSqlRecord(){}
    void load(QSqlRecord &src){}//TODO

};

#endif // USER_H
