#include "channelclass.h"
#include "baseclass.h"
channelClass::channelClass(int UID , QString nameChannel , int IDC , QVector<int> memId,QVector<QString> nameMem ,
      QVector<int> ADID,QVector<QString> Admins, QVector<QString> messageChannel)
{
    ID = UID;
    IDchannel = IDC;
    name = nameChannel;
    QVector<int>::iterator itt;
    for (itt = ADID.begin(); itt != ADID.end(); ++itt) {
         if(ID==*itt)
         {
             isAdmin = true;
             break;
         }
    }
    QVector<int>::iterator ittin;
    for (ittin = memId.begin(); ittin != memId.end(); ++ittin) {
         memberID.push_back(*ittin);
    }


    QVector<QString>::iterator i1;
    for (i1 = nameMem.begin(); i1 != nameMem.end(); ++i1) {
         nameOfmembers.push_back(*i1);
    }

    QVector<QString>::iterator i;
    for (i = Admins.begin(); i != Admins.end(); ++i) {
         nemaOfAdmins.push_back(*i);
    }

    QVector<QString>::iterator i2;
    for (i2 = messageChannel.begin(); i2 != messageChannel.end(); ++i2) {
         messages.push_back(*i2);
    }
}
