#ifndef MANAGER_H
#define MANAGER_H
#include"Handle.h"

class Manager:public Handle
{
public:
      Manager(QSqlRecord&src);
      ~Manager(){}//TODO
      //QSqlRecord& toSqlRecord(){}
      void  load(QSqlRecord& src){}//TODO

};

#endif // MANAGER_H
