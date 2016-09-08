#ifndef BASICDATA_H
#define BASICDATA_H
#include<QSqlRecord>
#include<QString>
#include"../Forms/trainform.h"
enum class BasicDataType
{
    Train,
    Profile,
    Station,
    TrainStation,
    Ticket
};
class BasicData
{
public:
    BasicData(){}
    virtual ~BasicData(){delete _record;}
    virtual void load(QSqlRecord&src)=0;
    QSqlRecord toSqlRecord();

protected:
    QSqlRecord* _record;
};


class Train:public BasicData
{
public:
    Train(QSqlRecord& src);
    void load(QSqlRecord& src);
 private:
    QString trainnumber;
    SeatType seattype;
    SpeedType speedtype;

};


class Station:public BasicData
{
public:
    Station(QSqlRecord& src);
    void load(QSqlRecord& src);
private:
    int id;
    QString name;
    QString province;

};

class Ticket:public BasicData
{
public:
    Ticket(QSqlRecord& src);
    void load(QSqlRecord& src);
 private:
    int id;
    int profile_id;
    int seatnumber;
    QString trainnumber;
    int beginnumber;
    int endnumber;

};

class TrainStation:public BasicData
{
public:
    TrainStation(QSqlRecord& src);
    void load(QSqlRecord& src);
private:
    int id;
    QString trainumber;
    QTime starttime;
    QTime arrivetime;
    int station_id;
    int miles;
    int bookednumber;

};

class Profile:public BasicData
{
public:
    Profile(QSqlRecord& src);
    void load(QSqlRecord& src);
 private:
    int id;
    QString sex;
    QString name;
    QString cardid;
    QString phone;
    QString username;

}

#endif // BASICDATA_H
