#ifndef BASICDATA_H
#define BASICDATA_H
#include<QSqlRecord>
#include<QString>
#include<QList>
#include"../Forms/trainform.h"
#include"../BasicDataField.h"
enum class BasicDataType
{
    Train,
    Profile,
    Station,
    TrainStation,
    Ticket
};
//这里的类只用做显示不能更改，更改只能通过qsqltable;
class BasicData
{
public:
    BasicData(){}
    virtual ~BasicData(){delete _record;}
    virtual void load(QSqlRecord& src)=0;
    QSqlRecord toSqlRecord();

protected:
    QSqlRecord* _record;
};

class TrainStation;
class Train:public BasicData
{
public:
    Train(QSqlRecord& src);
    void load(QSqlRecord& src);
    QList<TrainStation*> getstations();
    TrainStation* getstation(int number);
    int getindex(int station_id);
    QString gettrainnumber()const{return trainnumber;}
    SeatType getseattype()const{return seattype;}
    SpeedType getspeedtype()const{return speedtype;}
    ~Train();
 private:
    QString trainnumber;
    SeatType seattype;
    SpeedType speedtype;
    QList<TrainStation*> trainstations;

};


class Station:public BasicData
{
public:
    Station(QSqlRecord& src);
    void load(QSqlRecord& src);
    int getid()const{return id;}
    QString getname()const{return name;}
    QString getprovince()const{return province;}
private:
    int id;
    QString name;
    QString province;

};
class Profile;
class Ticket:public BasicData
{
public:
    Ticket(QSqlRecord& src);
    void load(QSqlRecord& src);
    Profile getProfile();
    int getid()const{return id;}
    int getseatnumber() const{return seatnumber;}
    QString gettrainnumber() const{return trainnumber;}
    QString getusername()const{return username;}
    int getbeginnumber()const{return beginnumber;}
    int getendnumber()const{return endnumber;}


 private:
    int id;
    int profile_id;
    int seatnumber;
    QString trainnumber;
    int beginnumber;
    int endnumber;
    QString username;

};

class TrainStation:public BasicData
{
public:
    TrainStation(QSqlRecord& src);
    void load(QSqlRecord& src);
    QString gettrainnumber()const{return trainnumber;}
    QTime   getstarttime()const{return starttime;}
    QTime	getarrivetime()const{return arrivetime;}
    int 	getmiles()const{return miles;}
    int 	getbookednumber()const{return bookednumber;}
    int		getstation_id()const{return station_id;}
    Station* getstation();
private:
    int id;
    QString trainnumber;
    QTime starttime;
    QTime arrivetime;
    Station* _station;
    int station_id;
    int miles;
    int bookednumber;

};

class Profile:public BasicData
{
public:
    Profile(QSqlRecord* src);
    void load(QSqlRecord& src);
    QString getsex()const{return sex;}
    int 	getid()const{return id;}
    QString getname()const{return name;}
    QString getcardid()const{return cardid;}
    QString getphone()const{return phone;}
    QString getusername()const{return username;}
 private:
    int id;
    QString sex;
    QString name;
    QString cardid;
    QString phone;
    QString username;

};

#endif // BASICDATA_H
