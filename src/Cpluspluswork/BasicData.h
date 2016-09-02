#ifndef BASICDATA_H
#define BASICDATA_H
#include<QSql>
#include<QSqlRecord>

class BasicData
{
public:
    BasicData(QSqlRecord &src);
    ~BasicData();
    void load(QSqlRecord& record);
    QSqlRecord& toQSqlRecord();
protected:
    QSqlRecord* record;
};

class Profile:public BasicData
{
protected:
    int id;
    QString sex;
    QString name;
    QString cardid;
    QString phone;
    QString username;
public:
    void load(QSqlRecord src);
    QSqlRecord toQSqlRecord();
    Profile(QSqlRecord src);
};

class Train: public BasicData
{
protected:
    QString trainnumber;
    int seattype;
    int speedtype;
public:
    void load(QSqlRecord src);
    QSqlRecord toQSqlRecord();
    Train(QSqlRecord src);
};

class Station:public BasicData
{
protected:
    int id;
    QString name;
    QString province;
public:
    void load(QSqlRecord src);
    QSqlRecord toQSqlRecord();
    Train(QSqlRecord src);
};
class TrainStation:public BasicData
{
protected:
    QTime arrivetime;
    QTime starttiem;
    int   id;
    int   number;
    QString trainnumber;
    int station_id;
public:
    void load(QSqlRecord src);
    QSqlRecord toQSqlRecord();
    Train(QSqlRecord src);
};
class Ticket:public BasicData
{
protected:
    int id;
    int profile_id;
    int seatnumber;
    int beginstation_id;
    int endstation_id;
public:
    void load(QSqlRecord src);
    QSqlRecord toQSqlRecord();
    Train(QSqlRecord src);


}

#endif // BASICDATA_H
