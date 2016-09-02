#ifndef MANAGER_H
#define MANAGER_H
#include"Handle.h"

class Manager:public Handle
{
public:
      Mananger(QSqlRecord&src);
      ~Manager();
      virtual QSqlRecord& toSqlRecord();
      virtual void  load(QSqlRecord& src);

};

#endif // MANAGER_H
