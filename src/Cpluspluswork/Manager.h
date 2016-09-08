#ifndef MANAGER_H
#define MANAGER_H
#include"Handle.h"

class Manager:public Handle
{
public:
      Manager(QSqlRecord&src);
      ~Manager(){delete record;}
      QSqlRecord toSqlRecord();
      void  load(QSqlRecord& src);


};

#endif // MANAGER_H
