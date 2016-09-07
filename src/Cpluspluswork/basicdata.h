#ifndef BASICDATA_H
#define BASICDATA_H
#include<QSqlRecord>
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
    BasicData();
    virtual ~BasicData();
protected:
    QSqlRecord* _record;
};

#endif // BASICDATA_H
