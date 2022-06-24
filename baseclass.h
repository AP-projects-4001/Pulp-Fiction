#ifndef BASECLASS_H
#define BASECLASS_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

class baseClass
{
public:
    virtual QVector<QString> getNameOfMem()const
    {
        return nameOfmembers;
    }
    virtual QVector<QString> getNameOfAd()const
    {
        return nemaOfAdmins;
    }
    virtual QVector<int> setMemberID()const
    {
        return memberID;
    }
    virtual QVector<QString> getMessages()const
    {
        return messages;
    }
    int getID() const {return ID;}
    QString getName() const{return name;}

protected:
    QVector<QString> nameOfmembers;
    QVector<QString> nemaOfAdmins;
    QVector<int> memberID;
    QVector<QString> messages;

    int ID;
    QString name;
};

#endif // BASECLASS_H
