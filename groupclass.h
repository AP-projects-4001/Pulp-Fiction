#ifndef GROUPCLASS_H
#define GROUPCLASS_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include "baseclass.h"

class groupClass : public baseClass
{
public:
    groupClass( int UID ,QString myName ,QString groupName , int IDC , QVector<int> memId,QVector<QString> nameMem ,
    QVector<int> ADID,QVector<QString> Admins, QVector<QString> groupMessage );

    int getIDgroup() const {return IDgroup;}
    bool getAdmin() const{return isAdmin;}
    QString getUserName() const {return userName;}
private:
    int IDgroup;
    bool isAdmin = false;
    QString userName;
};

#endif // GROUPCLASS_H
