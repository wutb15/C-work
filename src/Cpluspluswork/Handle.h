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
    void    setusername(QString src);
    void    setpassword(QString src);
    virtual ~Handle();
    Handle();
    virtual QSqlRecord& toSqlRecord();
    virtual void  load(QSqlRecord& src);

};

#endif // HANDLE_H
