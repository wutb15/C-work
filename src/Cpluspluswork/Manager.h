#ifndef MANAGER_H
#define MANAGER_H
#include"Handle.h"
#include <QWidget>

class Manager:public Handle
{
public:
      Manager(QSqlRecord src);
      ~Manager(){delete record;}
      QSqlRecord toSqlRecord();
      void  load(QSqlRecord& src);
private:
      void submit();


};

#endif // MANAGER_H
