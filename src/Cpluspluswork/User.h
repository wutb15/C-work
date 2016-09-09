#ifndef USER_H
#define USER_H
#include"Handle.h"
#include"BasicData/basicdata.h"

class User : public Handle
{
protected:
    double money;
    QString extrainformation;
    QList<Profile*> profiles;
public:
    User(QSqlRecord &src);
    ~User();
    QSqlRecord toSqlRecord();
    void load(QSqlRecord &src);
    void charge(double money);
    bool pay(double money);
    QList<Profile*> getprofiles();
    Profile*        getprofile(int number=0);

};

#endif // USER_H
