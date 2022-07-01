#ifndef GROUP_H
#define GROUP_H

#include "chat.h"

class Group : public chat
{
private:
    QString GroupName ;
    QVector<user> Members ;
public:
    Group( user in_Owner , QString in_GroupName );
    QString get_GroupName();
    void set_GroupName(QString in_GroupName) ;
    void set_Members( QVector<user> in_Members ) ;
    void add_Member(user &in_Member , QString FileName) ;
    QVector<user> get_Member() ;
    QString ExtractFileName( int GroupID ) ;
    void Make_NewGroupFile( QString FileName  ) ;
    static Group read_Group( int in_ID ) ;

};

#endif // GROUP_H
