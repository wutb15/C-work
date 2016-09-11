#include "basicdata.h"
#include"../BasicDataField.h"
#include<QListIterator>

QSqlRecord BasicData::toSqlRecord()
{
    return *_record;

}







Train::Train(QSqlRecord& src)
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

QList<TrainStation*> Train::getstations()
{

    for(auto i:this->trainstations)
    {
        delete i;

    }
    this->trainstations.clear();
    QSqlTableModel search;
    search.setTable("trainstations");
    QString filter="trainnumber ='"+trainnumber+"'";
    search.setFilter(filter);
    search.setSort(static_cast<int>(TrainStationField::TrainStation_Miles),Qt::AscendingOrder);
    search.select();
    for(int i=0;i<search.rowCount();i++)
    {
        TrainStation* temp=new TrainStation(search.record(i));
        this->trainstations.append(temp);
    }


    return this->trainstations;

}

TrainStation* Train::getstation(int number)
{
    return this->getstations().at(number);


}

int Train::getindex(int station_id)
{
    QList<TrainStation*> temp=this->getstations();
    for(int i=0;i<temp.size();i++)
    {
        if(temp.at(i)->getstation_id()==station_id)
        {
            return i;
            break;
        }

    }
    return -1;
}


Train::~Train()
{
    delete _record;
    for(auto i:this->trainstations)
    {
        delete i;

    }
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









TrainStation::TrainStation(QSqlRecord& src)
{
    _record=new QSqlRecord(src);
    this->id=src.value("id").toInt();
    this->arrivetime=src.value("arrivetime").toTime();
    this->starttime=src.value("starttime").toTime();
    this->station_id=src.value("station_id").toInt();
    this->miles=src.value("miles").toInt();
    this->trainnumber=src.value("trainnumber").toString();
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

Station* TrainStation::getstation()
{
    delete _station;
    QSqlTableModel model;
    model.setTable("stations");
    model.setFilter(QString("id = %1").arg(station_id));
    model.select();
    if(model.rowCount()==1)
    {
        _station=new Station(model.record(0));
    }
    return _station;
}








Profile::Profile(QSqlRecord& src)
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
    _record=new QSqlRecord(src);
}







Ticket::Ticket(QSqlRecord &src)
{
    this->id=src.value("id").toInt();
    this->seatnumber=src.value("seatnumber").toInt();
    this->trainnumber=src.value("trainnumber").toString();
    this->beginnumber=src.value("beginnumber").toInt();
    this->endnumber=src.value("endnumber").toInt();
    this->profile_id=src.value("profile_id").toInt();
    this->username=src.value("username").toString();
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

Profile Ticket::getProfile()
{
    QSqlTableModel model;
    model.setTable("profiles");
    QString filter="id = '"+QString(this->profile_id)+"'";
    model.setFilter(filter);
    if(model.rowCount()==1)
    {
        return Profile(model.record(0));
    }
}


