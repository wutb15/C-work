#include "basicdata.h"
#include"../BasicDataField.h"

BasicData::BasicData()
{

}

QSqlRecord BasicData::toSqlRecord()
{
    return *_record;

}







Train::Train(QSqlRecord &src)
{
    this->seattype=static_cast<SeatType>(src.value("seattype").toInt());
    this->speedtype=static_cast<SpeedType>(src.value("speedtype").toInt());
    this->trainnumber=src.value("trainnumber").toString();
    _record=new QSqlRecord(src);
}

void Train::load(QSqlRecord &src)
{
    delete _record;
    this->seattype=static_cast<SeatType>(src.value("seattype").toInt());
    this->speedtype=static_cast<SpeedType>(src.value("speedtype").toInt());
    this->trainnumber=src.value("trainnumber").toString();
    _record=new QSqlRecord(src);

}

QList<TrainStation> Train::getstations()
{
    QSqlTableModel search;
    search.setTable("trainstations");
    QString filter="trainnumber ='"+trainnumber+"'";
    search.setFilter(filter);
    search.select();
    QList<TrainStation> result;
    for(int i=0;i<search.rowcount();i++)
    {
        TrainStation temp(search.record(i));
        result.append(temp);
    }

    return result;

}

TrainStation Train::getstation(int number)
{
    QSqlTableModel search;
    search.setTable("trainstations");
    QString filter="trainnumber ='"+trainnumber+"'";
    search.setFilter(filter);
    search.setSort(static_cast<int>(TrainStationField::TrainStation_Miles),Qt::AscendingOrder);
    search.select();
    return TrainStation(search.record(number));


}










Station::Station(QSqlRecord &src)
{
    this->id=src.value("id").toInt(0);
    this->name=src.value("name").toString();
    this->province=src.value("province").toString();
    _record=new QSqlRecord(src);
}

void Station::load(QSqlRecord &src)
{
    delete _record;
    this->id=src.value("id").toInt(0);
    this->name=src.value("name").toString();
    this->province=src.value("province").toString();
    _record=new QSqlRecord(src);
}









TrainStation::TrainStation(QSqlRecord &src)
{
    _record=new QSqlRecord(src);
    this->id=src.value("id").toInt();
    this->arrivetime=src.value("arrivetime").toTime();
    this->starttime=src.value("starttime").toTime();
    this->station_id=src.value("station_id").toInt();
    this->miles=src.value("miles").toInt();
    this->trainumber=src.value("trainnumber").toString();
    this->bookednumber=src.value("bookednumber").toInt();
}

void TrainStation::load(QSqlRecord &src)
{
    delete _record;
    _record=new QSqlRecord(src);
    this->id=src.value("id").toInt();
    this->arrivetime=src.value("arrivetime").toTime();
    this->starttime=src.value("starttime").toTime();
    this->station_id=src.value("station_id").toInt();
    this->miles=src.value("miles").toInt();
    this->trainnumber=src.value("trainnumber").toString();
    this->bookednumber=src.value("bookednumber").toInt();
}








Profile::Profile(QSqlRecord &src)
{
    this->id=src.value("id").toInt();
    this->name=src.value("name").toString();
    this->cardid=src.value("cardid").toString();
    this->phone=src.value("phone").toString();
    this->sex=src.value("sex").toString();
    this->username=src.value("username").toString();
    _record=new QSqlRecord(src);
}

void Profile::load(QSqlRecord &src)
{
    delete _record;
    this->id=src.value("id").toInt();
    this->name=src.value("name").toString();
    this->cardid=src.value("cardid").toString();
    this->phone=src.value("phone").toString();
    this->sex=src.value("sex").toString();
    this->username=src.value("username").toString();
    record=new QSqlRecord(src);
}







Ticket::Ticket(QSqlRecord &src)
{
    this->id=src.value("id").toInt();
    this->seatnumber=src.value("seatnumber").toInt();
    this->trainnumber=src.value("trainnumber").toString();
    this->beginnumber=src.value("beginnumber").toInt();
    this->endnumber=src.value("endnumber").toInt();
    this->profile_id=src.value("profile_id").toInt();
    _record=new QSqlRecord(src);
}

void Ticket::load(QSqlRecord &src)
{
    delete _record;
    this->id=src.value("id").toInt();
    this->seatnumber=src.value("seatnumber").toInt();
    this->trainnumber=src.value("trainnumber").toString();
    this->beginnumber=src.value("beginnumber").toInt();
    this->endnumber=src.value("endnumber").toInt();
    this->profile_id=src.value("profile_id").toInt();
    _record=new QSqlRecord(src);
}

