#ifndef CHANNEL_H
#define CHANNEL_H

#include "chat.h"

class channel : public chat
{
private:
    QVector<user> Members  ;
    QVector<user> Admins  ;
    QString ChannelName ;
public:
    channel(user in_Owner , QString in_ChannelName);
    void set_ChannelName(QString in_ChannelName) ;
    void set_Members( QVector<user> in_Members ) ;
    QString get_ChannelName() ;
    void add_Member(user in_Member , QString FileName) ;
    QVector<user> get_Members() ;
    QString ExtractFileName( int ChannelID ) ;
    void Make_NewChannelFile( QString FileName  ) ;
    static channel read_channel( int in_ID ) ;
    QVector<user> get_Admins() ;
    void set_Admins( QVector<user> in_Admins) ;
    void add_Admins(user in_Admin , QString FileName) ;
};

#endif // CHANNEL_H
