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
    User(QSqlRecord src);
    ~User();
    QSqlRecord toSqlRecord();
    void load(QSqlRecord &src);
    void charge(int money);
    bool pay(int money);
    QList<Profile*> getprofiles();
    Profile*        getprofile();
    int number;//this is the profilenumber;
    void setnumber(int onumber){number=onumber;}
    int getnumber()const{return number;}

    int getmoney() const{ return money;}
private:
    void submit();
};



#endif // USER_H
