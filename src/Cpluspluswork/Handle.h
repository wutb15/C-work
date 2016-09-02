#ifndef HANDLE_H
#define HANDLE_H
#include<QString>
#include<QSqlRecord>
#include<QSql>
enum class HandleType
{
    User,
    Manager
};


class Handle
{
protected:
    QString	username;
    QString password;
    QSqlRecord* record;

public:
    QString getusername();
    QString getpassword();
    void    setusername(Qstring src);
    void    setpassword(Qstring src);
    virtual ~Handler();
    Handler();
    virtual QSqlRecord& toSqlRecord();
    virtual void  load(QSqlRecord& src);

};

#endif // HANDLE_H
