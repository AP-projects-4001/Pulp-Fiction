#ifndef CHAT1_H
#define CHAT1_H

#include<QString>
#include<QVector>
#include "user.h"
class chat
{
protected:
    int ID ;
    user Owner ;
    QVector<QString> Messages ;
    QString Name;
public:
    chat();
    int get_ID() ;
    user get_Owner() ;
    QVector<QString> get_Messages() ;
    void set_Messages(QVector<QString> in_Messages ) ;
    void set_ID(int in_ID ) ;
    void set_Owner(user in_Owner ) ;
    void add_Message(QString in_Message , QString FileName ) ;
    virtual QString ExtractFileName( int ChatID ) = 0 ;

    void setName(QString name){Name = name;}
    QString getName()const{return Name;}
    bool isAdminfunction()const{return true;}

};

#endif // CHAT1_H
