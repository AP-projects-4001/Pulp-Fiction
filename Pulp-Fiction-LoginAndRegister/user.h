#ifndef USER_H
#define USER_H

#include<QString>
#include<QVector>
#include<QDebug>
enum Access{ General , Friends , Nobody } ;
class user
{
public:
    user();
private:
    int ID ;
    Access nameAccessibility ;
    Access phoneAccessibility ;
    Access photoAccessibility ;
    Access firstNameAccessibility  ;
    Access lastNameAccessibility  ;
    Access emailAccessibility ;
    Access BioAccessibility ;
    QString Bio ;
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
    void set_PVchatID( QVector<int> in_PVchatsID) ;
    void set_GroupsID( QVector<int> in_GroupsID) ;
    void set_ChannelsID( QVector<int> in_ChannelsID) ;
    void set_FriendsID( QVector<int> in_FriendsID) ;
    void set_Bio( QString in_Bio ) ;
    void add_PVchatID(int in_chID) ;
    void add_GroupID(int in_gID) ;
    void add_ChannelID(int in_chID) ;
    void add_FriendID(int in_FID) ;
    void delete_PVchatID(int in_chID) ;
    void delete_GroupID(int in_gID) ;
    void delete_ChannelID(int in_chID) ;
    void delete_FriendID(int in_FID) ;
    int get_ID() ;
    QString get_UserName() ;
    QString get_Password() ;
    QString get_firstname() ;
    QString get_lastname() ;
    QString get_PhoneNumber() ;
    QString get_EmailAddress() ;
    QString get_BirthDate() ;
    QString get_Bio() ;
    QVector<int> get_PVchatsID() ;
    QVector<int> get_GroupsID() ;
    QVector<int> get_ChannelsID() ;
    QVector<int> get_FriendsID() ;
    int getBioAccessibility() ;
    int getNameAccessibility() ;
    int getPhoneAccessibility() ;
    int getPhotoAccessibility() ;
    int getFirstNameAccessibility() ;
    int getLastNameAccessibility() ;
    int getEmailAccessibility() ;
    void setNameAccessibility( int in_Accessibility ) ;
    void setPhoneAccessibility( int in_Accessibility ) ;
    void setPhotoAccessibility( int in_Accessibility ) ;
    void setFirstNameAccessibility(int in_Accessibility) ;
    void setLastNameAccessibility(int in_Accessibility) ;
    void setEmailAccessibility(int in_Accessibility) ;
    void setBioAccessibility( int in_BioAccessibility ) ;


};
#endif // USER_H
