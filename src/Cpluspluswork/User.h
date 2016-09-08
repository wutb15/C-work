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
    ~User(){delete record;}
    QSqlRecord toSqlRecord();
    void load(QSqlRecord &src);
    void charge(double money);
    bool pay(double money);

};

#endif // USER_H
