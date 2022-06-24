#ifndef CHAT_H
#define CHAT_H
#include<QString>
#include<QVector>
#include "user.h"
class chat
{
protected:
    int ID ;
    user Owner ;
    QVector<QString> Messages ;
public:
    chat();
    int get_ID() ;
    user get_Owner() ;
    QVector<QString> get_Messages() ;
    void set_ID(int in_ID ) ;
    void set_Owner(user in_Owner ) ;
    void add_Message(QString in_Message , QString FileName ) ;
    virtual QString ExtractFileName( int ChatID ) ;
};

#endif // CHAT_H
