#ifndef USER_H
#define USER_H

#include<QString>
#include<QVector>
class user
{
public:
    user();
private:
    int ID ;
    QString UserName ;
    QString Password ;
    QString PhoneNumber ;
    QString EmailAddress ;
    QString Firstname;
    QString Lastname;
    QString BirthDate ;
    QVector<int> PVchatsID ;
    QVector<int> GroupsID ;
    QVector<int> ChannelsID ;
    QVector<int> FriendsID ;
public:
    void set_ID(int in_ID) ;
    void set_UserName(QString in_UserName) ;
    void set_Password(QString in_Pass) ;
    void set_Firstname(QString in_firstname) ;
    void set_Lastname(QString in_lastname) ;
    void set_PhoneNumber(QString in_PhoneNumber) ;
    void set_EmailAddress(QString in_EmailAddress) ;
    void set_BirthDate(QString in_BirthDate) ;
    void add_PVchatID(int in_chID) ;
    void add_GroupID(int in_gID) ;
    void add_ChannelID(int in_chID) ;
    void add_FriendID(int in_FID) ;
    int get_ID() ;
    QString get_UserName() ;
    QString get_Password() ;
    QString get_firstname() ;
    QString get_lastname() ;
    QString get_PhoneNumber() ;
    QString get_EmailAddress() ;
    QString get_BirthDate() ;

};
#endif // USER_H
