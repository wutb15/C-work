#ifndef BASICDATA_H
#define BASICDATA_H
#include<QSql>
#include<QSqlRecord>

class BasicData
{
public:
    BasicData(Q);
    ~BasicData();
    void load(QSqlRecord& record);
    QSqlRecord& toQSqlRecord();
protected:
    QSqlRecord* record;
};

#endif // BASICDATA_H
