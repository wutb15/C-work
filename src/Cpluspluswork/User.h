#ifndef USER_H
#define USER_H
#include"Handle.h"

class User : public Handle
{
protected:
    int personalprofile_id;
    QString extrainformation;
public:
    void booktickets(Profile* profile,int begin_id,int end_id);
    User(QSqlRecord &src);
    QSqlRecord& toSqlRecord();
    void load(QSqlRecord &src);

};

#endif // USER_H
