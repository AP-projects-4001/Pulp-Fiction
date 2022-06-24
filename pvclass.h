#ifndef PVCLASS_H
#define PVCLASS_H
#include "baseclass.h"

class pvClass:public baseClass
{
public:
    pvClass(int UID ,int FID,QString name, QVector<QString> messagePV);
private:
    int yourID;
};

#endif // PVCLASS_H
