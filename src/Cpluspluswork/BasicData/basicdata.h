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
    QList<TrainStation*> getstations();
    TrainStation* getstation(int number);
    QString gettrainnumber()const{return trainnumber;}
    SeatType getseattype()const{return seattype;}
    SpeedType getspeedtype()const{return speedtype;}
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
    int getid()const{return id;}
    QString getname()const{return name;}
    QString province()const{return province;}
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
    int getid()const{return id;}
    int getseatnumber() const{return seatnumber;}
    int gettrainnumber() const{return trainnumber;}

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
    QString gettrainnumber()const{return trainnumber;}
    QTime   getstarttime()const{return starttime;}
    QTime	getarrivetime()const{return arrivetime;}
    int 	getmiles()const{return miles;}
    int 	getbookednumber()const{return bookednumber;}
private:
    int id;
    QString trainnumber;
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
    QString getsex()const{return sex;}
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

}

#endif // BASICDATA_H
