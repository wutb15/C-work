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
    void    setpassword(QString src);
    virtual ~Handle();
    Handle(){}
    virtual QSqlRecord toSqlRecord()=0;
    virtual void  load(QSqlRecord& src)=0;

private:
    virtual void submit()=0;

};

#endif // HANDLE_H
