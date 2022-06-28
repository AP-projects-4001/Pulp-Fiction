#ifndef CHANNELCLASS_H
#define CHANNELCLASS_H

#include <QString>
#include <QVector>
#include "baseclass.h"

class channelClass : public baseClass
{
public:
    channelClass(int ID , QString nameChannel , int IDC , QVector<int> memId,QVector<QString> nameMem ,
                 QVector<int> ADID,QVector<QString> Admins, QVector<QString> messageChannel);

    int getIDchannel() const {return IDchannel;}
    bool getAdmin() const{return isAdmin;}
private:
    int IDchannel;
    bool isAdmin = false;
};

#endif // CHANNELCLASS_H
