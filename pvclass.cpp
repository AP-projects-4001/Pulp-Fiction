#include "pvclass.h"
#include "baseclass.h"
pvClass::pvClass(int UID ,int FID ,QString nameF, QVector<QString> messagePV)
{
    ID= UID;
    yourID = FID;
    name = nameF;
    QVector<QString>::iterator i2;
    for (i2 = messagePV.begin(); i2 != messagePV.end(); ++i2) {
         messages.push_back(*i2);
    }
}
